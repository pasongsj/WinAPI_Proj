#include "WeaponFireWand.h"
#include "ContentsEnums.h"
#include "Player.h"
#include <GameEngineCore/GameEngineLevel.h>
#include <GameEngineBase/GameEngineRandom.h>

#include "Monster.h"

WeaponFireWand::WeaponFireWand()
{
}

WeaponFireWand::~WeaponFireWand()
{
}


void WeaponFireWand::ReSet()
{
	if (0 == WeaponRender.size()) {
		return;
	}
	float4 _Pos = Player::MainPlayer->GetPos();
	_Pos.y -= 32;
	SetPos(_Pos);

	float4 MainDir = float4{ GameEngineRandom::MainRandom.RandomFloat(-1.0f, 1.0f) ,GameEngineRandom::MainRandom.RandomFloat(-1.0f, 1.0f) }.GetNormalize();

	for (int i = 0;i < WeaponRender.size();++i)
	{
		WeaponRender[i]->SetPosition(float4::Zero);
		WeaponCollision[i]->SetPosition(float4::Zero);

		Passes[i] = GetWeaponPass();
		if (0 == (i ^ 0)) // 짝수라면?
		{
			WeaponDir[i] = MainDir.RotaitonZDegReturn(static_cast<float>(i * 3));
		}
		else // 홀수라면?
		{
			WeaponDir[i] = MainDir.RotaitonZDegReturn(static_cast<float>(- i * 3));
		}
		WeaponRender[i]->SetAngle(7); // float4{1, 0}위치기준
		float GetAng = float4{ 1,0 }.GetAngelBetweenVec(WeaponDir[i]) * GameEngineMath::RadToDeg;
		WeaponRender[i]->SetAngleAdd(GetAng);

		WeaponRender[i]->SetScale(GetWeaponRenderScale());
		WeaponCollision[i]->SetScale(GetWeaponCollisionScale());

		WeaponRender[i]->On();
		WeaponCollision[i]->On();
	}

	WaitTime = 0;
}

void WeaponFireWand::Init()
{
	{
		GameEngineRender* Render = CreateRender(VSRenderOrder::Weapon);
		Render->SetImage("FireWand.bmp");
		Render->SetScaleToImage();
		Render->SetRotFilter("FireWandBlack.bmp");

		GameEngineCollision* Collision = CreateCollision(VSRenderOrder::Weapon);
		Collision->SetScale({ 25,25 });

		WeaponRender.push_back(Render);
		WeaponCollision.push_back(Collision);
		WeaponDir.push_back(float4::Zero);
		Passes.push_back(1);
		SetWeaponScale(Render->GetScale(), Collision->GetScale());

	}
}

void WeaponFireWand::Start()
{
	SetWeaponName("FireWand");
	Init();
	Init();
	Init();

	SetCoolTime(3.0f);
	SetRunTime(2.9f);
	float _Dmg[9] = { 0.0f,20.0f,30.0f,40.0f,50.0f,60.0f,70.0f,80.0f,90.0f };
	SetDmg(_Dmg);
	SetWeaponSpeed(400.0f);

	Weapon::Weapons[GetWeaponName()] = this;

	this->Off();
}

void WeaponFireWand::Update(float _DeltaTime)
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

		std::vector<GameEngineCollision*> Collision;
		if (true == WeaponCollision[i]->Collision({ .TargetGroup = static_cast<int>(VSRenderOrder::Monster), .ThisColType = CollisionType::CT_CirCle }, Collision))
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
