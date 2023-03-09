#include "WeaponMagicWand.h"
#include "ContentsEnums.h"
#include "Player.h"
#include <GameEngineCore/GameEngineLevel.h>
#include <GameEngineBase/GameEngineRandom.h>
#include <list>
#include "Monster.h"
WeaponMagicWand::WeaponMagicWand()
{
}

WeaponMagicWand::~WeaponMagicWand()
{
}

void WeaponMagicWand::LevelUp()
{
	Weapon::LevelUp();
	if (2 == GetWeaponLevel() || 4 == GetWeaponLevel() || 6 == GetWeaponLevel()) //발사체를 1개 더 발사합니다.2 4 6
	{
		SetWeaponCount(GetOriginWeaponCount() + 1);
	}
	if (3 == GetWeaponLevel() ) //재사용 대기시간이 0.2초 감소했습니다.3
	{
		SetCoolTime(GetCoolTime() - 0.2f);
	}
	else if (7 == GetWeaponLevel()) // 적 1명을 더 통과합니다. 7 
	{
		SetWeaponPass(GetWeaponPass() + 1);
	}

	if (8 == GetWeaponLevel())
	{
		AdditionItemUI::DeleteItemName.push_back(GetWeaponName());
	}
}

void WeaponMagicWand::ReSet()
{
	if (0 == WeaponRender.size()) {
		return;
	}
	float4 _Pos = Player::MainPlayer->GetPos();
	_Pos.y -= 32;
	//SetPos(_Pos);

	std::vector<float4> _Dir = GetWeaponDir(_Pos);

	int _Num = 0;
	int index = 0;
	while (_Num < GetWeaponCount())
	{
		if (WeaponRender.size() - 1 < index) // 투사체가 부족할 시
		{
			Init();
		}

		if (true == WeaponRender[index]->IsUpdate()) // 현재 활동중인 투사체 무기
		{
			index++;
			continue;
		}

		WeaponRender[index]->SetPosition(_Pos);
		WeaponCollision[index]->SetPosition(_Pos);

		WeaponRender[index]->SetScale(GetWeaponRenderScale());
		WeaponCollision[index]->SetScale(GetWeaponCollisionScale());
		
		Passes[index] = GetWeaponPass();
		WeaponRender[index]->SetAngle(108); // float4{1, 0}위치기준

		WeaponDir[index] = _Dir[_Num];
		float GetAng = float4{ 1,0 }.GetAngelBetweenVec(WeaponDir[index]) * GameEngineMath::RadToDeg;
		WeaponRender[index]->SetAngleAdd(GetAng);

		DelayTime[index] = static_cast<float>(_Num) * -ProjectileInterval; // 날아가는 타이밍 다각화


		WeaponRender[index]->On();
		WeaponCollision[index]->On();
		index++;
		++_Num;
	}
	
	WaitTime = 0;
	/*GameEngineSoundPlayer Dwn = GameEngineResources::GetInst().SoundPlayToControl("ProjectileMagic.mp3");
	Dwn.Volume(0.2f);
	Dwn.LoopCount(1);*/
}


std::vector<float4> WeaponMagicWand::GetWeaponDir(const float4& _Pos) // -- 방향 수정필요
{
	std::list<float4> _Dir;
	std::vector<float4> DirReturn;
	_Dir.clear();
	float MinLen = static_cast<float>(3.40282e+38); // float최댓값 3.402823466 E + 38
	std::vector<GameEngineActor*> _Monsters = GetLevel()->GetActors(VSRenderOrder::Monster);
	for (GameEngineActor* _Monster : _Monsters)
	{
		if (false == _Monster->IsUpdate())
		{
			continue;
		}
		float4 Diff = (_Monster->GetPos() - Player::MainPlayer->GetPos());
		if (MinLen > Diff.Size()) {
			MinLen = Diff.Size();
			_Dir.push_front(Diff.GetNormalize());
		}
	}
	int lim = static_cast<int>(_Dir.size());
	std::list<float4>::iterator DirBegin = _Dir.begin();
	std::list<float4>::iterator DirEnd = _Dir.end();
	for (;DirBegin!= DirEnd;DirBegin++)
	{
		DirReturn.push_back(*DirBegin);
	}
	for (int i = 0;i < GetWeaponCount() - lim;i ++ )
	{
		float4 RandomDir = float4{ GameEngineRandom::MainRandom.RandomFloat(-1.0f, 1.0f) ,GameEngineRandom::MainRandom.RandomFloat(-1.0f, 1.0f) }.GetNormalize();
		DirReturn.push_back(RandomDir);
	}
	return DirReturn;
}


bool WeaponMagicWand::IsInScreen(float4 _Pos)
{
	CollisionData Screen = { Player::MainPlayer->GetPos() , GameEngineWindow::GetScreenSize() };
	if (Screen.Bot() > _Pos.y && Screen.Top() < _Pos.y && Screen.Left() < _Pos.x && Screen.Right() > _Pos.x)
	{
		return true;
	}
	return false;
}

void WeaponMagicWand::Init()
{
	{
		GameEngineRender* Render = CreateRender(VSRenderOrder::Weapon);
		Render->SetImage("MagicWand.bmp");
		Render->SetScaleToImage();
		Render->SetRotFilter("MagicWandBlack.bmp");

		GameEngineCollision* Collision = CreateCollision(VSRenderOrder::Weapon);
		Collision->SetScale({ 25,25 });

		WeaponRender.push_back(Render);
		WeaponCollision.push_back(Collision);
		WeaponDir.push_back(float4::Zero);
		Passes.push_back(1);
		if (GetOriginCollisionScale() == float4::Zero)
		{
			SetWeaponScale(Render->GetScale(), Collision->GetScale());
		}
		DelayTime.push_back(0.0f);
		Render->Off();
		Collision->Off();

	}
}

void WeaponMagicWand::Start()
{
	SetWeaponName("MagicWand");
	SetWeaponCount(1);

	SetCoolTime(1.2f);
	SetRunTime(10.0f);
	float _Dmg[9] = { 0.0f,10.0f,10.0f,10.0f,10.0f,20.0f,20.0f,20.0f,30.0f };
	SetDmg(_Dmg);
	SetWeaponSpeed(600.0f);
	SetWeaponPass(1);

	Weapon::Weapons[GetWeaponName()] = this;
	for (int i = 0;i < GetWeaponCount();i++)
	{
		Init();
	}

	this->Off();
}

void WeaponMagicWand::Update(float _DeltaTime)
{
	if (WeaponRender.size() == 0 || WeaponCollision.size() == 0)
	{
		MsgAssert("무기랜더가 생성되지 않았습니다.");
		return;
	}

	//if (WaitTime > GetRunTime())
	//{
	//	for (int i = 0;i < WeaponRender.size();++i)
	//	{
	//		WeaponRender[i]->Off();
	//		WeaponCollision[i]->Off();
	//	}
	//	return;
	//	//this->Off();
	//}



	for (int i = 0;i < WeaponRender.size();++i)
	{
		if (false == WeaponRender[i]->IsUpdate() || false == IsInScreen(GetPos() + WeaponRender[i]->GetPosition())) // 이미 off된 투사체 또는 화면밖으로 나가 off할 투사체
		{
			WeaponRender[i]->Off();
			WeaponCollision[i]->Off();
			continue;
		}
		if (DelayTime[i] < 0.0f) // 투사체 딜레이타임 조절
		{
			DelayTime[i] += _DeltaTime;
			continue;
		}

		WeaponRender[i]->SetMove(WeaponDir[i] * _DeltaTime * GetWeaponSpeed());
		WeaponCollision[i]->SetMove(WeaponDir[i] * _DeltaTime * GetWeaponSpeed());

		std::vector<GameEngineCollision*> Collision;
		if (true == WeaponCollision[i]->Collision({ .TargetGroup = static_cast<int>(VSRenderOrder::Monster), .TargetColType = CollisionType::CT_Rect, .ThisColType = CollisionType::CT_CirCle }, Collision))
		{

			for (size_t j = 0; j < Collision.size(); j++)
			{
				GameEngineActor* ColActor = Collision[j]->GetActor();
				Monster* ColWeaponActor = dynamic_cast<Monster*> (ColActor);
				ColWeaponActor->Attack(GetDmg());
				--Passes[i];
				if (Passes[i] <= 0) {
					WeaponRender[i]->Off();
					WeaponCollision[i]->Off();
					break; // or Continue;
				}

			}
		}
		/*if (Collision.size() > 0)
		{
			GameEngineSoundPlayer Dwn = GameEngineResources::GetInst().SoundPlayToControl("EnemyHit.mp3");
			Dwn.Volume(1.0f);
			Dwn.LoopCount(1);
			Dwn.LoopCount(1);
		}*/
	}
}
