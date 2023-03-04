#include "WeaponRuneTracer.h"
#include "ContentsEnums.h"
#include "Player.h"
#include <GameEngineCore/GameEngineLevel.h>
#include <GameEngineBase/GameEngineRandom.h>

#include "Monster.h"

WeaponRuneTracer::WeaponRuneTracer()
{
}

WeaponRuneTracer::~WeaponRuneTracer()
{
}



void WeaponRuneTracer::SetWeaponDir()
{
	std::vector<float4> _Dir;
	_Dir.clear();

	for (int i = 0;i < WeaponRender.size();i++) { // 0,0이 나오면 ..?
		WeaponDir[i] = float4{ GameEngineRandom::MainRandom.RandomFloat(-1.0f, 1.0f) ,GameEngineRandom::MainRandom.RandomFloat(-1.0f, 1.0f) }.GetNormalize();
	}

}



void WeaponRuneTracer::ReSet()
{
	if (0 == WeaponRender.size()) {
		return;
	}
	float4 _Pos = Player::MainPlayer->GetPos();
	_Pos.y -= 32;
	SetPos(_Pos);


	for (int i = 0;i < WeaponRender.size();++i)
	{
		WeaponRender[i]->SetPosition(float4::Zero);
		WeaponCollision[i]->SetPosition(float4::Zero);

		WeaponRender[i]->SetScale(GetWeaponRenderScale());
		WeaponCollision[i]->SetScale(GetWeaponCollisionScale());

		WeaponRender[i]->On();
		WeaponCollision[i]->On();
	}
	SetWeaponDir();

	WaitTime = 0;
}



void WeaponRuneTracer::Init()
{
	{
		GameEngineRender* Render = CreateRender(VSRenderOrder::Weapon);
		Render->SetImage("RuneTracer.bmp");
		Render->SetScaleToImage();

		GameEngineCollision* Collision = CreateCollision(VSRenderOrder::Weapon);
		Collision->SetScale((Render->GetScale())*0.7f);

		WeaponRender.push_back(Render);
		WeaponCollision.push_back(Collision);
		WeaponDir.push_back(float4::Zero);
		SetWeaponScale(Render->GetScale(), Collision->GetScale());
	}
}

void WeaponRuneTracer::Start()
{
	SetWeaponName("RuneTracer");
	Init();


	SetCoolTime(3.0f);
	SetRunTime(2.25f);
	float _Dmg[9] = { 0.0f,10.0f,15.0f,20.0f,20.0f,25.0f,30.0f,30.0f,30.0f };
	SetDmg(_Dmg);
	SetWeaponSpeed(1000.0f);

	Weapon::Weapons[GetWeaponName()] = this;

	this->Off();
}


float4 WeaponRuneTracer::CheckNextPos(const float4& _Pos, const float4& _Dir)
{
	//float4 NextDir = _Dir;
	CollisionData Screen = { Player::MainPlayer->GetPos() , GameEngineWindow::GetScreenSize() };
	// PlayerPos
	float4 NextDir[4] = { _Dir,{_Dir.y,-_Dir.x},-_Dir, {-_Dir.y,_Dir.x} };
	for (int i = 0;i < 4;++i)
	{
		float4 NextPos = _Pos + NextDir[i];
		if (Screen.Bot() > NextPos.y && Screen.Top() < NextPos.y && Screen.Left() < NextPos.x && Screen.Right() > NextPos.x)
		{
			if (0 != i) {
				return NextDir[i] * 10;
			}
			return NextDir[i];
		}
	}
	return float4::Zero;
}

void WeaponRuneTracer::Update(float _DeltaTime)
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


	for (int i = 0;i < WeaponRender.size();++i)
	{
		WeaponDir[i] = CheckNextPos(GetPos() + WeaponRender[i]->GetPosition(),WeaponDir[i] * _DeltaTime * GetWeaponSpeed()).GetNormalize();
		WeaponRender[i]->SetMove(WeaponDir[i] * _DeltaTime * GetWeaponSpeed());
		WeaponCollision[i]->SetMove(WeaponDir[i] * _DeltaTime * GetWeaponSpeed());

		std::vector<GameEngineCollision*> Collision;
		if (true == WeaponCollision[i]->Collision({ .TargetGroup = static_cast<int>(VSRenderOrder::Monster), .ThisColType = CollisionType::CT_CirCle }, Collision))
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
