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
	if (0 == WeaponRender.size()) {
		return;
	}
	else {
		for (int i = 0;i < WeaponRender.size();++i)
		{
			WeaponRender[i]->SetPosition(float4::Zero);
			WeaponCollision[i]->SetPosition(float4::Zero);
			Passes[i] = 1;

			WeaponRender[i]->On();
			WeaponCollision[i]->On();
			WeaponDir[i] = (Player::MainPlayer->GetMoveVec()).GetNormalize();

			if (float4::Zero == WeaponDir[i])
			{
				if ("RIght_" == Player::MainPlayer->GetDirString())
				{
					WeaponDir[i] = { 1,0 };
				}
				else
				{
					WeaponDir[i] = { -1,0 };
				}
			}
		}
	}
	WaitTime = 0;

}


void WeaponKnife::Start() 
{
	SetWeaponName("Knife");
	{
		GameEngineRender* Render = CreateRender(VSRenderOrder::Weapon);
		Render->SetImage("Knife.bmp");
		Render->SetScaleToImage();
		//Render->SetRotFilter("MagicWandBlack.bmp");

		GameEngineCollision* Collision = CreateCollision(VSRenderOrder::Weapon);
		Collision->SetScale({ 25,25 });

		WeaponRender.push_back(Render);
		WeaponCollision.push_back(Collision);
		WeaponDir.push_back(float4::Zero);
		Passes.push_back(1);

	}

	SetCoolTime(1.0f);
	SetRunTime(0.9f);
	float _Dmg[9] = { 0,6.5f,6.5f,11.5f,11.5f,11.5f,11.5f, 16.5f, 16.5f };
	SetDmg(_Dmg);

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
		//this->Off();
	}

	for (int i = 0;i < WeaponRender.size();++i)
	{
		WeaponRender[i]->SetMove(WeaponDir[i] * _DeltaTime * 800);
		WeaponCollision[i]->SetMove(WeaponDir[i] * _DeltaTime * 800);

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
