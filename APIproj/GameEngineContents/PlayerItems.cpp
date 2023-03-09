#include "Player.h"
#include "AdditionItemUI.h"
#include <vector>
#include <GameEngineCore/GameEngineLevel.h>
#include "ContentsEnums.h"
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
		(*it)->LevelUp();

	}
}



//0MaxHealth
//1Recovery
//2Armor
//3ActiveSpeed
//
//4Might
//5Area
//6Speed
//7Duration
//8Amount
//9Cooldown
//
//10Luck
//11Growth
//12Greed
//
//13Magnet
//
//14Revival
//15Reroll
//16Skip

void Player::PushActive(const std::string_view& _Active)
{
	int NextLevel = 0;

	float PercValue[6] = { 100,110,120,130,140,150 };
	if ("Bracer" == _Active)
	{
		PlayerActive.Speed = PercValue[++PlayerActiveLevel.LevelBracer];
		NextLevel = PlayerActiveLevel.LevelBracer;
		AdditionItemUI::SelectUI->SetActiveStatUIValue(6, static_cast<int>(PlayerActive.Speed - 100));
	}
	else if ("Candle" == _Active)
	{
		PlayerActive.Area = PercValue[++PlayerActiveLevel.LevelCandle];
		NextLevel = PlayerActiveLevel.LevelCandle;
		AdditionItemUI::SelectUI->SetActiveStatUIValue(5, static_cast<int>(PlayerActive.Area - 100));
	}
	else if ("Clover" == _Active)
	{
		PlayerActive.Luck = PercValue[++PlayerActiveLevel.LevelClover];
		NextLevel = PlayerActiveLevel.LevelClover;
		AdditionItemUI::SelectUI->SetActiveStatUIValue(10, static_cast<int>(PlayerActive.Luck - 100));
	}
	else if ("Emptytome" == _Active)
	{
		float Value[6] = { 100,92,88,80,72,68 };
		PlayerActive.Cooldown = Value[++PlayerActiveLevel.LevelEmptytome];
		NextLevel = PlayerActiveLevel.LevelEmptytome;
		AdditionItemUI::SelectUI->SetActiveStatUIValue(9, static_cast<int>(PlayerActive.Cooldown)-100); // minus img
	}
	else if ("Hp" == _Active)
	{
		GetHp(30.0f);
	}
	else if ("Magnet" == _Active)
	{
		int Value[6] = { 0,10,20,30,40,50 };
		PlayerActive.Magnet = Value[++PlayerActiveLevel.LevelMagnet];
		NextLevel = PlayerActiveLevel.LevelMagnet;
		AdditionItemUI::SelectUI->SetActiveStatUIValue(13, PlayerActive.Magnet);
	}
	else if ("Money" == _Active)
	{

	}
	else if ("Spinach" == _Active)
	{
		PlayerActive.Might = PercValue[++PlayerActiveLevel.LevelSpinach];
		NextLevel = PlayerActiveLevel.LevelSpinach;
		AdditionItemUI::SelectUI->SetActiveStatUIValue(4, static_cast<int>(PlayerActive.Might - 100));

	}
	else if ("Wing" == _Active)
	{
		PlayerActive.ActiveSpeed = PercValue[++PlayerActiveLevel.LevelWing];
		NextLevel = PlayerActiveLevel.LevelWing;
		AdditionItemUI::SelectUI->SetActiveStatUIValue(3, static_cast<int>(PlayerActive.ActiveSpeed - 100));
	}
	else if ("Duplicator" == _Active)
	{
		int Value[6] = { 0,1,2 };
		PlayerActive.Amount = Value[++PlayerActiveLevel.LevelDuplicator];
		NextLevel = PlayerActiveLevel.LevelDuplicator + 3;
		AdditionItemUI::SelectUI->SetActiveStatUIValue(8, PlayerActive.Amount);
	}
	else if ("Pummarola" == _Active)
	{
		float Value[6] = { 0,0.2f,0.4f,0.6f,0.8f,1.0f };
		PlayerActive.Recovery = Value[++PlayerActiveLevel.LevelPummarola];
		NextLevel = PlayerActiveLevel.LevelPummarola;
		float _Value = PlayerActive.Recovery < 1 ? PlayerActive.Recovery * 10 : PlayerActive.Recovery;
		AdditionItemUI::SelectUI->SetActiveStatUIValue(1, static_cast<int>(_Value));// 소수점
	}
	else if ("Spellbinder" == _Active)
	{
		PlayerActive.Duration = PercValue[++PlayerActiveLevel.LevelSpellbinder];
		NextLevel = PlayerActiveLevel.LevelSpellbinder;
		AdditionItemUI::SelectUI->SetActiveStatUIValue(7, static_cast<int>(PlayerActive.Duration) - 100);
	}
	else if ("Crown" == _Active)
	{
		float Value[6] = { 0, 8,16,24,32,40 };
		PlayerActive.Growth = Value[++PlayerActiveLevel.LevelCrown];
		if (PlayerName == "Imelda")
		{
			PlayerActive.Growth += 10;
		}
		NextLevel = PlayerActiveLevel.LevelCrown;
		AdditionItemUI::SelectUI->SetActiveStatUIValue(11, static_cast<int>(PlayerActive.Growth));// 소수점
	}
	else if ("HollowHeart" == _Active)
	{
		float Value[6] = { 0, 1.2f, 1.44f,1.728f ,2.0736f, 2.48832f };
		float BeforeMax = PlayerActive.MaxHealth;
		if (PlayerName == "Antonio")
		{
			PlayerActive.MaxHealth = 120.0f * Value[++PlayerActiveLevel.LevelHollowHeart];
		}
		else
		{
			PlayerActive.MaxHealth = 100.0f * Value[++PlayerActiveLevel.LevelHollowHeart];
		}
		NextLevel = PlayerActiveLevel.LevelHollowHeart;
		float AfterMax = PlayerActive.MaxHealth;
		Hp += (AfterMax - BeforeMax);


		AdditionItemUI::SelectUI->SetActiveStatUIValue(0, static_cast<int>(PlayerActive.MaxHealth));

	}
	else if ("Armor" == _Active)
	{
		PlayerActive.Armor = ++PlayerActiveLevel.LevelArmor;
		NextLevel = PlayerActiveLevel.LevelArmor;
		AdditionItemUI::SelectUI->SetActiveStatUIValue(2, static_cast<int>(PlayerActive.Armor));
	}
	if (5 == NextLevel)
	{
		AdditionItemUI::DeleteItemName.push_back(_Active.data());
	}

}