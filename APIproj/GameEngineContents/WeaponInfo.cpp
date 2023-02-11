#include "WeaponInfo.h"
#include <GameEngineBase/GameEngineDebug.h>
#include <GameEngineCore/GameEngineRender.h>
#include <GameEngineCore/GameEngineCollision.h>


WeaponInfo::WeaponInfo()
{
}

WeaponInfo::~WeaponInfo()
{
}

void WeaponInfo::Start()
{
	WeaponRender = CreateRender();
	WeaponCollision = CreateCollision();
}


void WeaponInfo::CreateWeapon(const std::string_view& _WeaponName)
{
	if (Infos.end() != Infos.find(_WeaponName.data()))
	{
		MsgAssert("이미 등록된 무기입니다.");
		return;
	}

	WeaponInfo* NewWeapon = new WeaponInfo();
	Infos[_WeaponName.data()] = NewWeapon;

}

void WeaponInfo::SetImage(std::string_view& _Image) {
	WeaponRender->SetImage(_Image);
}

void WeaponInfo::Update(float _DeltaTime)
{

}

void WeaponInfo::SetScale(const float4& _Scale)
{
	Scale = _Scale;
	WeaponRender->SetScale(Scale);
	WeaponCollision->SetScale(Scale);
}