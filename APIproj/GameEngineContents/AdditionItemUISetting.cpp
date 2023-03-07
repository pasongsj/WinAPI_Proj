#include "AdditionItemUI.h"
#include "AdditionItemUIButtonFunction.h"
#include <GameEngineCore/GameEngineLevel.h>
#include <GameEngineBase/GameEngineRandom.h>
#include "ContentsEnums.h"

void AdditionItemUI::SetItemImage()
{
	{
		ItemNames["Bracer"] = "LevelupBracer.bmp";
		ItemNames["Candle"] = "LevelupCandle.bmp";
		ItemNames["Clover"] = "LevelupClover.bmp";
		ItemNames["Emptytome"] = "LevelupEmptytome.bmp";
		ItemNames["FireWand"] = "LevelupFirewand.bmp";


		ItemNames["Hp"] = "LevelupHp.bmp";
		ItemNames["KingBible"] = "LevelupKingBible.bmp";
		ItemNames["Knife"] = "LevelupKnife.bmp";
		ItemNames["MagicWand"] = "LevelupMagicwand.bmp";
		ItemNames["Magnet"] = "LevelupMagnet.bmp";


		ItemNames["Money"] = "LevelupMoney.bmp";
		ItemNames["Whip"] = "LevelupWhip.bmp";
		ItemNames["RuneTracer"] = "LevelupRunetracer.bmp";
		ItemNames["Spinach"] = "LevelupSpinach.bmp";
		ItemNames["Wing"] = "LevelupWing.bmp";


		ItemNames["Duplicator"] = "LevelUpDuplicator.bmp";
		ItemNames["Pummarola"] = "LevelUpPummarola.bmp";
		ItemNames["Spellbinder"] = "LevelUpSpellbinder.bmp";
		ItemNames["Crown"] = "LevelUpCrown.bmp";
		ItemNames["HollowHeart"] = "LevelUpHollowHeart.bmp";
		ItemNames["Armor"] = "LevelUpArmor.bmp";

	}
	{
		for (std::pair<std::string, std::string> _Name : ItemNames)
		{
			Button* NewCharBtn = GetLevel()->CreateActor<Button>(VSRenderOrder::LastUI);
			NewCharBtn->setting(_Name.second, _Name.second, _Name.second, { 0,0 }, BtnScale, static_cast<int>(VSRenderOrder::LastUI), false);
			NewCharBtn->GetButtonRender()->SetImage(_Name.second);
			NewCharBtn->GetButtonRender()->EffectCameraOn();
			Items[_Name.first] = (NewCharBtn);
			NewCharBtn->Off();
		}
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


void AdditionItemUI::ReSet()
{
	ShowedBtn.clear();
	int i = 0;
	while (true)
	{
		if (ShowedBtn.size() == 4 || Items.size() == 0)
		{
			break;
		}
		std::map<std::string, Button*>::iterator iter = Items.begin();
		int ItemIndex = GameEngineRandom::MainRandom.RandomInt(0, static_cast<int>(Items.size()) - 1);
		std::advance(iter, ItemIndex);
		if (Items.size() > 2 && (iter->first == "Money" || iter->first == "Hp"))
		{
			continue;
		}
		Button* Picked = iter->second;
		ShowedBtn.insert(*iter);
		Items.erase(iter);
		Picked->On();


		float4 Cam_Pos = GetLevel()->GetCameraPos() + BtnPos[i++];
		Picked->SetPos(Cam_Pos);

	}

	std::set<std::pair< std::string, Button*>>::iterator startit = ShowedBtn.begin();
	std::set<std::pair< std::string, Button*>>::iterator endit = ShowedBtn.end();

	for (;startit != endit;startit++)
	{
		Items.insert(*startit);
	}

}