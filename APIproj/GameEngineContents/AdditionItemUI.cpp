#include "AdditionItemUI.h"

//#include <set>
#include <GameEngineBase/GameEngineRandom.h>
#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEngineCore/GameEngineLevel.h>
#include <GameEngineCore/NumberRenderObject.h>
#include <GameEngineCore/GameEngineCollision.h>
#include "ContentsEnums.h"

//#include "AdditionItemUIButtonFunction.h"


AdditionItemUI* AdditionItemUI::SelectUI;
std::string AdditionItemUI::DeleteItemName = "";

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
	_Pos.y -= (BtnScale.y * 1.06f);
	for (int i = 0;i < 4;i++)
	{
		BtnPos.push_back(_Pos);
		_Pos.y += BtnScale.y;
	}

	SetItemImage();

	for (std::pair<std::string, std::string> _Name : ItemNames)
	{
		Button* NewCharBtn = GetLevel()->CreateActor<Button>(VSRenderOrder::LastUI);
		NewCharBtn->setting(_Name.second, _Name.second, _Name.second, { 0,0 }, BtnScale, static_cast<int>(VSRenderOrder::LastUI), false);
		NewCharBtn->GetButtonRender()->SetImage(_Name.second);
		NewCharBtn->GetButtonRender()->EffectCameraOn();
		Items[_Name.first] = (NewCharBtn);
		NewCharBtn->Off();
	}

	SetItemFunction();

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