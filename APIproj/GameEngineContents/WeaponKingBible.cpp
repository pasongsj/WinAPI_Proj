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

void WeaponKingBible::LevelUp()
{
	Weapon::LevelUp();
	if (2 == GetWeaponLevel() || 8 == GetWeaponLevel()) //발사체를 1개 더 발사합니다.
	{
		SetWeaponCount(GetOriginWeaponCount() + 1);
	}
	else if (3 == GetWeaponLevel() || 6 == GetWeaponLevel()) //기본 속도가 30% 증가합니다. 기본 면적이 25% 증가했습니다.
	{
		SetWeaponSpeed(GetOriginWeaponSpeed() * 1.3f);
		SetWeaponScale(GetOriginRenderScale(), GetOriginCollisionScale());
		WeaponRange *= 1.25f;
	}
	else if (4 == GetWeaponLevel() || 7 == GetWeaponLevel()) //효과가 0.5초 더 오래 지속됩니다. 기본 데미지가 10 증가합니다.
	{
		SetRunTime(GetRunTime() + 0.5f);
	}
	if (8 == GetWeaponLevel())
	{
		AdditionItemUI::DeleteItemName.push_back(GetWeaponName());
	}



}

void WeaponKingBible::ReSet()
{
	if (0 == WeaponRender.size()) {
		return;
	}
	float4 StandardPos = { 0,-32 };
	float4 WeaponDir = float4{ 0,1 } * WeaponRange;

	while (WeaponRender.size() < GetWeaponCount())
	{
		Init();
	}
	for (int i = 0;i < WeaponRender.size();i++)
	{
		WeaponRender[i]->SetPosition(StandardPos + WeaponDir);
		WeaponCollision[i]->SetPosition(StandardPos + WeaponDir);
		WeaponPos[i] = WeaponDir;

		WeaponRender[i]->SetScale(GetOriginRenderScale());
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
	if (GetOriginCollisionScale() == float4::Zero)
	{
		SetWeaponScale(Render->GetScale(), Collision->GetScale());
	}
	int a = 0;



}



void WeaponKingBible::Start()
{
	SetWeaponName("KingBible");

	SetWeaponCount(1);
	SetCoolTime(3.0f);
	SetRunTime(1.7f);
	float _Dmg[9] = { 0.0f,10.0f,10.0f,10.0f,20.0f,20.0f,20.0f,30.0f,30.0f };
	SetDmg(_Dmg);
	SetWeaponSpeed(200.0f);

	Weapon::Weapons[GetWeaponName()] = this;
	for (int i = 0;i < GetWeaponCount();i++)
	{
		Init();
	}

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
		if (true == WeaponCollision[i]->Collision({ .TargetGroup = static_cast<int>(VSRenderOrder::Monster), .TargetColType = CollisionType::CT_Rect, .ThisColType = CollisionType::CT_Rect }, Collision))
		{

			for (size_t j = 0; j < Collision.size(); j++)
			{
				GameEngineActor* ColActor = Collision[j]->GetActor();
				Monster* ColWeaponActor = dynamic_cast<Monster*> (ColActor);
				ColWeaponActor->Attack(GetDmg());

			}
		}
		/*if (Collision.size() > 0)
		{
			GameEngineSoundPlayer Dwn = GameEngineResources::GetInst().SoundPlayToControl("EnemyHit.mp3");
			Dwn.Volume(1.0f);
			Dwn.LoopCount(1);
		}*/
	}
}

