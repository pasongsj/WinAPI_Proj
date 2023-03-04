#include "Player.h"
#include "AdditionItemUI.h"
#include <vector>

void Player::PushWeapon(const std::string_view& _Weapon)
{
	std::string WeaponName = _Weapon.data();
	if (Weapon::Weapons.end() == Weapon::Weapons.find(WeaponName))
	{
		MsgAssert(WeaponName + "은 생성되지 않은 무기입니다.");
		return;
	}
	Weapon* _WeaponPointer = Weapon::Weapons[WeaponName];
	std::vector<Weapon*>::iterator it = find(MyWeapon.begin(), MyWeapon.end(), _WeaponPointer);
	if (it == MyWeapon.end()) // 새로 추가하기
	{
		MyWeapon.push_back(_WeaponPointer);
		MyWeapon.back()->On();
		MyWeapon.back()->ReSet();
	}
	else // 레벨업 하기
	{

	}
}

void Player::PushActive(const std::string_view& _Active)
{
	int NextLevel = 0;

	float PercValue[6] = { 100,110,120,130,140,150 };
	if ("Bracer" == _Active)
	{
		PlayerActive.Speed = PercValue[++PlayerActiveLevel.LevelBracer];
		NextLevel = PlayerActiveLevel.LevelBracer;
	}
	else if ("Candle" == _Active)
	{
		PlayerActive.Area = PercValue[++PlayerActiveLevel.LevelCandle];
		NextLevel = PlayerActiveLevel.LevelCandle;
	}
	else if ("Clover" == _Active)
	{
		PlayerActive.Luck = PercValue[++PlayerActiveLevel.LevelClover];
		NextLevel = PlayerActiveLevel.LevelClover;
	}
	else if ("Emptytome" == _Active)
	{
		float Value[6] = { 100,92,88,80,72,68 };
		PlayerActive.Cooldown = Value[++PlayerActiveLevel.LevelEmptytome];
		NextLevel = PlayerActiveLevel.LevelEmptytome;
	}
	else if ("Hp" == _Active)
	{

	}
	else if ("Magnet" == _Active)
	{
		int Value[6] = { 0,10,20,30,40,50 };
		PlayerActive.Magnet = Value[++PlayerActiveLevel.LevelMagnet];
		NextLevel = PlayerActiveLevel.LevelMagnet;
	}
	else if ("Money" == _Active)
	{

	}
	else if ("Spinach" == _Active)
	{
		PlayerActive.Might = PercValue[++PlayerActiveLevel.LevelSpinach];
		NextLevel = PlayerActiveLevel.LevelSpinach;
	}
	else if ("Wing" == _Active)
	{
		PlayerActive.ActiveSpeed = PercValue[++PlayerActiveLevel.LevelWing];
		NextLevel = PlayerActiveLevel.LevelWing;
	}
	else if ("Duplicator" == _Active)
	{
		int Value[6] = { 0,1,2 };
		PlayerActive.Amount = Value[++PlayerActiveLevel.LevelDuplicator];
		NextLevel = PlayerActiveLevel.LevelDuplicator + 3;
	}
	else if ("Pummarola" == _Active)
	{
		float Value[6] = { 0,0.2f,0.4f,0.6f,0.8f,1.0f };
		PlayerActive.Recovery = Value[++PlayerActiveLevel.LevelPummarola];
		NextLevel = PlayerActiveLevel.LevelPummarola;
	}
	else if ("Spellbinder" == _Active)
	{
		PlayerActive.Duration = PercValue[++PlayerActiveLevel.LevelSpellbinder];
		NextLevel = PlayerActiveLevel.LevelSpellbinder;
	}
	else if ("Crown" == _Active)
	{
		float Value[6] = { 0, 8,16,24,32,40 };
		PlayerActive.Growth = Value[++PlayerActiveLevel.LevelCrown];
		NextLevel = PlayerActiveLevel.LevelCrown;
	}
	else if ("HollowHeart" == _Active)
	{
		float Value[6] = { 0, 1.2f, 1.44f,1.728f ,2.0736f, 2.48832f };
		if (PlayerName == "Antonio")
		{
			PlayerActive.MaxHealth = 120.0f * Value[++PlayerActiveLevel.LevelHollowHeart];
		}
		else
		{
			PlayerActive.MaxHealth = 100.0f * Value[++PlayerActiveLevel.LevelHollowHeart];
		}
		NextLevel = PlayerActiveLevel.LevelHollowHeart;

	}
	else if ("Armor" == _Active)
	{
		PlayerActive.Armor = ++PlayerActiveLevel.LevelArmor;
		NextLevel = PlayerActiveLevel.LevelArmor;
	}
	if (5 == NextLevel)
	{
		AdditionItemUI::DeleteItemName.push_back(_Active.data());
	}

}