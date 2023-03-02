#include "AdditionItemUI.h"
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
		LevelUpUIRender = CreateRender("LevelUpUI.BMP", VSRenderOrder::UI);
		LevelUpUIRender->SetScaleToImage();
		LevelUpUIRender->SetPosition(GameEngineWindow::GetScreenSize().half());
		LevelUpUIRender->EffectCameraOff();
	}
	float4 _Pos = GameEngineWindow::GetScreenSize().half();
	_Pos.y -= BtnScale.y*(1.2);

	for (int i = 0;i < 4;i++)
	{
		//Button* NewCharBtn = GetLevel()->CreateActor<Button>(VSRenderOrder::UI);
		//NewCharBtn->setting("LevelupBlank.BMP", "LevelupBlank.BMP", "LevelupBlank.BMP", _Pos, BtnScale, static_cast<int>(VSRenderOrder::UI), false);
		//Items.push_back(NewCharBtn);
		BtnPos.push_back(_Pos);
		_Pos.y += BtnScale.y;
		//NewCharBtn->Off();
	}

	//for (int i = 0;i < 4;i++)
	//{
	//	Button* NewBtn = GetLevel()->CreateActor<Button>(VSRenderOrder::UI);
	//	Items[i]->setting("LevelupBlank.bmp", "LevelupBlank.bmp", "LevelupBlank.bmp", _Pos, BtnScale, static_cast<int>(VSRenderOrder::UI), false);
	//	//Items.push_back(NewBtn);
	//	//BtnPos.push_back(_Pos);
	//	////NewBtn->Off();
	//	//_Pos.y += BtnScale.y;
	//}
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
		//LevelupItems.push_back("LevelupWhip.bmp");
		LevelupItems.push_back("LevelupRunetracer.bmp");
		LevelupItems.push_back("LevelupSpinach.bmp");
		LevelupItems.push_back("LevelupWing.bmp");
	}
	for (std::string _Name : LevelupItems)
	{
		Button* NewCharBtn = GetLevel()->CreateActor<Button>(VSRenderOrder::LastUI);
		NewCharBtn->setting(_Name, _Name, _Name, {0,0}, BtnScale, static_cast<int>(VSRenderOrder::LastUI), false);
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
	for (int i = 0;i < 4;i++)
	{
		int ItemIndex = GameEngineRandom::MainRandom.RandomInt(0, LevelupItems.size() - 1);
		Items[ItemIndex]->On();
		Items[ItemIndex]->SetPos(BtnPos[i]);
	}
	int a = 0;
}

void AdditionItemUI::UIOn()
{
	this->On();
	LevelUpUIRender->On();
	for (Button* _Btn : Items)
	{
		_Btn->On();
	}
}
void AdditionItemUI::UIOff()
{

	this->On();
	LevelUpUIRender->Off();
	for (Button* _Btn : Items)
	{
		_Btn->Off();
	}
}