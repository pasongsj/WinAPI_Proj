#include "ItemIcon.h"
#include "Player.h"
#include "ContentsEnums.h"

ItemIcon::ItemIcon()
{
}

ItemIcon::~ItemIcon()
{
}

void ItemIcon::Start()
{
	WeaponPos = { 25, 59 };
	ActivePos = { 25, 94 };
}

void ItemIcon::Update(float _DeltaTime)
{
	std::vector<std::pair<int, std::string>> WeaponList = Player::MainPlayer->GetWeapon();

	for (int i = 0;i < WeaponList.size();++i)
	{
		if (WeaponIconList.end() == WeaponIconList.find(WeaponList[i].second))
		{
			WeaponIconList.insert(WeaponList[i].second);
			GameEngineRender* Render = CreateRender(VSRenderOrder::MAX);
			std::string ImgName = WeaponList[i].second + "Icon.bmp";
			Render->EffectCameraOff();
			Render->SetImage(ImgName);
			Render->SetScale({ 37,37 });
			Render->SetPosition(WeaponPos);
			WeaponIcon.push_back(Render);
			NextWeaponIconPos();
		}
	}

	ActiveLevel ActiveList = Player::MainPlayer->GetActive();
	_Active["Bracer"] = ActiveList.LevelBracer;
	_Active["Candle"] = ActiveList.LevelCandle;					
	_Active["Clover"] = ActiveList.LevelClover;					
	_Active["Emptytome"] = ActiveList.LevelEmptytome;			
	_Active["Magnet"] = ActiveList.LevelMagnet;					
	_Active["Spinach"] = ActiveList.LevelSpinach;				
	_Active["Wing"] = ActiveList.LevelWing;					
	_Active["Duplicator"] = ActiveList.LevelDuplicator;			
	_Active["Pummarola"] = ActiveList.LevelPummarola;			
	_Active["Spellbinder"] = ActiveList.LevelSpellbinder;		
	_Active["Crown"] = ActiveList.LevelCrown;					
	_Active["HollowHeart"] = ActiveList.LevelHollowHeart;		
	_Active["Armor"] = ActiveList.LevelArmor;
	std::map<std::string, int>::iterator startiter = _Active.begin();
	std::map<std::string, int>::iterator enditer = _Active.end();

	for (;startiter != enditer;++startiter)
	{
		if (startiter->second > 0 && ActiveIconList.end() == ActiveIconList.find(startiter->first))
		{
			ActiveIconList.insert(startiter->first);
			GameEngineRender* Render = CreateRender(VSRenderOrder::MAX);
			std::string ImgName = startiter->first + "Icon.bmp";
			Render->EffectCameraOff();
			Render->SetImage(ImgName);
			Render->SetScale({ 37,37 });
			Render->SetPosition(ActivePos);
			ActiveIcon.push_back(Render);
			NextActiveIconPos();
		}
	}

	//int LevelBracer = 0;
	//int LevelCandle = 0;
	//int LevelClover = 0;
	//int LevelEmptytome = 0;
	//int LevelMagnet = 0;
	//int LevelSpinach = 0;
	//int LevelWing = 0;
	//int LevelDuplicator = 0;
	//int LevelPummarola = 0;
	//int LevelSpellbinder = 0;
	//int LevelCrown = 0;
	//int LevelHollowHeart = 0;
	//int LevelArmor = 0;


}

void ItemIcon::NextWeaponIconPos()
{
	WeaponPos.x += 37;
	int a = 0;
}
void ItemIcon::NextActiveIconPos()
{
	if (ActiveIconList.size() % 6 == 0)
	{
		ActivePos.x = 26;
		ActivePos.y += 35;
	}
	else
	{

		ActivePos.x += 37;
	}
}
