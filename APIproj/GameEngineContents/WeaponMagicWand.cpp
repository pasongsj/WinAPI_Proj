#include "WeaponMagicWand.h"
#include "ContentsEnums.h"
#include "Player.h"
#include <GameEngineCore/GameEngineLevel.h>

#include "Monster.h"
WeaponMagicWand::WeaponMagicWand()
{
}

WeaponMagicWand::~WeaponMagicWand()
{
}

void WeaponMagicWand::ReSet()
{
	Passes = 1;
	WaitTime = 0;
	SetPos(Player::MainPlayer->GetPos());
	WepaonDir = float4::Zero;
	this->On();
}

void WeaponMagicWand::Start()
{
	SetWeaponName("MagicWand");

	WeaponRender = CreateRender(VSRenderOrder::Weapon);
	WeaponCollision = CreateCollision(VSRenderOrder::Weapon);

	WeaponRender->SetImage("MagicWandTmp.bmp");
	WeaponRender->SetScale({20,20});


	float4 CollisionScale = WeaponRender->GetScale();
	WeaponCollision->SetScale(CollisionScale);

	SetCoolTime(1.2f);
	SetRunTime(1.0f);
	int _Dmg[9] = { 0,10,10,10,10,20,20,20,30 };
	SetDmg(_Dmg);

	Weapon::Weapons[GetWeaponName()] = this;

	this->Off();
}

void WeaponMagicWand::Update(float _DeltaTime)
{
	if (WaitTime > GetRunTime())
	{
		this->Off();
	}

	if (float4::Zero == WepaonDir)
	{
		float MinLen = 3.40282e+38; // floatÃÖ´ñ°ª 3.402823466 E + 38
		std::vector<GameEngineActor*> _Monsters = GetLevel()->GetActors(VSRenderOrder::Monster);
		for (GameEngineActor* _Monster : _Monsters)
		{
			float4 Diff = (_Monster->GetPos() - GetPos());
			if (MinLen > Diff.Size()) {
				MinLen = Diff.Size();
				WepaonDir = (Diff.Normalize());
			}
		}
	}
	SetMove(WepaonDir * _DeltaTime * 600);


	std::vector<GameEngineCollision*> Collision;
	if (true == WeaponCollision->Collision({ .TargetGroup = static_cast<int>(VSRenderOrder::Monster), .ThisColType = CollisionType::CT_CirCle }, Collision))
	{

		for (size_t i = 0; i < Collision.size(); i++)
		{
			GameEngineActor* ColActor = Collision[i]->GetActor();
			Monster* ColWeaponActor = dynamic_cast<Monster*> (ColActor);
			ColWeaponActor->Attack(GetDmg());
			--Passes;
			if (Passes <= 0) {
				this->Off();
				return; // or Continue;
			}

		}
	}
}
