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
	//this->On();
	if (0 == WeaponRender.size()) {
		return;
	}
	else {
		LastDir = Player::MainPlayer->GetDirString();
		WeaponRender[LastDir]->On();
		WeaponCollision[LastDir]->On();
	}
	WaitTime = 0;
}

void WeaponWhip::Init()
{
	{
		GameEngineRender* Render = CreateRender(VSRenderOrder::Weapon);
		Render->CreateAnimation({ .AnimationName = "Right_Whip",  .ImageName = "RightWhip.bmp", .Start = 0, .End = 5, .InterTime = 0.02f });
		Render->SetScale({ 600,60 });
		Render->SetPosition({ 0, -60 });
		Render->ChangeAnimation("Right_Whip");

		GameEngineCollision* Collision = CreateCollision(VSRenderOrder::Weapon);
		float4 CollisionScale = Render->GetScale();
		CollisionScale.x = CollisionScale.hx();
		Collision->SetScale(CollisionScale);
		Collision->SetPosition({ Collision->GetScale().hx(),-Collision->GetScale().y });
		WeaponRender["Right_"] = Render;
		WeaponCollision["Right_"] = Collision;
		WeaponRender["Right_"]->Off();
		WeaponCollision["Right_"]->Off();
	}
	{
		GameEngineRender* Render = CreateRender(VSRenderOrder::Weapon);
		Render->CreateAnimation({ .AnimationName = "Left_Whip",  .ImageName = "LeftWhip.bmp", .Start = 0, .End = 5, .InterTime = 0.02f });
		Render->SetScale({ 600,60 });
		Render->SetPosition({ 0, -60 });
		Render->ChangeAnimation("Left_Whip");

		GameEngineCollision* Collision = CreateCollision(VSRenderOrder::Weapon);
		float4 CollisionScale = Render->GetScale();
		CollisionScale.x = CollisionScale.hx();
		Collision->SetScale(CollisionScale);
		Collision->SetPosition({ -Collision->GetScale().hx(),-Collision->GetScale().y });
		WeaponRender["Left_"] = Render;
		WeaponCollision["Left_"] = Collision;
		WeaponRender["Left_"]->Off();
		WeaponCollision["Left_"]->Off();
	}
}



void WeaponWhip::Start()
{
	SetWeaponName("Whip");
	Init();
	/*{
		GameEngineRender* Render = CreateRender(VSRenderOrder::Weapon);
		Render->CreateAnimation({ .AnimationName = "Right_Whip",  .ImageName = "RightWhip.bmp", .Start = 0, .End = 5, .InterTime = 0.02f });
		Render->SetScale({ 600,60 });
		Render->SetPosition({ 0, -60 });
		Render->ChangeAnimation("Right_Whip");

		GameEngineCollision* Collision = CreateCollision(VSRenderOrder::Weapon);
		float4 CollisionScale = Render->GetScale();
		CollisionScale.x = CollisionScale.hx();
		Collision->SetScale(CollisionScale);
		Collision->SetPosition({ Collision->GetScale().hx(),-Collision->GetScale().y });
		WeaponRender["Right_"] = Render;
		WeaponCollision["Right_"] = Collision;
		WeaponRender["Right_"]->Off();
		WeaponCollision["Right_"]->Off();
	}
	{
		GameEngineRender* Render = CreateRender(VSRenderOrder::Weapon);
		Render->CreateAnimation({ .AnimationName = "Left_Whip",  .ImageName = "LeftWhip.bmp", .Start = 0, .End = 5, .InterTime = 0.02f });
		Render->SetScale({ 600,60 });
		Render->SetPosition({ 0, -60 });
		Render->ChangeAnimation("Left_Whip");

		GameEngineCollision* Collision = CreateCollision(VSRenderOrder::Weapon);
		float4 CollisionScale = Render->GetScale();
		CollisionScale.x = CollisionScale.hx();
		Collision->SetScale(CollisionScale);
		Collision->SetPosition({ -Collision->GetScale().hx(),-Collision->GetScale().y });
		WeaponRender["Left_"] = Render;
		WeaponCollision["Left_"] = Collision;
		WeaponRender["Left_"]->Off();
		WeaponCollision["Left_"]->Off();
	}*/

	//WeaponRender = CreateRender(VSRenderOrder::Weapon);
	//WeaponCollision = CreateCollision(VSRenderOrder::Weapon);

	////Weapon* NewWeapon = _Level->CreateActor<Weapon>(VSRenderOrder::Weapon);
	//SetWeaponName("Whip");
	//
	//WeaponRender->CreateAnimation({ .AnimationName = "Right_Whip",  .ImageName = "RightWhip.bmp", .Start = 0, .End = 5, .InterTime = 0.02f });
	//WeaponRender->CreateAnimation({ .AnimationName = "Left_Whip",  .ImageName = "LeftWhip.bmp", .Start = 0, .End = 5, .InterTime = 0.02f });
	//WeaponRender->CreateAnimation({ .AnimationName = "Bidi_Whip",  .ImageName = "BidiWhip.bmp", .Start = 0, .End = 5, .InterTime = 0.02f });
	//WeaponRender->SetScale({ 600,60 });
	//WeaponRender->SetPosition({ 0, -60 });

	//float4 CollisionScale = WeaponRender->GetScale();
	//CollisionScale.x = CollisionScale.hx();
	//WeaponCollision->SetScale(CollisionScale);

	SetCoolTime(2.0f);
	SetRunTime(0.1f);
	float _Dmg[9] = { 0.0f,10.0f,10.0f,15.0f,20.0f,25.0f,30.0f,35.0f,40.0f };
	SetDmg(_Dmg);

	//NewWeapon->GetWeaponCollision()->SetScale(CollisionScale);
	Weapon::Weapons[GetWeaponName()] = this;

	this->Off();
}


void WeaponWhip::Update(float _DeltaTime)
{
	if (WeaponRender.size() == 0 || WeaponCollision.size() == 0)
	{
		MsgAssert("무기랜더가 생성되지 않았습니다.");
		return;
	}

	if (WaitTime > GetRunTime())
	{
		WeaponRender[LastDir]->Off();
		WeaponCollision[LastDir]->Off();
		return;
		//this->Off();
	}
	SetPos(Player::MainPlayer->GetPos());

	/*std::map<std::string, GameEngineCollision*>::iterator ColBegin = WeaponCollision.begin();
	std::map<std::string, GameEngineCollision*>::iterator ColEnd = WeaponCollision.end();
	for (;ColBegin != ColEnd;ColBegin++)
	{
		if (true == ColBegin->second->IsUpdate())
		{
			std::vector<GameEngineCollision*> Collision;
			if (true == ColBegin->second->Collision({ .TargetGroup = static_cast<int>(VSRenderOrder::Monster), .ThisColType = CollisionType::CT_Rect }, Collision))
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
	}*/
	if (true == WeaponCollision[LastDir]->IsUpdate())
	{
		std::vector<GameEngineCollision*> Collision;
		if (true == WeaponCollision[LastDir]->Collision({ .TargetGroup = static_cast<int>(VSRenderOrder::Monster), .ThisColType = CollisionType::CT_Rect }, Collision))
		{
			for (size_t i = 0; i < Collision.size(); i++)
			{
				GameEngineActor* ColActor = Collision[i]->GetActor();
				Monster* ColWeaponActor = dynamic_cast<Monster*> (ColActor);
				ColWeaponActor->Attack(GetDmg());

			}
		}
	}
}

