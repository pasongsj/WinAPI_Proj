#include "WeaponKnife.h"
#include "ContentsEnums.h"
#include "Monster.h"
#include "Player.h"

WeaponKnife::WeaponKnife()
{
}

WeaponKnife::~WeaponKnife()
{
}


void WeaponKnife::ReSet()
{

	float4 _Pos = Player::MainPlayer->GetPos();
	_Pos.y -= 32;
	SetPos(_Pos);
	//if (_Dir != float4::Zero) {
	//	int  a = 0;
	//}
	float4 _Dir = float4::Zero;
	if (0 == WeaponRender.size()) {
		return;
	}
	for (int i = 0;i < WeaponRender.size();++i)
	{
		WeaponRender[i]->SetPosition(float4::Zero);
		WeaponCollision[i]->SetPosition(float4::Zero);
		Passes[i] = 1;

		WeaponRender[i]->SetScale(GetWeaponRenderScale());
		WeaponCollision[i]->SetScale(GetWeaponCollisionScale());

		WeaponRender[i]->On();
		WeaponCollision[i]->On();
		_Dir = Player::MainPlayer->GetLastMoveVec();

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
		WeaponDir[i] = _Dir;
		WeaponRender[i]->SetAngle(KnifeAngle);
	}
	Player::MainPlayer->SetLastMoveVec(float4::Zero);
	WaitTime = 0;

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

	}
}

void WeaponKnife::Start() 
{
	SetWeaponName("Knife");
	Init();


	SetCoolTime(1.0f);
	SetRunTime(0.8f);
	float _Dmg[9] = { 0,6.5f,6.5f,11.5f,11.5f,11.5f,11.5f, 16.5f, 16.5f };
	SetDmg(_Dmg);
	SetWeaponSpeed(800.0f);

	Weapon::Weapons[GetWeaponName()] = this;

}
void WeaponKnife::Update(float _DeltaTime)
{
	if (WeaponRender.size() == 0 || WeaponCollision.size() == 0)
	{
		MsgAssert("무기랜더가 생성되지 않았습니다.");
		return;
	}

	if (WaitTime > GetRunTime())
	{
		for (int i = 0;i < WeaponRender.size();++i)
		{
			WeaponRender[i]->Off();
			WeaponCollision[i]->Off();
		}
		return;

	}

	for (int i = 0;i < WeaponRender.size();++i)
	{
		WeaponRender[i]->SetMove(WeaponDir[i] * _DeltaTime * GetWeaponSpeed());
		WeaponCollision[i]->SetMove(WeaponDir[i] * _DeltaTime * GetWeaponSpeed());
		float _GetAngVal = WeaponRender[i]->GetAngle();

		std::vector<GameEngineCollision*> Collision;
		if (true == WeaponCollision[i]->Collision({ .TargetGroup = static_cast<int>(VSRenderOrder::Monster), .ThisColType = CollisionType::CT_Rect }, Collision))
		{

			for (size_t i = 0; i < Collision.size(); i++)
			{
				GameEngineActor* ColActor = Collision[i]->GetActor();
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
