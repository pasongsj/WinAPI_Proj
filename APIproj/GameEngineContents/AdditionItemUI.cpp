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

AdditionItemUI::AdditionItemUI()
{
}

AdditionItemUI::~AdditionItemUI()
{
}


void PushLevelupBracer()
{
	//Player::MainPlayer->PushWeapon("Bracer");
}
void PushLevelupCandle()
{
	//Player::MainPlayer->PushWeapon("Candle");
}
void PushLevelupClover()
{
	//Player::MainPlayer->PushWeapon("Clover");
}
void PushLevelupEmptytome()
{
	//Player::MainPlayer->PushWeapon("Emptytome");
}
void PushLevelupFirewand()
{
	//Player::MainPlayer->PushWeapon("Firewand");
}
void PushLevelupHp()
{
	//Player::MainPlayer->PushWeapon("Hp");
}
void PushLevelupKingBible()
{
	//Player::MainPlayer->PushWeapon("KingBible");
}
void PushLevelupKnife()
{
	Player::MainPlayer->PushWeapon("Knife");
}
void PushLevelupMagicwand()
{
	Player::MainPlayer->PushWeapon("MagicWand");
}
void PushLevelupMagnet()
{
	//Player::MainPlayer->PushWeapon("Magnet");
}
void PushLevelupMoney()
{
	//Player::MainPlayer->PushWeapon("Money");
}
void PushLevelupWhip()
{
	Player::MainPlayer->PushWeapon("Whip");
}
void PushLevelupRunetracer()
{
	//Player::MainPlayer->PushWeapon("Runetracer");
}
void PushLevelupSpinach()
{
	//Player::MainPlayer->PushWeapon("Spinach");
}
void PushLevelupWing()
{
	//Player::MainPlayer->PushWeapon("Wing");
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
	_Pos.y -= (BtnScale.y * 1.15f);
	for (int i = 0;i < 4;i++)
	{
		BtnPos.push_back(_Pos);
		_Pos.y += BtnScale.y;
	}


	{
		LevelupItems.push_back("LevelupBracer.bmp");
		LevelupItems.push_back("LevelupCandle.bmp");
		LevelupItems.push_back("LevelupClover.bmp");
		LevelupItems.push_back("LevelupEmptytome.bmp");
		LevelupItems.push_back("LevelupFirewand.bmp");


		LevelupItems.push_back("LevelupHp.bmp");
		LevelupItems.push_back("LevelupKingBible.bmp");
		LevelupItems.push_back("LevelupKnife.bmp");
		LevelupItems.push_back("LevelupMagicwand.bmp");
		LevelupItems.push_back("LevelupMagnet.bmp");


		LevelupItems.push_back("LevelupMoney.bmp");
		LevelupItems.push_back("LevelupWhip.bmp");
		LevelupItems.push_back("LevelupRunetracer.bmp");
		LevelupItems.push_back("LevelupSpinach.bmp");
		LevelupItems.push_back("LevelupWing.bmp");
	}
	//int index_ = 0;
	for (std::string _Name : LevelupItems)
	{
		Button* NewCharBtn = GetLevel()->CreateActor<Button>(VSRenderOrder::LastUI);
		NewCharBtn->setting(_Name, _Name, _Name, { 0,0 }, BtnScale, static_cast<int>(VSRenderOrder::LastUI), false);
		NewCharBtn->SetRenderOrder(static_cast<int>(VSRenderOrder::LastUI));
		NewCharBtn->GetButtonRender()->SetImage(_Name);
		NewCharBtn->GetButtonRender()->EffectCameraOn();
		Items.push_back(NewCharBtn);
		NewCharBtn->Off();
	}
	{
		Items[0]->SetClickCallBack(PushLevelupBracer);
		Items[1]->SetClickCallBack(PushLevelupCandle);
		Items[2]->SetClickCallBack(PushLevelupClover);
		Items[3]->SetClickCallBack(PushLevelupEmptytome);
		Items[4]->SetClickCallBack(PushLevelupFirewand);
		Items[5]->SetClickCallBack(PushLevelupHp);
		Items[6]->SetClickCallBack(PushLevelupKingBible);
		Items[7]->SetClickCallBack(PushLevelupKnife);
		Items[8]->SetClickCallBack(PushLevelupMagicwand);
		Items[9]->SetClickCallBack(PushLevelupMagnet);
		Items[10]->SetClickCallBack(PushLevelupMoney);
		Items[11]->SetClickCallBack(PushLevelupWhip);
		Items[12]->SetClickCallBack(PushLevelupRunetracer);
		Items[13]->SetClickCallBack(PushLevelupSpinach);
		Items[14]->SetClickCallBack(PushLevelupWing);
	}

	this->Off();
}


void AdditionItemUI::Update(float _DeltaTime)
{
	if (false == IsReset)
	{
		IsReset = true;
		ReSet();
	}

	//for (int i = 0;i < 4;i++)
	//{
	//	int ItemIndex = GameEngineRandom::MainRandom.RandomInt(0, LevelupItems.size() - 1);
	//	Items[i]->SetPressImage(LevelupItems[ItemIndex]);
	//	Items[i]->SetHoverImage(LevelupItems[ItemIndex]);
	//	Items[i]->SetReleaseImage(LevelupItems[ItemIndex]);
	//}

}

void AdditionItemUI::ReSet()
{
	//std::set<Button*> ShowedBtn;
	//ShowedBtn.clear();
	ShowedBtn.clear();
	int i = 0;
	while (true)
	{
		if (ShowedBtn.size() == 4 || Items.size() == 0)
		{
			break;
		}
		int ItemIndex = GameEngineRandom::MainRandom.RandomInt(0, static_cast<int>(Items.size()) - 1);
		Button* Picked = Items[ItemIndex];
		ShowedBtn.insert(Picked);
		Items.erase(Items.begin() + ItemIndex);
		Picked->On();


		float4 Cam_Pos = GetLevel()->GetCameraPos() + BtnPos[i++];
		Picked->SetPos(Cam_Pos);
		//Picked->GetButtonRender()->SetPosition(BtnPos[i++]);
		//Picked->GetButtonCollision()->SetPosition(GetLevel()->GetCameraPos() + BtnPos[i++]);
	}

	std::set<Button*>::iterator startit = ShowedBtn.begin();
	std::set<Button*>::iterator endit = ShowedBtn.end();

	for (;startit != endit;startit++)
	{
		//(*startit)->On();
		Items.push_back(*startit);
		//ShowedBtn.erase(*startit);
	}

}

void AdditionItemUI::UIOn()
{
	this->On();
	LevelUpUIRender->On();
	StatUI->On();
	/*std::set<Button*>::iterator startit = ShowedBtn.begin();
	std::set<Button*>::iterator endit = ShowedBtn.end();*/

	/*for (;startit != endit;startit++)
	{
		(*startit)->On();
	}*/
	/*for (Button* _Btn : Items)
	{
		_Btn->On();
		int a = 0;
	}*/


}
void AdditionItemUI::UIOff()
{
	LevelUpUIRender->Off();
	StatUI->Off();
	for (Button* _Btn : Items)
	{
		_Btn->Off();
	}
	this->Off();
}