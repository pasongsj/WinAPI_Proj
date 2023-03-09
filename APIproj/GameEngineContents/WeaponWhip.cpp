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

void WeaponWhip::LevelUp()
{
	Weapon::LevelUp();
	if (2 == GetWeaponLevel())
	{
		WeaponRender->ChangeAnimation("Bi_Whip");
		float4 Col_Scale = GetOriginCollisionScale();
		Col_Scale.x *= 2;
		SetWeaponCollisionScale(Col_Scale);
		WeaponCollision->SetPosition(float4::Zero);
		SetRunTime(0.2f);
	}
	if (4 == GetWeaponLevel() || 6 == GetWeaponLevel())
	{
		SetWeaponScale(GetOriginRenderScale() * 1.1f, GetOriginCollisionScale() * 1.1f);
	}
	if (8 == GetWeaponLevel())
	{
		AdditionItemUI::DeleteItemName.push_back(GetWeaponName());
	}
}

void WeaponWhip::ReSet()
{
	//this->On();
	if (nullptr == WeaponRender) {
		return;
	}
	else {
		if (1 == GetWeaponLevel())
		{
			LastDir = Player::MainPlayer->GetDirString();
			if ("Right_" == LastDir)
			{
				WeaponRender->ChangeAnimation("Right_Whip");
				WeaponCollision->SetPosition({ 125, });
			}
			else if ("Left_" == LastDir)
			{
				WeaponRender->ChangeAnimation("Left_Whip");
				WeaponCollision->SetPosition({ -125, });
			}
		}

		WeaponRender->SetScale(GetWeaponRenderScale());
		WeaponCollision->SetScale(GetWeaponCollisionScale());

		WeaponRender->On();
		WeaponCollision->On();
	}
	WaitTime = 0;
}

void WeaponWhip::Init()
{
	WeaponRender = CreateRender(VSRenderOrder::Weapon);
	WeaponRender->CreateAnimation({ .AnimationName = "Right_Whip",  .ImageName = "RightWhip.bmp", .Start = 0, .End = 5, .InterTime = 0.016f });
	WeaponRender->CreateAnimation({ .AnimationName = "Left_Whip",  .ImageName = "LeftWhip.bmp", .Start = 0, .End = 5, .InterTime = 0.016f });
	WeaponRender->CreateAnimation({ .AnimationName = "Bi_Whip",  .ImageName = "BidiWhip.bmp", .Start = 0, .End = 5, .InterTime = 0.033f });
	WeaponRender->SetScale({ 530,60 });
	//WeaponRender->SetPosition({ 0,0 });
	WeaponRender->ChangeAnimation("Right_Whip");

	WeaponCollision = CreateCollision(VSRenderOrder::Weapon);
	WeaponCollision->SetScale({ 250,50 });
	WeaponCollision->SetPosition({ 125, 0 });
	SetWeaponScale(WeaponRender->GetScale(), WeaponCollision->GetScale());

}



void WeaponWhip::Start()
{
	SetWeaponName("Whip");
	Init();

	SetCoolTime(2.7f);
	SetRunTime(0.1f);
	float _Dmg[9] = { 0.0f,10.0f,10.0f,15.0f,20.0f,25.0f,30.0f,35.0f,40.0f };
	SetDmg(_Dmg);

	//NewWeapon->GetWeaponCollision()->SetScale(CollisionScale);
	Weapon::Weapons[GetWeaponName()] = this;

	this->Off();
}


void WeaponWhip::Update(float _DeltaTime)
{
	if (nullptr == WeaponRender || nullptr == WeaponCollision)
	{
		MsgAssert("무기랜더가 생성되지 않았습니다.");
		return;
	}

	if (WaitTime > GetRunTime())
	{
		WeaponRender->Off();
		WeaponCollision->Off();
		return;
		//this->Off();
	}
	SetPos(Player::MainPlayer->GetPos() + float4{0, -50});

	if (true == WeaponCollision->IsUpdate())
	{
		std::vector<GameEngineCollision*> Collision;
		if (true == WeaponCollision->Collision({ .TargetGroup = static_cast<int>(VSRenderOrder::Monster), .TargetColType = CollisionType::CT_Rect, .ThisColType = CollisionType::CT_Rect }, Collision))
		{
			for (size_t j = 0; j < Collision.size(); j++)
			{
				GameEngineActor* ColActor = Collision[j]->GetActor();
				Monster* ColWeaponActor = dynamic_cast<Monster*> (ColActor);
				ColWeaponActor->Attack(GetDmg(),1);

			}
		}
		if (Collision.size() > 0)
		{
			GameEngineSoundPlayer Dwn = GameEngineResources::GetInst().SoundPlayToControl("EnemyHit.mp3");
			Dwn.Volume(1.0f);
			Dwn.LoopCount(1);
		}
	}
}

