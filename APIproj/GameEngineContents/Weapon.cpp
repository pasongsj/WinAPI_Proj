#include "Weapon.h"
//#include <GameEngineCore/GameEngineRender.h>
//#include <GameEngineCore/GameEngineCollision.h>
#include "ContentsEnums.h"
#include <GameEngineCore/GameEngineLevel.h>
#include <utility>

#include "Player.h"
std::map<std::string, Weapon*> Weapon::Weapons;

Weapon::Weapon()
{
}

Weapon::~Weapon()
{
}
void Weapon::InitWeapon(GameEngineLevel* _Level)
{

	Weapon* NewWeapon = _Level->CreateActor<Weapon>(VSRenderOrder::Weapon);
	NewWeapon->SetWeaponName("Whip");
	GameEngineRender* Render = NewWeapon->GetWeaponRender();
	if (nullptr == Render)
	{
		MsgAssert("Weapon Render가 생성되지 않았습니다.");
		return;
	}
	Render->CreateAnimation({ .AnimationName = "Right_Whip",  .ImageName = "RightWhip.bmp", .Start = 0, .End = 5, .InterTime = 0.02f});
	Render->CreateAnimation({ .AnimationName = "Left_Whip",  .ImageName = "LeftWhip.bmp", .Start = 0, .End = 5, .InterTime = 0.02f });
	Render->SetScale({ 600,60 });
	Render->SetPosition({ 0, -60 });

	/*NewWeapon->SetImage("RightWhip", "Whip.bmp", 0, 2, 0.03f);
	NewWeapon->SetRenderScale({ 314, 280 });*/
	NewWeapon->SetCollisionScale({ 300, 60 });
	NewWeapon->SetCoolTime(2.0f);
	NewWeapon->SetRunTime(0.1f);
	
	int _Dmg[9] = { 0,5,10,15,20,25,30,35,40 };
	NewWeapon->SetDmg(_Dmg);
	float4 CollisionScale = Render->GetScale();
	CollisionScale.x = CollisionScale.hx();
	NewWeapon->GetWeaponCollision()->SetScale(CollisionScale);
	NewWeapon->SetCollisionPosition({ 0, -15 });
	//NewWeapon->SetWeaponDebugType(CT_Rect);
	Weapon::Weapons["Whip"] = NewWeapon;

	//AnimationRender = CreateRender(VSRenderOrder::Player);
	//AnimationRender->SetScale({ 70, 140 }); // 실제 크기 64 x 64
	//{
	//	AnimationRender->CreateAnimation({ .AnimationName = "Right_Idle",  .ImageName = RightChar }); //RightAntonio.bmp
	//	AnimationRender->CreateAnimation({ .AnimationName = "Right_Move",  .ImageName = RightChar, .Start = 0, .End = 2, .InterTime = 0.1f });
	//}
	//{
	//	AnimationRender->CreateAnimation({ .AnimationName = "Left_Idle",  .ImageName = LeftChar });
	//	AnimationRender->CreateAnimation({ .AnimationName = "Left_Move",  .ImageName = LeftChar, .Start = 0, .End = 2, .InterTime = 0.1f });
	//}

	//{
	//	BodyCollision = CreateCollision(VSRenderOrder::Player);
	//	BodyCollision->SetScale({ 64, 64 });
	//	BodyCollision->SetPosition({ 0, -BodyCollision->GetScale().hy() });
	//}

}

void Weapon::SetImage(const std::string_view& _AnimationName, const std::string_view& _Image, int _Start, int _End , float _InterTime)
{
	if ("" == _Image) {
		MsgAssert("이미지명을 입력하지 않았습니다.");

	}

	if (true == IsAnimation) 
	{
		WeaponRender->CreateAnimation({ .AnimationName = _AnimationName,  .ImageName = _Image, .Start = _Start, .End = _End, .InterTime = _InterTime });
		WeaponRender->ChangeAnimation(_AnimationName);
	}
	else 
	{
		WeaponRender->SetImage(_Image);
	}
}


void Weapon::Start()
{
	WeaponRender = CreateRender(VSRenderOrder::Weapon);
	WeaponCollision = CreateCollision(VSRenderOrder::Weapon);
	this->Off();
}

void Weapon::Update(float _DeltaTime)
{
	if (WaitTime > RunTime)
	{
		this->Off();
	}
	std::string _Animation = Player::MainPlayer->GetDirString() + WeaponName;
	WeaponRender->ChangeAnimation(_Animation);
	
}

