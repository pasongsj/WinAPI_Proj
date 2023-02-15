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

void Weapon::SetWeaponDebugType(CollisionType _Type)
{
	WeaponCollision->SetDebugRenderType(_Type);
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
	
}

