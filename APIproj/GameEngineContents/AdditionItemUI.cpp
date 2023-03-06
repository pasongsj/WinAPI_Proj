#include "AdditionItemUI.h"
#include <vector>
//#include <set>
#include <GameEngineBase/GameEngineRandom.h>
#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEngineCore/GameEngineLevel.h>
#include <GameEngineCore/NumberRenderObject.h>
#include <GameEngineCore/GameEngineCollision.h>
#include "ContentsEnums.h"

//#include "AdditionItemUIButtonFunction.h"
#include "Player.h"

AdditionItemUI* AdditionItemUI::SelectUI;
std::vector<std::string> AdditionItemUI::DeleteItemName;


AdditionItemUI::AdditionItemUI()
{
}

AdditionItemUI::~AdditionItemUI()
{
	/*for (NumberRenderObject* _UI : AdditionItemUI::ActiveStatUI)
	{
		if (nullptr == _UI)
		{
			return;
		}
		delete _UI;
		_UI = nullptr;
	}*/

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

	float interval = 18.6f;

	float4 ActiveStatUIPos = { 210,205 };
	for (int i = 0; i < 17; i++)
	{
		//NumberRenderObject* _Num = new NumberRenderObject();

		//NumberRenderObject* _Num = GetLevel()->CreateActor(VSRenderOrder::MAX);

		ActiveStatUI[i].SetOrder(static_cast<int> (VSRenderOrder::MAX));
		float4 BarPos = GameEngineWindow::GetScreenSize().half();
		//BarPos.y -= 55;
		ActiveStatUI[i].SetOwner(this);
		ActiveStatUI[i].SetImage("Number.BMp", { 12, 15 }, static_cast<int>(VSRenderOrder::MAX), RGB(255, 0, 255),"Negative.bmp", "Percent.bmp");
		ActiveStatUI[i].SetRenderPos(ActiveStatUIPos);
		ActiveStatUI[i].SetAlign(Align::Right);
		ActiveStatUI[i].SetValue(0);


		ActiveStatUIPos.y += interval;
		if ((3 == i) || (i == 9) || (i == 12) || (i == 13))
		{
			ActiveStatUIPos.y += interval;
		}
	}

	Active Originactive;
	int index = 0;
	ActiveStatUI[index++].SetValue(static_cast<int>(Originactive.MaxHealth));
	ActiveStatUI[index++].SetValue(/*Originactive.Recovery*/0	 );  // 소수점
	ActiveStatUI[index++].SetValue(Originactive.Armor		 );
	ActiveStatUI[index].SetPercent();	ActiveStatUI[index++].SetValue(static_cast<int>(Originactive.ActiveSpeed)	-100);
								
	ActiveStatUI[index].SetPercent();	ActiveStatUI[index++].SetValue(static_cast<int>(Originactive.Might) - 100);
	ActiveStatUI[index].SetPercent();	ActiveStatUI[index++].SetValue(static_cast<int>(Originactive.Area) - 100);
	ActiveStatUI[index].SetPercent();	ActiveStatUI[index++].SetValue(static_cast<int>(Originactive.Speed) - 100);
	ActiveStatUI[index].SetPercent();	ActiveStatUI[index++].SetValue(static_cast<int>(Originactive.Duration) - 100);
	ActiveStatUI[index++].SetValue(Originactive.Amount	 );
	ActiveStatUI[index].SetPercent();	ActiveStatUI[index++].SetValue(static_cast<int>(Originactive.Cooldown) - 100);
								 
	ActiveStatUI[index].SetPercent();	ActiveStatUI[index++].SetValue(static_cast<int>(Originactive.Luck) - 100);
	ActiveStatUI[index].SetPercent();	ActiveStatUI[index++].SetValue(static_cast<int>(Originactive.Growth)	 );
	ActiveStatUI[index].SetPercent();	ActiveStatUI[index++].SetValue(static_cast<int>(Originactive.Greed) - 100);
								
	ActiveStatUI[index].SetPercent();	ActiveStatUI[index++].SetValue(Originactive.Magnet	 );
								  
	ActiveStatUI[index++].SetValue(Originactive.Revival	 );
	ActiveStatUI[index++].SetValue(Originactive.Reroll 	 );
	ActiveStatUI[index++].SetValue(Originactive.Skip 		 );

	this->Off();
}


void AdditionItemUI::Update(float _DeltaTime)
{
	if (false == IsReset)
	{
		IsReset = true;
		ReSet();
	}
	if (0 < DeleteItemName.size())
	{
		for (std::string _Name : DeleteItemName)
		{
			if (Items.find(_Name) == Items.end())
			{
				MsgAssert("리스트에 없는 무기를 제거하려 했습니다.");
			}
			DeletedItem[_Name] = Items[_Name];
			DeletedItem[_Name]->Off();
			Items.erase(_Name);

		}
		DeleteItemName.clear();
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