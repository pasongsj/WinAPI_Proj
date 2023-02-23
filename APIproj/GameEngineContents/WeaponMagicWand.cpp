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


void WeaponMagicWand::Start()
{
	SetPos(Player::MainPlayer->GetPos());
	WeaponRender = CreateRender(VSRenderOrder::Weapon);
	WeaponCollision = CreateCollision(VSRenderOrder::Weapon);

	//Weapon* NewWeapon = _Level->CreateActor<Weapon>(VSRenderOrder::Weapon);
	SetWeaponName("MagicWand");
	//WeaponRender->SetImage("MagicWandTmp");
	WeaponRender->SetImageToScaleToImage("MagicWandTmp");

	/*WeaponRender->CreateAnimation({ .AnimationName = "Right_Whip",  .ImageName = "RightWhip.bmp", .Start = 0, .End = 5, .InterTime = 0.02f });
	WeaponRender->CreateAnimation({ .AnimationName = "Left_Whip",  .ImageName = "LeftWhip.bmp", .Start = 0, .End = 5, .InterTime = 0.02f });
	WeaponRender->CreateAnimation({ .AnimationName = "Bidi_Whip",  .ImageName = "BidiWhip.bmp", .Start = 0, .End = 5, .InterTime = 0.02f });*/
	//WeaponRender->SetPosition({ 0, -60 });

	float4 CollisionScale = WeaponRender->GetScale();
	//CollisionScale.x = CollisionScale.hx();
	WeaponCollision->SetScale(CollisionScale);

	SetCoolTime(2.0f);
	SetRunTime(0.1f);
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
	std::vector<GameEngineActor*> _Monsters = GetLevel()->GetActors(VSRenderOrder::Monster);


	std::string Dir = Player::MainPlayer->GetDirString();
	std::string _Animation = Dir + GetWeaponName();
	WeaponRender->ChangeAnimation(_Animation);
	if ("Right_" == Dir) {
		WeaponCollision->SetPosition({ WeaponCollision->GetScale().hx(),-WeaponCollision->GetScale().y });
	}
	else
	{
		WeaponCollision->SetPosition({ -WeaponCollision->GetScale().hx(),-WeaponCollision->GetScale().y });
	}

}

