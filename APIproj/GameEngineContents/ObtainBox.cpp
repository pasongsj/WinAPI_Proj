#include "ObtainBox.h"
#include  "ContentsEnums.h"
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
	{
		std::vector<float> _FrameTime = { 1.5f,0.1f,0.1f,0.1f };
		ObtainBoxUI = CreateRender(VSRenderOrder::LastUI);
		ObtainBoxUI->CreateAnimation({.AnimationName = "FoundBox", .ImageName = "BoxFoundUI.bmp", .Start = 0, .End = 3,  .Loop = true, .FrameTime  = _FrameTime });
		ObtainBoxUI->ChangeAnimation("FoundBox");
		//ObtainBoxUI->SetImageToScaleToImage("BoxFoundUI.bmp");
		ObtainBoxUI->SetScale({ 576, 767 });
		ObtainBoxUI->EffectCameraOff();
		ObtainBoxUI->SetPosition(GameEngineWindow::GetScreenSize().half());
	}
	{
		/*float4 OpenBoxButtonPos = GameEngineWindow::GetScreenSize().half() + float4 { 0, 248 };;*/
		OpenBoxButton = GetLevel()->CreateActor<Button>(VSRenderOrder::LastUI);
		OpenBoxButton->setting("BoxOpenButton.bmp", "BoxOpenButton.bmp", "BoxOpenButton.bmp", {0,0}/*OpenBoxButtonPos*/, { 270, 85 }, static_cast<int>(VSRenderOrder::LastUI), false);
		OpenBoxButton->GetButtonRender()->SetImage("BoxOpenButton.bmp");
		OpenBoxButton->GetButtonRender()->EffectCameraOn();
		OpenBoxButton->SetClickCallBack(ClickOpenBox);
		//NewCharBtn->GetButtonRender()->EffectCameraOn();
	}
	{
		OpeningAnimation = CreateRender(VSRenderOrder::LastUI);
		OpeningAnimation->CreateAnimation({ .AnimationName = "GlodBox",  .ImageName = "openingBox1.bmp", .Start = 0, .End =  7, .Loop = false }); // 5개줄 애니메이션
		OpeningAnimation->CreateAnimation({ .AnimationName = "SilverBox",  .ImageName = "openingBox1.bmp", .Start = 0, .End = 7 , .Loop = false }); //3개줄 애니메이션
		OpeningAnimation->CreateAnimation({ .AnimationName = "BronzeBox",  .ImageName = "openingBox1.bmp", .Start = 0, .End = 7 , .Loop = false }); // 1개줄 애니메이션
		OpeningAnimation->ChangeAnimation("BronzeBox");
		OpeningAnimation->EffectCameraOff();
		OpeningAnimation->SetPosition(GameEngineWindow::GetScreenSize().half());
		OpeningAnimation->SetScale({576,767}); //크기맞춤
		OpeningAnimation->Off();
	}

	{
		//float4 CloseUIButtonPos = GameEngineWindow::GetScreenSize().half() + float4{ 0, 248 };
		CloseUIButton = GetLevel()->CreateActor<Button>(VSRenderOrder::LastUI);
		CloseUIButton->setting("BackBtn.bmp", "BackBtn.bmp", "BackBtn.bmp", {0,0}, { 270, 85 }, static_cast<int>(VSRenderOrder::LastUI), false);
		CloseUIButton->GetButtonRender()->SetImage("BackBtn.bmp");
		CloseUIButton->GetButtonRender()->EffectCameraOn();
		CloseUIButton->SetClickCallBack(ClickCloseBox);

		CloseUIButton->Off();//
	}

	//this->Off();
}

void ObtainBox::OpeningBoxAnimation()
{
	OpenBoxButton->Off();
	OpeningAnimation->On();
	GameEngineSoundPlayer Dwn = GameEngineResources::GetInst().SoundPlayToControl("TreasureOpening.mp3");
	Dwn.Volume(0.3f);
	Dwn.LoopCount(1);
}


void ObtainBox::Update(float _DeltaTime)
{
	if (false == IsOpened)
	{
		OpenBoxButton->On();
		IsOpened = true;
	}
	if (true == OpeningAnimation->IsUpdate())
	{
		AnimationTime += _DeltaTime;
	}
	if (AnimationTime > 9.0f && false == CloseUIButton->IsUpdate())
	{
		CloseUIButton->On();
	}
}

void ObtainBox::UIOn()
{
	float4 OpenBoxButtonPos = GameEngineWindow::GetScreenSize().half() + float4{ 0, 295 } + GetLevel()->GetCameraPos();
	OpenBoxButton->SetPos(OpenBoxButtonPos);
	CloseUIButton->SetPos(OpenBoxButtonPos);
	this->On();
	//OpenBoxButton->On();
	//CloseUIButton->On();

}
void ObtainBox::UIOff()
{
	//IsUIOnOff = false;
	OpenBoxButton->Off();
	CloseUIButton->Off();
	this->Off();
	IsOpened = false;
}