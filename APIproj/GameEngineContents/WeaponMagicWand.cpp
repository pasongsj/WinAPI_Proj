#include "WeaponMagicWand.h"
#include "ContentsEnums.h"
#include "Player.h"
#include <GameEngineCore/GameEngineLevel.h>
WeaponMagicWand::WeaponMagicWand()
{
}

WeaponMagicWand::~WeaponMagicWand()
{
}

void WeaponMagicWand::ReSet()
{
	WaitTime = 0;
	SetPos(Player::MainPlayer->GetPos());
	WepaonDir = float4::Zero;
	this->On();
}

void WeaponMagicWand::Start()
{
	//SetPos(Player::MainPlayer->GetPos());
	WeaponRender = CreateRender(VSRenderOrder::Weapon);
	WeaponCollision = CreateCollision(VSRenderOrder::Weapon);

	//Weapon* NewWeapon = _Level->CreateActor<Weapon>(VSRenderOrder::Weapon);
	SetWeaponName("MagicWand");
	//WeaponRender->SetImage("MagicWandTmp");
	WeaponRender->SetImage("MagicWandTmp.bmp");
	WeaponRender->SetScale({20,20});
	//WeaponRender->SetImageToScaleToImage("MagicWandTmp.bmp");


	float4 CollisionScale = WeaponRender->GetScale();
	//CollisionScale.x = CollisionScale.hx();
	WeaponCollision->SetScale(CollisionScale);

	SetCoolTime(4.0f);
	SetRunTime(3.0f);
	int _Dmg[9] = { 0,10,10,15,20,25,30,35,40 };
	SetDmg(_Dmg);

	//NewWeapon->GetWeaponCollision()->SetScale(CollisionScale);
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
	SetMove(WepaonDir * _DeltaTime * 450);
	//SetPos(GetPos() + WepaonDir);

	//std::string Dir = Player::MainPlayer->GetDirString();
	//std::string _Animation = Dir + GetWeaponName();
	//WeaponRender->ChangeAnimation(_Animation);
	//if ("Right_" == Dir) {
	//	WeaponCollision->SetPosition({ WeaponCollision->GetScale().hx(),-WeaponCollision->GetScale().y });
	//}
	//else
	//{
	//	WeaponCollision->SetPosition({ -WeaponCollision->GetScale().hx(),-WeaponCollision->GetScale().y });
	//}

}
