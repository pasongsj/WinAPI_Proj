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
		MsgAssert("�̹� ��ϵ� �����Դϴ�.");
		return;
	}
	WeaponInfo* NewWeapon = new WeaponInfo();
	Infos[_WeaponName.data()] = NewWeapon;

}