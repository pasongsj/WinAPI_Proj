#include "AdditionItemUI.h"

//#include <set>
#include <GameEngineBase/GameEngineRandom.h>
#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEngineCore/GameEngineLevel.h>
#include <GameEngineCore/NumberRenderObject.h>
#include <GameEngineCore/GameEngineCollision.h>
#include "ContentsEnums.h"
#include "Player.h"


AdditionItemUI* AdditionItemUI::SelectUI;
std::string AdditionItemUI::DeleteItemName = "";

AdditionItemUI::AdditionItemUI()
{
}

AdditionItemUI::~AdditionItemUI()
{
}


void PushLevelupBracer()
{
	Player::MainPlayer->PushActive("Bracer");
	Player::IsStop = false;
}
void PushLevelupCandle()
{
	Player::MainPlayer->PushActive("Candle");
	Player::IsStop = false;
}
void PushLevelupClover()
{
	Player::MainPlayer->PushActive("Clover");
	Player::IsStop = false;
}
void PushLevelupEmptytome()
{
	Player::MainPlayer->PushActive("Emptytome");
	Player::IsStop = false;
}
void PushLevelupFirewand()
{
	Player::MainPlayer->PushWeapon("FireWand");
	Player::IsStop = false;
}
void PushLevelupHp()
{
	//Player::MainPlayer->PushWeapon("Hp");
}
void PushLevelupKingBible()
{
	Player::MainPlayer->PushWeapon("KingBible");
	Player::IsStop = false;
}
void PushLevelupKnife()
{
	Player::MainPlayer->PushWeapon("Knife");
	Player::IsStop = false;
}
void PushLevelupMagicwand()
{
	Player::MainPlayer->PushWeapon("MagicWand");
	Player::IsStop = false;
}
void PushLevelupMagnet()
{
	Player::MainPlayer->PushActive("Magnet");
	Player::IsStop = false;
}
void PushLevelupMoney()
{
	//Player::MainPlayer->PushWeapon("Money");
}
void PushLevelupWhip()
{
	Player::MainPlayer->PushWeapon("Whip");
	Player::IsStop = false;
}
void PushLevelupRunetracer()
{
	Player::MainPlayer->PushWeapon("RuneTracer");
	Player::IsStop = false;
}
void PushLevelupSpinach()
{
	Player::MainPlayer->PushActive("Spinach");
	Player::IsStop = false;
}
void PushLevelupWing()
{
	Player::MainPlayer->PushActive("Wing");
	Player::IsStop = false;
}
void PushLevelupDuplicator()
{
	Player::MainPlayer->PushActive("Duplicator");
	Player::IsStop = false;
}
void PushLevelupPummarola()
{
	Player::MainPlayer->PushActive("Pummarola");
	Player::IsStop = false;
}
void PushLevelupSpellbinder()
{
	Player::MainPlayer->PushActive("Spellbinder");
	Player::IsStop = false;
}
void PushLevelupCrown()
{
	Player::MainPlayer->PushActive("Crown");
	Player::IsStop = false;
}
void PushLevelupHollowHeart()
{
	Player::MainPlayer->PushActive("HollowHeart");
	Player::IsStop = false;
}
void PushLevelupArmor()
{
	Player::MainPlayer->PushActive("Armor");
	Player::IsStop = false;
}


void AdditionItemUI::Start()
{
	SelectUI = this;
	{
		LevelUpUIRender = CreateRender("LevelUpUI.BMP", VSRenderOrder::LastUI);
		LevelUpUIRender->SetScaleToImage();
		LevelUpUIRender->SetPosition(GameEngineWindow::GetScreenSize().half());
		LevelUpUIRender->EffectCameraOff();
	}

	{
		StatUI = CreateRender("StatUI.BMP", VSRenderOrder::LastUI);
		StatUI->SetScaleToImage();
		float4 StatUIPos = StatUI->GetScale().half();
		StatUIPos.y += 30;
		StatUI->SetPosition(StatUIPos);
		StatUI->EffectCameraOff();
	}


	float4 _Pos = GameEngineWindow::GetScreenSize().half();
	_Pos.y -= (BtnScale.y * 1.06f);
	for (int i = 0;i < 4;i++)
	{
		BtnPos.push_back(_Pos);
		_Pos.y += BtnScale.y;
	}
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


	for (std::pair<std::string, std::string> _Name : ItemNames)
	{
		Button* NewCharBtn = GetLevel()->CreateActor<Button>(VSRenderOrder::LastUI);
		NewCharBtn->setting(_Name.second, _Name.second, _Name.second, { 0,0 }, BtnScale, static_cast<int>(VSRenderOrder::LastUI), false);
		NewCharBtn->GetButtonRender()->SetImage(_Name.second);
		NewCharBtn->GetButtonRender()->EffectCameraOn();
		Items[_Name.first] = (NewCharBtn);
		NewCharBtn->Off();
	}



	std::map<std::string, Button*>::iterator itemiter = Items.begin();

	{
		itemiter++->second->SetClickCallBack(PushLevelupArmor		);		
		itemiter++->second->SetClickCallBack(PushLevelupBracer		);		
		itemiter++->second->SetClickCallBack(PushLevelupCandle		);		
		itemiter++->second->SetClickCallBack(PushLevelupClover		);		
		itemiter++->second->SetClickCallBack(PushLevelupCrown		);	
				
				
		itemiter++->second->SetClickCallBack(PushLevelupDuplicator	 );
		itemiter++->second->SetClickCallBack(PushLevelupEmptytome	 );
		itemiter++->second->SetClickCallBack(PushLevelupFirewand	 );
		itemiter++->second->SetClickCallBack(PushLevelupHollowHeart	 );
		itemiter++->second->SetClickCallBack(PushLevelupHp			 );
				
				
		itemiter++->second->SetClickCallBack(PushLevelupKingBible	);
		itemiter++->second->SetClickCallBack(PushLevelupKnife		);
		itemiter++->second->SetClickCallBack(PushLevelupMagicwand	);
		itemiter++->second->SetClickCallBack(PushLevelupMagnet		);
		itemiter++->second->SetClickCallBack(PushLevelupMoney		);
				
				
		itemiter++->second->SetClickCallBack(PushLevelupPummarola	);
		itemiter++->second->SetClickCallBack(PushLevelupRunetracer	);
		itemiter++->second->SetClickCallBack(PushLevelupSpellbinder	);
		itemiter++->second->SetClickCallBack(PushLevelupSpinach		);
		itemiter++->second->SetClickCallBack(PushLevelupWhip		);
		itemiter++->second->SetClickCallBack(PushLevelupWing		);
	}

	int a = 0;


	this->Off();
}


void AdditionItemUI::Update(float _DeltaTime)
{
	if (false == IsReset)
	{
		IsReset = true;
		ReSet();
	}
	if ("" != DeleteItemName)
	{
		DeletedItem[DeleteItemName] = Items[DeleteItemName];
		UIOff();
		Items.erase(DeleteItemName);
		DeleteItemName = "";

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

void AdditionItemUI::UIOn()
{
	this->On();
	LevelUpUIRender->On();
	StatUI->On();

}
void AdditionItemUI::UIOff()
{
	LevelUpUIRender->Off();
	StatUI->Off();
	for (std::pair<std::string, Button*> _Item : Items)
	{
		(*_Item.second).Off();
	}
	this->Off();
}