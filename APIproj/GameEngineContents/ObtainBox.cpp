#include "ObtainBox.h"
#include  "ContentsEnums.h"
#include <GameEngineBase/GameEngineMath.h>
#include <GameEngineBase/GameEngineRandom.h>
#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEngineCore/GameEngineLevel.h>
#include <GameEngineCore/GameEngineRender.h>
#include <GameEngineCore/Button.h>
#include "Player.h"



ObtainBox* ObtainBox::ObtainBoxAni = nullptr;
ObtainBox::ObtainBox()
{
}

ObtainBox::~ObtainBox()
{
}

void ClickOpenBox()
{
	ObtainBox::ObtainBoxAni->OpeningBoxAnimation();
}

void ClickCloseBox()
{
	ObtainBox::ObtainBoxAni->UIOff();
	Player::MainPlayer->OpenBoxUI = false;
}

void ObtainBox::Start()
{
	ObtainBoxAni = this;
	{//  안열린 박스
		std::vector<float> _FrameTime = { 1.5f,0.1f,0.1f,0.1f };
		ObtainBoxUI = CreateRender(VSRenderOrder::LastUI);
		ObtainBoxUI->CreateAnimation({.AnimationName = "FoundBox", .ImageName = "BoxFoundUI.bmp", .Start = 0, .End = 3,  .Loop = true, .FrameTime  = _FrameTime });
		ObtainBoxUI->ChangeAnimation("FoundBox");
		ObtainBoxUI->SetScale({ 576, 767 });
		ObtainBoxUI->EffectCameraOff();
		ObtainBoxUI->SetPosition(GameEngineWindow::GetScreenSize().half());
	}
	{ // 박스 열기 버튼
		OpenBoxButton = GetLevel()->CreateActor<Button>(VSRenderOrder::LastUI);
		OpenBoxButton->setting("BoxOpenButton.bmp", "BoxOpenButton.bmp", "BoxOpenButton.bmp", {0,0}/*OpenBoxButtonPos*/, { 270, 85 }, static_cast<int>(VSRenderOrder::LastUI), false);
		OpenBoxButton->GetButtonRender()->SetImage("BoxOpenButton.bmp");
		OpenBoxButton->GetButtonRender()->EffectCameraOn();
		OpenBoxButton->SetClickCallBack(ClickOpenBox);

	}

	{ // 열린 박스 이미지
		OpenedBoxUI = CreateRender("OpenedBox.bmp",VSRenderOrder::LastUI);
		OpenedBoxUI->SetScaleToImage();
		OpenedBoxUI->EffectCameraOff();
		OpenedBoxUI->SetPosition(GameEngineWindow::GetScreenSize().half());
		OpenedBoxUI->Off();
	}

	//{ // 박스 열리는 애니메이션
		OpeningAnimation = CreateRender(VSRenderOrder::LastUI);
		OpeningAnimation->SetImage("OpeningBronze.bmp");
		OpeningAnimation->SetAlpha(150);
		OpeningAnimation->EffectCameraOff();
		OpeningAnimation->SetPosition(GameEngineWindow::GetScreenSize().half() + float4{0,154});
		OpeningAnimation->SetScale({ 576, 10 });
		OpeningAnimation->Off();
	//}

	{
		Opening = CreateRender(VSRenderOrder::LastUI);
		Opening->EffectCameraOff();
		Opening->CreateAnimation({ .AnimationName = "Box",  .ImageName = "Animation.bmp", .Start = 0, .End = 11, .Loop = true }); // 5개줄 애니메이션
		Opening->ChangeAnimation("Box");
		Opening->SetPosition(GameEngineWindow::GetScreenSize().half() + float4{ 0,-90 });
		Opening->SetScale({ 85.5f,513 });
		Opening->Off();

	}
	{ // 나가기 버튼
		CloseUIButton = GetLevel()->CreateActor<Button>(VSRenderOrder::LastUI);
		CloseUIButton->setting("BackBtn.bmp", "BackBtn.bmp", "BackBtn.bmp", {0,0}, { 270, 85 }, static_cast<int>(VSRenderOrder::LastUI), false);
		CloseUIButton->GetButtonRender()->SetImage("BackBtn.bmp");
		CloseUIButton->GetButtonRender()->EffectCameraOn();
		CloseUIButton->SetClickCallBack(ClickCloseBox);

		CloseUIButton->Off();//
	}

	
	{
		for (int i = 0;i < 5;i++)
		{
			GameEngineRender* _Render = CreateRender(VSRenderOrder::LastUI);
			_Render->EffectCameraOff();
			_Render->SetScale({ 90,90 });
			_Render->Off();
			BoxItemsRender.push_back(_Render);
		}
		BoxItemsRender[0]->SetPosition({ 768, 200 }); // 768
		BoxItemsRender[1]->SetPosition({ 648, 250 });
		BoxItemsRender[2]->SetPosition({ 888, 250 });
		BoxItemsRender[3]->SetPosition({ 588, 400 });
		BoxItemsRender[4]->SetPosition({ 948, 400 });
	}

	//this->Off();
}

void ObtainBox::OpeningBoxAnimation()
{
	ObtainBoxUI->Off();
	OpenBoxButton->Off();

	OpenedBoxUI->On();
	OpeningAnimation->SetScale({ 576, 10 });
	OpeningAnimation->On();
	//
	//Opening->SetScale({ 100, 10 });
	/*Opening->SetPosition(GameEngineWindow::GetScreenSize().half() + float4{ 0,154 });*/
	Opening->On();
	//
	GameEngineSoundPlayer Dwn = GameEngineResources::GetInst().SoundPlayToControl("TreasureOpening.mp3");
	Dwn.Volume(0.3f);
	Dwn.LoopCount(1);
}


void ObtainBox::Update(float _DeltaTime)
{
	CheckIsOpen(_DeltaTime);
	if (true == OpenedBoxUI->IsUpdate())
	{
		AnimationTime += _DeltaTime;
		if(OpeningAnimation->GetScale().y< 1026)
		{
			float4 _Scale = float4::Zero.LerpClamp(float4{ 200,10 }, float4{ 576,1026 }, 3.0f*AnimationTime);
			OpeningAnimation->SetScale(_Scale);
			//float4 _Scale2 = float4::Zero.LerpClamp(float4{ 85.5f,10 }, float4{ 85.5f,513 }, 3.0f * AnimationTime);
			//Opening->SetScale(_Scale2);
		}

	}
	if (AnimationTime > 7.5f && false == CloseUIButton->IsUpdate())
	{
		OpeningAnimation->Off();
		Opening->Off();
		for (int i = 0;i < PickedItems.size();i++)
		{
			std::string ImgName = "Box" + PickedItems[i] + ".bmp";
			BoxItemsRender[i]->SetImage(ImgName);
			BoxItemsRender[i]->On();
		}
		CloseUIButton->On();
	}
}

void ObtainBox::CheckIsOpen(float _DeltaTime)
{

	if (false == IsOpened)
	{
		ObtainBoxUI->On();
		OpenBoxButton->On();
		IsOpened = true;
		float _Num = GameEngineRandom::MainRandom.RandomFloat(0, 100);
		int Cnt = 0;

		/*std::vector<std::string> PickedItems;*/
		PickedItems.clear();

		if (GoldBox > _Num)
		{
			int a = 0;
			Cnt = 5;
		}
		else if (SilverBox >= _Num)
		{
			OpeningAnimation->SetImage("OpeningSilver.bmp");
			Cnt = 3;
		}
		else
		{
			OpeningAnimation->SetImage("OpeningBronze.bmp");
			Cnt = 1;
		}
		for (int i = 0;i < Cnt;++i)
		{
			std::vector<std::string> ItemsList = GetItems();
			if (ItemsList.size() == 0)
			{
				Player::MainPlayer->PushActive("Money");
				PickedItems.push_back("Money");
				continue;
			}
			int _Ran = GameEngineRandom::MainRandom.RandomInt(0, static_cast<int>(ItemsList.size())-1);


			if (ItemsList[_Ran] == "FireWand" || ItemsList[_Ran] == "KingBible" || ItemsList[_Ran] == "Knife" ||
				ItemsList[_Ran] == "MagicWand" || ItemsList[_Ran] == "RuneTracer" || ItemsList[_Ran] == "Whip")
			{
				Player::MainPlayer->PushWeapon(ItemsList[_Ran]);
			}
			else
			{
				Player::MainPlayer->PushActive(ItemsList[_Ran]);
			}
			PickedItems.push_back(ItemsList[_Ran]);
		}
	}
}
std::vector<std::string> ObtainBox::GetItems()
{
	std::vector<std::string> _Return;
	std::vector<std::pair<int, std::string>> WeaponList = Player::MainPlayer->GetWeapon();

	for (std::pair<int, std::string> _Weap : WeaponList)
	{
		if (_Weap.first < 8)
		{
			_Return.push_back(_Weap.second);
		}
	}
	ActiveLevel ActiveList = Player::MainPlayer->GetActive();
	std::map<std::string, int> _Active;
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
		if (startiter->second > 0 && startiter->second < 5)
		{
			_Return.push_back(startiter->first);
		}
	}

	return _Return;
}

void ObtainBox::UIOn()
{
	float4 OpenBoxButtonPos = GameEngineWindow::GetScreenSize().half() + float4{ 0, 295 } + GetLevel()->GetCameraPos();
	OpenBoxButton->SetPos(OpenBoxButtonPos);
	CloseUIButton->SetPos(OpenBoxButtonPos);
	this->On();

}
void ObtainBox::UIOff()
{
	//IsUIOnOff = false;
	OpenBoxButton->Off();
	CloseUIButton->Off();
	ObtainBoxUI->Off();

	OpeningAnimation->Off();
	Opening->Off();
	//OpeningAnimation->SetScale({ 576, 10 });
	OpenedBoxUI->Off();

	IsOpened = false;
	AnimationTime = 0.0f;

	for (int i = 0;i < 5;i++)
	{
		BoxItemsRender[i]->Off();
	}
	this->Off();
}