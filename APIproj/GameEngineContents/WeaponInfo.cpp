#include "WeaponInfo.h"
#include <GameEngineBase/GameEngineDebug.h>

WeaponInfo::WeaponInfo()
{
}

WeaponInfo::~WeaponInfo()
{
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