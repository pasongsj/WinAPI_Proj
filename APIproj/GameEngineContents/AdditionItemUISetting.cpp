#include "AdditionItemUI.h"
#include "AdditionItemUIButtonFunction.h"

void AdditionItemUI::SetItemImage()
{
	{
		ItemNames["Bracer"] = "LevelupBracer.bmp";
		ItemNames["Candle"] = "LevelupCandle.bmp";
		ItemNames["Clover"] = "LevelupClover.bmp";
		ItemNames["Emptytome"] = "LevelupEmptytome.bmp";
		ItemNames["Firewand"] = "LevelupFirewand.bmp";


		ItemNames["Hp"] = "LevelupHp.bmp";
		ItemNames["KingBible"] = "LevelupKingBible.bmp";
		ItemNames["Knife"] = "LevelupKnife.bmp";
		ItemNames["Magicwand"] = "LevelupMagicwand.bmp";
		ItemNames["Magnet"] = "LevelupMagnet.bmp";


		ItemNames["Money"] = "LevelupMoney.bmp";
		ItemNames["Whip"] = "LevelupWhip.bmp";
		ItemNames["Runetracer"] = "LevelupRunetracer.bmp";
		ItemNames["Spinach"] = "LevelupSpinach.bmp";
		ItemNames["Wing"] = "LevelupWing.bmp";


		ItemNames["Duplicator"] = "LevelUpDuplicator.bmp";
		ItemNames["Pummarola"] = "LevelUpPummarola.bmp";
		ItemNames["Spellbinder"] = "LevelUpSpellbinder.bmp";
		ItemNames["Crown"] = "LevelUpCrown.bmp";
		ItemNames["HollowHeart"] = "LevelUpHollowHeart.bmp";
		ItemNames["Armor"] = "LevelUpArmor.bmp";

	}

}

void AdditionItemUI::SetItemFunction()
{
	std::map<std::string, Button*>::iterator itemiter = Items.begin();

	{
		itemiter++->second->SetClickCallBack(PushLevelupArmor);
		itemiter++->second->SetClickCallBack(PushLevelupBracer);
		itemiter++->second->SetClickCallBack(PushLevelupCandle);
		itemiter++->second->SetClickCallBack(PushLevelupClover);
		itemiter++->second->SetClickCallBack(PushLevelupCrown);


		itemiter++->second->SetClickCallBack(PushLevelupDuplicator);
		itemiter++->second->SetClickCallBack(PushLevelupEmptytome);
		itemiter++->second->SetClickCallBack(PushLevelupFirewand);
		itemiter++->second->SetClickCallBack(PushLevelupHollowHeart);
		itemiter++->second->SetClickCallBack(PushLevelupHp);


		itemiter++->second->SetClickCallBack(PushLevelupKingBible);
		itemiter++->second->SetClickCallBack(PushLevelupKnife);
		itemiter++->second->SetClickCallBack(PushLevelupMagicwand);
		itemiter++->second->SetClickCallBack(PushLevelupMagnet);
		itemiter++->second->SetClickCallBack(PushLevelupMoney);


		itemiter++->second->SetClickCallBack(PushLevelupPummarola);
		itemiter++->second->SetClickCallBack(PushLevelupRunetracer);
		itemiter++->second->SetClickCallBack(PushLevelupSpellbinder);
		itemiter++->second->SetClickCallBack(PushLevelupSpinach);
		itemiter++->second->SetClickCallBack(PushLevelupWhip);
		itemiter++->second->SetClickCallBack(PushLevelupWing);
	}

}