#include "WeaponKnife.h"
#include "ContentsEnums.h"
#include "Monster.h"
#include "Player.h"
#include <GameEnginePlatform/GameEngineWindow.h>

WeaponKnife::WeaponKnife()
{
}

WeaponKnife::~WeaponKnife()
{
}

void WeaponKnife::LevelUp()
{
	Weapon::LevelUp();

	if (2 == GetWeaponLevel() || 3 == GetWeaponLevel() || 4 == GetWeaponLevel() || 6 == GetWeaponLevel() || 7 == GetWeaponLevel()) //발사체를 1개 더 발사합니다.2 3 4 6 7
	{
		SetWeaponCount(GetOriginWeaponCount() + 1);
	}
	else if (5 == GetWeaponLevel() || 8 == GetWeaponLevel()) // 적 1명을 더 통과합니다.
	{
		SetWeaponPass(GetWeaponPass() + 1);
	}

	if (8 == GetWeaponLevel())
	{
		AdditionItemUI::DeleteItemName.push_back(GetWeaponName());
	}
}


void WeaponKnife::ReSet()
{

	if (0 == WeaponRender.size()) {
		return;
	}

	float4 _Pos = Player::MainPlayer->GetPos();
	_Pos.y -= 32;
	


	// 방향 설정, 무기 각도 설정
	float4 _Dir = Player::MainPlayer->GetLastMoveVec();
	float KnifeAngle = 0.0f;
	if (float4::Zero == _Dir || float4{ -1,0,0,1 } == _Dir)
	{
		if ("Right_" == Player::MainPlayer->GetDirString())
		{
			_Dir = float4{ 1,0 };
			KnifeAngle = 0.0f;
		}
		else if("Left_" == Player::MainPlayer->GetDirString())
		{
			_Dir = float4{ -1,0 };
			KnifeAngle = 181.0f;
		}
	}
	else
	{
		KnifeAngle = float4{ 1,0 }.GetAngelBetweenVec(_Dir) * GameEngineMath::RadToDeg;
	}
	
	int _Num = 0; // reset한 Weapon 수
	int index = 0; // 인덱스
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
		if (0 == (_Num & 1))
		{
			WeaponRender[index]->SetPosition(_Pos + float4{ 0,static_cast<float>(_Num*5) });
			WeaponCollision[index]->SetPosition(_Pos + float4{ 0,static_cast<float>(_Num*5) });
		}
		else
		{
			WeaponRender[index]->SetPosition(_Pos + float4{ 0,static_cast<float>(-_Num*5) });
			WeaponCollision[index]->SetPosition(_Pos + float4{ 0,static_cast<float>(-_Num*5) });
		}
		Passes[index] = GetWeaponPass();
		WeaponRender[index]->SetScale(GetWeaponRenderScale());
		WeaponCollision[index]->SetScale(GetWeaponCollisionScale());
		WeaponDir[index] = _Dir;
		WeaponRender[index]->SetAngle(KnifeAngle);
		DelayTime[index] = static_cast<float>(_Num) * -ProjectileInterval; // 날아가는 타이밍 다각화

		WeaponRender[index]->On();
		WeaponCollision[index]->On();

		index++;
		++_Num;
	}
	
	Player::MainPlayer->SetLastMoveVec(float4::Zero);
	WaitTime = 0;

}

bool WeaponKnife::IsInScreen(float4 _Pos)
{
	CollisionData Screen = { Player::MainPlayer->GetPos() , GameEngineWindow::GetScreenSize() };
	if (Screen.Bot() > _Pos.y && Screen.Top() < _Pos.y && Screen.Left() < _Pos.x && Screen.Right() > _Pos.x)
	{
		return true;
	}
	return false;
}

void WeaponKnife::Init()
{
	{
		GameEngineRender* Render = CreateRender(VSRenderOrder::Weapon);
		Render->SetImage("Knife.bmp");
		Render->SetScaleToImage();
		Render->SetRotFilter("KnifeBlack.bmp");

		GameEngineCollision* Collision = CreateCollision(VSRenderOrder::Weapon);
		Collision->SetScale(Render->GetScale().half());

		WeaponRender.push_back(Render);
		WeaponCollision.push_back(Collision);
		WeaponDir.push_back(float4::Zero);
		Passes.push_back(1);
		SetWeaponScale(Render->GetScale(), Collision->GetScale());
		DelayTime.push_back(0.0f);
		Render->Off();
		Collision->Off();

	}
}

void WeaponKnife::Start() 
{
	SetWeaponName("Knife");
	SetWeaponCount(1);
	SetWeaponPass(1);
	SetCoolTime(1.0f);
	SetRunTime(10.0f);
	float _Dmg[9] = { 0,6.5f,6.5f,11.5f,11.5f,11.5f,11.5f, 16.5f, 16.5f };
	SetDmg(_Dmg);
	SetWeaponSpeed(800.0f);

	Weapon::Weapons[GetWeaponName()] = this;
	for (int i = 0;i < GetWeaponCount();i++)
	{
		Init();
	}


}
void WeaponKnife::Update(float _DeltaTime)
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
		float _GetAngVal = WeaponRender[i]->GetAngle();

		std::vector<GameEngineCollision*> Collision;
		if (true == WeaponCollision[i]->Collision({ .TargetGroup = static_cast<int>(VSRenderOrder::Monster), .ThisColType = CollisionType::CT_Rect }, Collision))
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
					return; // or Continue;
				}

			}
		}
	}
}
