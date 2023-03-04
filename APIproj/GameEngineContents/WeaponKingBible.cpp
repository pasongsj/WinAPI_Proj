#include "WeaponKingBible.h"
#include "ContentsEnums.h"

#include "Player.h"
#include "Monster.h"

WeaponKingBible::WeaponKingBible()
{
}

WeaponKingBible::~WeaponKingBible()
{
}


void WeaponKingBible::ReSet()
{
	if (0 == WeaponRender.size()) {
		return;
	}
	float4 StandardPos = { 0,-32 };
	float4 WeaponDir = float4{ 0,1 } * WeaponRange;
	for (int i = 0;i < WeaponRender.size();i++)
	{
		WeaponRender[i]->SetPosition(StandardPos + WeaponDir);
		WeaponCollision[i]->SetPosition(StandardPos + WeaponDir);
		WeaponPos[i] = WeaponDir;

		WeaponRender[i]->SetScale(GetWeaponRenderScale());
		WeaponCollision[i]->SetScale(GetWeaponCollisionScale());

		WeaponRender[i]->On();
		WeaponCollision[i]->On();

		WeaponDir.RotaitonZDeg(360.0f / WeaponRender.size());
	}


	WaitTime = 0;
}

void WeaponKingBible::Init()
{
	GameEngineRender* Render = CreateRender(VSRenderOrder::Weapon);
	Render->SetImage("KingBible.bmp");
	Render->SetScaleToImage();

	GameEngineCollision* Collision = CreateCollision(VSRenderOrder::Weapon);
	Collision->SetScale(Render->GetScale());

	WeaponRender.push_back(Render);
	WeaponCollision.push_back(Collision);
	WeaponPos.push_back(float4::Zero);
	SetWeaponScale(Render->GetScale(), Collision->GetScale());

}



void WeaponKingBible::Start()
{
	SetWeaponName("KingBible");
	Init();

	SetCoolTime(6.0f);
	SetRunTime(3.0f);
	float _Dmg[9] = { 0.0f,10.0f,10.0f,10.0f,20.0f,20.0f,20.0f,30.0f,30.0f };
	SetDmg(_Dmg);
	SetWeaponSpeed(200.0f);

	Weapon::Weapons[GetWeaponName()] = this;

	this->Off();
}


void WeaponKingBible::Update(float _DeltaTime)
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

	SetPos(Player::MainPlayer->GetPos());

	for (int i = 0;i < WeaponRender.size();++i)
	{
		WeaponPos[i].RotaitonZDeg(GetWeaponSpeed() * _DeltaTime);
		WeaponRender[i]->SetPosition(StandardPos + WeaponPos[i]);
		WeaponCollision[i]->SetPosition(StandardPos + WeaponPos[i]);

		std::vector<GameEngineCollision*> Collision;
		if (true == WeaponCollision[i]->Collision({ .TargetGroup = static_cast<int>(VSRenderOrder::Monster), .ThisColType = CollisionType::CT_Rect }, Collision))
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

