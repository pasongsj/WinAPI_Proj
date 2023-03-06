#include "ObtainBox.h"
#include  "ContentsEnums.h"
#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEngineCore/GameEngineLevel.h>
#include <GameEngineCore/GameEngineRender.h>
#include <GameEngineCore/Button.h>
ObtainBox::ObtainBox()
{
}

ObtainBox::~ObtainBox()
{
}


void ObtainBox::Start()
{
	{
		ObtainBoxUI = CreateRender(VSRenderOrder::LastUI);
		ObtainBoxUI->SetImageToScaleToImage("BoxFoundUI.bmp");
		ObtainBoxUI->EffectCameraOff();
		ObtainBoxUI->SetPosition(GameEngineWindow::GetScreenSize().half());
	}
	{
		float4 OpenBoxButtonPos = GameEngineWindow::GetScreenSize().half();
		OpenBoxButton = GetLevel()->CreateActor<Button>(VSRenderOrder::LastUI);
		OpenBoxButton->setting("BoxOpenButton.bmp", "BoxOpenButton.bmp", "BoxOpenButton.bmp", OpenBoxButtonPos, {225, 71}, static_cast<int>(VSRenderOrder::LastUI), false);
		OpenBoxButton->GetButtonRender()->SetImage("BoxOpenButton.bmp");
		//NewCharBtn->GetButtonRender()->EffectCameraOn();
	}
	{
		//OpeningAnimation = CreateRender(VSRenderOrder::LastUI);
		//OpeningAnimation->CreateAnimation({ .AnimationName = "GlodBox",  .ImageName = RImage, .Start = 3, .End = 3 , .Loop = false }); // 5개줄 애니메이션
		//OpeningAnimation->CreateAnimation({ .AnimationName = "SilverBox",  .ImageName = RImage, .Start = 3, .End = 3 , .Loop = false }); //3개줄 애니메이션
		//OpeningAnimation->CreateAnimation({ .AnimationName = "BronzeBox",  .ImageName = RImage, .Start = 3, .End = 3 , .Loop = false }); // 1개줄 애니메이션
		//OpeningAnimation->SetScale(); //크기맞춤
	}

	{
		float4 CloseUIButtonPos = GameEngineWindow::GetScreenSize().half();
		CloseUIButton = GetLevel()->CreateActor<Button>(VSRenderOrder::LastUI);
		CloseUIButton->setting("BackBtn.bmp", "BackBtn.bmp", "BackBtn.bmp", CloseUIButtonPos, { 225, 71 }, static_cast<int>(VSRenderOrder::LastUI), false);
		CloseUIButton->GetButtonRender()->SetImage("BackBtn.bmp");
		CloseUIButton->Off();
		//NewCharBtn->GetButtonRender()->EffectCameraOn();
	}

	this->On();
}
void ObtainBox::Update(float _DeltaTime)
{

}