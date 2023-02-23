#include "WeaponWhip.h"
#include "ContentsEnums.h"

#include "Player.h"
#include "Monster.h"
WeaponWhip::WeaponWhip()
{
}

WeaponWhip::~WeaponWhip()
{
}

void WeaponWhip::ReSet()
{
	WaitTime = 0;
	this->On();
}


void WeaponWhip::Start()
{
	WeaponRender = CreateRender(VSRenderOrder::Weapon);
	WeaponCollision = CreateCollision(VSRenderOrder::Weapon);

	//Weapon* NewWeapon = _Level->CreateActor<Weapon>(VSRenderOrder::Weapon);
	SetWeaponName("Whip");
	
	WeaponRender->CreateAnimation({ .AnimationName = "Right_Whip",  .ImageName = "RightWhip.bmp", .Start = 0, .End = 5, .InterTime = 0.02f });
	WeaponRender->CreateAnimation({ .AnimationName = "Left_Whip",  .ImageName = "LeftWhip.bmp", .Start = 0, .End = 5, .InterTime = 0.02f });
	WeaponRender->CreateAnimation({ .AnimationName = "Bidi_Whip",  .ImageName = "BidiWhip.bmp", .Start = 0, .End = 5, .InterTime = 0.02f });
	WeaponRender->SetScale({ 600,60 });
	WeaponRender->SetPosition({ 0, -60 });

	float4 CollisionScale = WeaponRender->GetScale();
	CollisionScale.x = CollisionScale.hx();
	WeaponCollision->SetScale(CollisionScale);

	SetCoolTime(2.0f);
	SetRunTime(0.1f);
	int _Dmg[9] = { 0,10,10,15,20,25,30,35,40 };
	SetDmg(_Dmg);

	//NewWeapon->GetWeaponCollision()->SetScale(CollisionScale);
	Weapon::Weapons[GetWeaponName()] = this;

	this->Off();
}

void WeaponWhip::Update(float _DeltaTime)
{
	if (WaitTime > GetRunTime())
	{
		this->Off();
	}
	SetPos(Player::MainPlayer->GetPos());
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



	std::vector<GameEngineCollision*> Collision;
	if (true == WeaponCollision->Collision({ .TargetGroup = static_cast<int>(VSRenderOrder::Monster), .ThisColType = CollisionType::CT_Rect }, Collision))
	{
		int a = 0;
		for (size_t i = 0; i < Collision.size(); i++)
		{

			GameEngineActor* ColActor = Collision[i]->GetActor();
			Monster* ColWeaponActor = dynamic_cast<Monster*> (ColActor);

			ColWeaponActor->Attack(GetDmg());

		}
	}
}

