#include "WeaponMagicWand.h"
#include "ContentsEnums.h"
#include "Player.h"
#include <GameEngineCore/GameEngineLevel.h>
#include <GameEngineBase/GameEngineRandom.h>

#include "Monster.h"
WeaponMagicWand::WeaponMagicWand()
{
}

WeaponMagicWand::~WeaponMagicWand()
{
}

void WeaponMagicWand::ReSet()
{
	//Passes = 1;
	//WaitTime = 0;
	float4 _Pos = Player::MainPlayer->GetPos();
	_Pos.y -= 32;
	SetPos(_Pos);
	//WepaonDir = float4::Zero;
	//this->On();
	if (0 == WeaponRender.size()) {
		return;
	}
	else {
		for (int i = 0;i < WeaponRender.size();++i)
		{
			WeaponRender[i]->SetPosition(float4::Zero);
			WeaponCollision[i]->SetPosition(float4::Zero);
			Passes[i] = 1;
		//	WeaponRender[i]->SetAngle(105);
			WeaponRender[i]->On();
			WeaponCollision[i]->On();
		}
		SetWeaponDir();
	}
	WaitTime = 0;
}

void WeaponMagicWand::SetWeaponDir()
{
	std::vector<float4> _Dir;
	_Dir.clear();
	float MinLen = static_cast<float>(3.40282e+38); // float최댓값 3.402823466 E + 38
	std::vector<GameEngineActor*> _Monsters = GetLevel()->GetActors(VSRenderOrder::Monster);
	for (GameEngineActor* _Monster : _Monsters)
	{
		float4 Diff = (_Monster->GetPos() - GetPos());
		if (MinLen > Diff.Size()) {
			MinLen = Diff.Size();
			_Dir.push_back(Diff.GetNormalize());
		}
	}
	for (int i = 0;i < WeaponRender.size();i++) {
		if (_Dir.size() > 0 && _Dir.size() - i - 1 >= 0) {
			WeaponDir[i] = _Dir[_Dir.size() -1 - i];
			
		}
		else
		{
			WeaponDir[i] = float4{ GameEngineRandom::MainRandom.RandomFloat(-1.0f, 1.0f) ,GameEngineRandom::MainRandom.RandomFloat(-1.0f, 1.0f) }.GetNormalize();
		}
		WeaponRender[i]->SetAngle(108);
		float _Deg = float4{ 1, 0 }.GetAngelBetweenVec(WeaponDir[i]);
		//WeaponRender[i]->SetAngleAdd(_Deg);
		if (WeaponDir[i].x >= 0 && WeaponDir[i].y >= 0) // 4사분면
		{
			WeaponRender[i]->SetAngleAdd(_Deg);
		}
		else if (WeaponDir[i].x <= 0 && WeaponDir[i].y >= 0) {//3사분면
			WeaponRender[i]->SetAngleAdd(_Deg-90);
		}
		else if (WeaponDir[i].x <= 0 && WeaponDir[i].y <= 0) { //2사분면
			WeaponRender[i]->SetAngleAdd(360-_Deg);
		}
		else
		{
			WeaponRender[i]->SetAngleAdd(360 -_Deg); //1사분면
		}
	}

}

void WeaponMagicWand::Start()
{
	SetWeaponName("MagicWand");
	{
		GameEngineRender* Render = CreateRender(VSRenderOrder::Weapon);
		Render->SetImage("MagicWand.bmp");
		Render->SetScaleToImage();
		Render->SetRotFilter("MagicWandBlack.bmp");
		//Render->SetAngle(105); // {1,0}

		GameEngineCollision* Collision = CreateCollision(VSRenderOrder::Weapon);
		Collision->SetScale({ 25,25 });

		WeaponRender.push_back(Render);
		WeaponCollision.push_back(Collision);
		WeaponDir.push_back(float4::Zero);
		Passes.push_back(1);

	}
	/*WeaponRender = CreateRender(VSRenderOrder::Weapon);
	WeaponCollision = CreateCollision(VSRenderOrder::Weapon);

	WeaponRender->SetImage("MagicWand.bmp");
	WeaponRender->SetScaleToImage();


	float4 CollisionScale = WeaponRender->GetScale();
	WeaponCollision->SetScale({25,25});*/

	SetCoolTime(1.2f);
	SetRunTime(1.0f);
	int _Dmg[9] = { 0,10,10,10,10,20,20,20,30 };
	SetDmg(_Dmg);

	Weapon::Weapons[GetWeaponName()] = this;

	//this->Off();
}

void WeaponMagicWand::Update(float _DeltaTime)
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

	//if (float4::Zero == WepaonDir)
	//{
	//	float MinLen = static_cast<float>(3.40282e+38); // float최댓값 3.402823466 E + 38
	//	std::vector<GameEngineActor*> _Monsters = GetLevel()->GetActors(VSRenderOrder::Monster);
	//	for (GameEngineActor* _Monster : _Monsters)
	//	{
	//		float4 Diff = (_Monster->GetPos() - GetPos());
	//		if (MinLen > Diff.Size()) {
	//			MinLen = Diff.Size();
	//			WepaonDir = (Diff.Normalize());
	//		}
	//	}
	//	if (0 == _Monsters.size())
	//	{
	//		WepaonDir = { GameEngineRandom::MainRandom.RandomFloat(-1.0f, 1.0f) ,GameEngineRandom::MainRandom.RandomFloat(-1.0f, 1.0f) };// 랜덤으로 설정해줘야합니다.
	//		WepaonDir.Normalize();
	//	}
	//}

	for (int i = 0;i < WeaponRender.size();++i)
	{
		WeaponRender[i]->SetMove(WeaponDir[i] * _DeltaTime * 600);
		WeaponCollision[i]->SetMove(WeaponDir[i] * _DeltaTime * 600);

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
