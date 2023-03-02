#include "AdditionItemUI.h"
#include <set>
#include <GameEngineBase/GameEngineRandom.h>
#include <GameEngineCore/GameEngineLevel.h>
#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEngineCore/NumberRenderObject.h>
#include "ContentsEnums.h"
#include "Player.h"


AdditionItemUI* AdditionItemUI::SelectUI;

AdditionItemUI::AdditionItemUI()
{
}

AdditionItemUI::~AdditionItemUI()
{
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
	_Pos.y -= static_cast<float>(BtnScale.y*(1.05));
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
	for (std::string _Name : LevelupItems)
	{
		Button* NewCharBtn = GetLevel()->CreateActor<Button>(VSRenderOrder::LastUI);
		NewCharBtn->setting(_Name, _Name, _Name, {0,0}, BtnScale, static_cast<int>(VSRenderOrder::LastUI), false);
		//NewCharBtn->SetClickCallBack();
		Items.push_back(NewCharBtn);
		NewCharBtn->Off();
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
	std::set<Button*> ShowedBtn;

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
		Picked->On();
		Picked->SetPos(BtnPos[i++]);
		Items.erase(Items.begin() + ItemIndex);
	}
	int a = 0;
	std::set<Button*>::iterator startit = ShowedBtn.begin();
	std::set<Button*>::iterator endit = ShowedBtn.end();

	for (;startit != endit;startit++)
	{
		Items.push_back(*startit);
	}

}

void AdditionItemUI::UIOn()
{
	this->On();
	LevelUpUIRender->On();
	StatUI->On();
	for (Button* _Btn : Items)
	{
		_Btn->On();
	}
}
void AdditionItemUI::UIOff()
{
	this->On();
	LevelUpUIRender->Off();
	StatUI->Off();
	for (Button* _Btn : Items)
	{
		_Btn->Off();
	}
}