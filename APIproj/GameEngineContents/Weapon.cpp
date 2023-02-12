#include "Weapon.h"
#include <GameEngineCore/GameEngineRender.h>
#include <GameEngineCore/GameEngineCollision.h>
#include "ContentsEnums.h"

std::map<std::string, Weapon*> Weapon::Weapons;

Weapon::Weapon()
{
}

Weapon::~Weapon()
{
}

//void Weapon::SetPos(const float4& _Pos) {
//	//Pos = _Pos;
//	WeaponRender->SetPosition(Pos);
//	WeaponCollision->SetPosition(_Pos);
//}

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


void Weapon::SetRenderOrder(int _Value)
{
	WeaponRender->SetOrder(_Value);
}

void Weapon::SetRenderScale(float4 _Scale)
{
	WeaponRender->SetScale(_Scale);
}

void Weapon::SetCollisionScale(float4 _Scale)
{
	WeaponCollision->SetScale(_Scale);
}

void Weapon::Start()
{
	WeaponRender = CreateRender(VSRenderOrder::Player);
	WeaponCollision = CreateCollision(VSRenderOrder::Player);
	//this->Off();

	//NewWeapon->SetWeaponRender(CreateRender(VSRenderOrder::Player));
	//NewWeapon->SetWeaponCollision(CreateCollision(VSRenderOrder::Player));
	/*WeaponRender->SetScale({ 180,80 });
	WeaponCollision->SetScale({ 180,80 });*/
	//WeaponRender->CreateAnimation({ .AnimationName = "Right_Whip",  .ImageName = "Whip.bmp", .Start = 0, .End = 2, .InterTime = 0.1f });
	//NewWeapon->GetWeaponRender()->CreateAnimation({ .AnimationName = "Right_Whip",  .ImageName = "Whip.bmp", .Start = 0, .End = 2, .InterTime = 0.1f });
	//NewWeapon->GetWeaponRender()->SetScale({ 180,80 });
	//WeaponRender->SetPosition({ 90 , 0 });
	//WeaponCollision->SetPosition({ 90 , 0 });
	//WeaponCollision->SetDebugRenderType(CollisionType::CT_Rect);
	//WeaponRender->ChangeAnimation("Right_Whip");
	//NewWeapon->GetWeaponRender()->SetPosition({ 90 , 0 });
	//NewWeapon->GetWeaponCollision()->SetPosition({ 90 , 0 });
	//NewWeapon->GetWeaponCollision()->SetScale({ 180,20 });
	//NewWeapon->GetWeaponCollision()->SetDebugRenderType(CollisionType::CT_Rect);
}

void Weapon::Update(float _DeltaTime)
{

}

