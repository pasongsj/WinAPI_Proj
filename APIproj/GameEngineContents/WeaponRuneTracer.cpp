#include "WeaponRuneTracer.h"
#include "ContentsEnums.h"
#include "Player.h"
#include <GameEngineCore/GameEngineLevel.h>
#include <GameEngineBase/GameEngineRandom.h>

#include "Monster.h"

WeaponRuneTracer::WeaponRuneTracer()
{
}

WeaponRuneTracer::~WeaponRuneTracer()
{
}

void WeaponRuneTracer::LevelUp()
{
	Weapon::LevelUp();
	if (2 == GetWeaponLevel() || 5 == GetWeaponLevel()) //기본 속도가 20% 증가합니다.2 5
	{
		SetWeaponSpeed(GetWeaponSpeed() * 1.2f);
	}
	if (3 == GetWeaponLevel() || 6 == GetWeaponLevel()) //효과가 0.3초 더 오래 지속됩니다. 3 6
	{
		SetRunTime(GetRunTime() + 0.3f);
	}
	else if (4 == GetWeaponLevel() || 7 == GetWeaponLevel()) // 발사체를 1개 더 발사합니다. 4 7
	{
		SetWeaponCount(GetOriginWeaponCount() + 1);
	}
	else if (8 == GetWeaponLevel()) // 효과가 0.5초 더 오래 지속됩니다. 8
	{
		SetRunTime(GetRunTime() + 0.5f);
	}

	if (8 == GetWeaponLevel())
	{
		AdditionItemUI::DeleteItemName.push_back(GetWeaponName());
	}
}

//void WeaponRuneTracer::SetWeaponDir()
//{
//	std::vector<float4> _Dir;
//	_Dir.clear();
//
//	for (int i = 0;i < WeaponRender.size();i++) { // 0,0이 나오면 ..?
//		WeaponDir[i] = float4{ GameEngineRandom::MainRandom.RandomFloat(-1.0f, 1.0f) ,GameEngineRandom::MainRandom.RandomFloat(-1.0f, 1.0f) }.GetNormalize();
//	}
//
//}



void WeaponRuneTracer::ReSet()
{
	if (0 == WeaponRender.size()) {
		return;
	}
	float4 _Pos = Player::MainPlayer->GetPos();
	_Pos.y -= 32;
	//SetPos(_Pos);

	int _Num = 0;/*GetWeaponCount();*/
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

		WeaponDir[index] = float4{ GameEngineRandom::MainRandom.RandomFloat(-1.0f, 1.0f) ,GameEngineRandom::MainRandom.RandomFloat(-1.0f, 1.0f) }.GetNormalize();
		LuneLiveTime[index] = 0.0f;

		WeaponRender[index]->On();
		WeaponCollision[index]->On();
		
		++index;
		++_Num;
	}

	/*for (int i = 0;i < WeaponRender.size();++i)
	{
		WeaponRender[i]->SetPosition(float4::Zero);
		WeaponCollision[i]->SetPosition(float4::Zero);

		WeaponRender[i]->SetScale(GetWeaponRenderScale());
		WeaponCollision[i]->SetScale(GetWeaponCollisionScale());

		LuneLiveTime[i] = 0.0f;

		WeaponRender[i]->On();
		WeaponCollision[i]->On();
	}*/
	//SetWeaponDir();

	WaitTime = 0;
}



void WeaponRuneTracer::Init()
{
	{
		GameEngineRender* Render = CreateRender(VSRenderOrder::Weapon);
		Render->SetImage("RuneTracer.bmp");
		Render->SetScaleToImage();

		GameEngineCollision* Collision = CreateCollision(VSRenderOrder::Weapon);
		Collision->SetScale((Render->GetScale())*0.7f);

		WeaponRender.push_back(Render);
		WeaponCollision.push_back(Collision);
		WeaponDir.push_back(float4::Zero);

		SetWeaponScale(Render->GetScale(), Collision->GetScale());

		LuneLiveTime.push_back(0.0f);
		Render->Off();
		Collision->Off();
	}
}

void WeaponRuneTracer::Start()
{
	SetWeaponName("RuneTracer");
	SetWeaponCount(1);

	SetCoolTime(3.0f);
	SetRunTime(2.25f);
	float _Dmg[9] = { 0.0f,10.0f,15.0f,20.0f,20.0f,25.0f,30.0f,30.0f,30.0f };
	SetDmg(_Dmg);
	SetWeaponSpeed(1000.0f);

	Weapon::Weapons[GetWeaponName()] = this;
	for (int i = 0;i < GetWeaponCount();i++)
	{
		Init();
	}
	this->Off();
}


float4 WeaponRuneTracer::CheckNextPos(const float4& _Pos, const float4& _Dir)
{
	//float4 NextDir = _Dir;
	CollisionData Screen = { Player::MainPlayer->GetPos() , GameEngineWindow::GetScreenSize() };
	// PlayerPos
	float4 NextDir[4] = { _Dir,{_Dir.y,-_Dir.x},-_Dir, {-_Dir.y,_Dir.x} };
	for (int i = 0;i < 4;++i)
	{
		float4 NextPos = _Pos + NextDir[i];
		if (Screen.Bot() > NextPos.y && Screen.Top() < NextPos.y && Screen.Left() < NextPos.x && Screen.Right() > NextPos.x)
		{
			if (0 != i) {
				return NextDir[i] * 10;
			}
			return NextDir[i];
		}
	}
	return float4::Zero;
}

void WeaponRuneTracer::Update(float _DeltaTime)
{
	if (WeaponRender.size() == 0 || WeaponCollision.size() == 0)
	{
		MsgAssert("무기랜더가 생성되지 않았습니다.");
		return;
	}

	/*if (WaitTime > GetRunTime())
	{
		for (int i = 0;i < WeaponRender.size();++i)
		{
			WeaponRender[i]->Off();
			WeaponCollision[i]->Off();
		}
		return;
	}*/



	for (int i = 0;i < WeaponRender.size();++i)
	{

		if (false == WeaponRender[i]->IsUpdate() || LuneLiveTime[i] > GetRunTime()) // 이미 off된 투사체 또는 지속시간이 지난 투사체
		{
			WeaponRender[i]->Off();
			WeaponCollision[i]->Off();
			continue;
		}

		LuneLiveTime[i] += _DeltaTime;
		WeaponDir[i] = CheckNextPos(GetPos() + WeaponRender[i]->GetPosition(),WeaponDir[i] * _DeltaTime * GetWeaponSpeed()).GetNormalize();
		WeaponRender[i]->SetMove(WeaponDir[i] * _DeltaTime * GetWeaponSpeed());
		WeaponCollision[i]->SetMove(WeaponDir[i] * _DeltaTime * GetWeaponSpeed());

		std::vector<GameEngineCollision*> Collision;
		if (true == WeaponCollision[i]->Collision({ .TargetGroup = static_cast<int>(VSRenderOrder::Monster), .ThisColType = CollisionType::CT_CirCle }, Collision))
		{
			for (size_t j = 0; j < Collision.size(); j++)
			{
				GameEngineActor* ColActor = Collision[j]->GetActor();
				Monster* ColWeaponActor = dynamic_cast<Monster*> (ColActor);
				ColWeaponActor->Attack(GetDmg());
			}
		}
	}
}
