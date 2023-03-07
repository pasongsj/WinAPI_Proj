#include "AdditionItemUI.h"
#include <vector>
//#include <set>
//#include <GameEngineBase/GameEngineRandom.h>
#include <GameEnginePlatform/GameEngineWindow.h>
//#include <GameEngineCore/GameEngineLevel.h>
#include <GameEngineCore/NumberRenderObject.h>
#include <GameEngineCore/GameEngineCollision.h>
#include "ContentsEnums.h"
#include <GameEngineCore/GameEngineResources.h>

//#include "AdditionItemUIButtonFunction.h"
#include "Player.h"

AdditionItemUI* AdditionItemUI::SelectUI;
std::vector<std::string> AdditionItemUI::DeleteItemName;


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
	SetItemFunction();
	SetStatNumber();
	SetStatNumberValue();


	this->Off();
}
void AdditionItemUI::SetStatNumberValue()
{
	Active Originactive;
	int index = 0;
	ActiveStatUI[index++].SetValue(static_cast<int>(Originactive.MaxHealth));
	ActiveStatUI[index].SetPercent();	ActiveStatUI[index++].SetValue(static_cast<int>(Originactive.Recovery));  // 소수점
	ActiveStatUI[index++].SetValue(Originactive.Armor);
	ActiveStatUI[index].SetPercent();	ActiveStatUI[index++].SetValue(static_cast<int>(Originactive.ActiveSpeed) - 100);

	ActiveStatUI[index].SetPercent();	ActiveStatUI[index++].SetValue(static_cast<int>(Originactive.Might) - 100);
	ActiveStatUI[index].SetPercent();	ActiveStatUI[index++].SetValue(static_cast<int>(Originactive.Area) - 100);
	ActiveStatUI[index].SetPercent();	ActiveStatUI[index++].SetValue(static_cast<int>(Originactive.Speed) - 100);
	ActiveStatUI[index].SetPercent();	ActiveStatUI[index++].SetValue(static_cast<int>(Originactive.Duration) - 100);
	ActiveStatUI[index++].SetValue(Originactive.Amount);
	ActiveStatUI[index].SetPercent();	ActiveStatUI[index++].SetValue(static_cast<int>(Originactive.Cooldown) - 100);

	ActiveStatUI[index].SetPercent();	ActiveStatUI[index++].SetValue(static_cast<int>(Originactive.Luck) - 100);
	ActiveStatUI[index].SetPercent();	ActiveStatUI[index++].SetValue(static_cast<int>(Originactive.Growth));
	ActiveStatUI[index].SetPercent();	ActiveStatUI[index++].SetValue(static_cast<int>(Originactive.Greed) - 100);

	ActiveStatUI[index].SetPercent();	ActiveStatUI[index++].SetValue(Originactive.Magnet);

	ActiveStatUI[index++].SetValue(Originactive.Revival);
	ActiveStatUI[index++].SetValue(Originactive.Reroll);
	ActiveStatUI[index++].SetValue(Originactive.Skip);
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

	/*std::vector<std::pair<int, std::string>> WeaponList = Player::MainPlayer->GetWeapon();

	int IconIndex = Icon.size()-1;
	for (int i = 0;i < WeaponList.size();++i)
	{
		if (IconIndex >= i)
		{
			continue;
		}
		Icon.push_back(WeaponList[i]);
		MakerIconRender(WeaponList[i].first, WeaponList[i].second);
	}*/

}

void AdditionItemUI::UIOn()
{
	this->On();
	LevelUpUIRender->On();
	StatUI->On();

}
void AdditionItemUI::UIOff()
{
	IsUIOnOff = false;
	LevelUpUIRender->Off();
	StatUI->Off();
	for (std::pair<std::string, Button*> _Item : Items)
	{
		(*_Item.second).Off();
	}
	this->Off();
}