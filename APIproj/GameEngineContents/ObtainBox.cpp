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
		/*float4 OpenBoxButtonPos = GameEngineWindow::GetScreenSize().half() + float4 { 0, 248 };;*/
		OpenBoxButton = GetLevel()->CreateActor<Button>(VSRenderOrder::LastUI);
		OpenBoxButton->setting("BoxOpenButton.bmp", "BoxOpenButton.bmp", "BoxOpenButton.bmp", {0,0}/*OpenBoxButtonPos*/, { 225, 71 }, static_cast<int>(VSRenderOrder::LastUI), false);
		OpenBoxButton->GetButtonRender()->SetImage("BoxOpenButton.bmp");
		OpenBoxButton->GetButtonRender()->EffectCameraOn();
		//NewCharBtn->GetButtonRender()->EffectCameraOn();
	}
	//{
	//	OpeningAnimation = CreateRender(VSRenderOrder::LastUI);
	//	OpeningAnimation->CreateAnimation({ .AnimationName = "GlodBox",  .ImageName = "openingBox1.bmp", .Start = 0, .End =  7, .Loop = false }); // 5개줄 애니메이션
	//	OpeningAnimation->CreateAnimation({ .AnimationName = "SilverBox",  .ImageName = "openingBox1.bmp", .Start = 0, .End = 7 , .Loop = false }); //3개줄 애니메이션
	//	OpeningAnimation->CreateAnimation({ .AnimationName = "BronzeBox",  .ImageName = "openingBox1.bmp", .Start = 0, .End = 7 , .Loop = false }); // 1개줄 애니메이션
	//	OpeningAnimation->ChangeAnimation("BronzeBox");
	//	OpeningAnimation->EffectCameraOff();
	//	OpeningAnimation->SetPosition(GameEngineWindow::GetScreenSize().half());
	//	OpeningAnimation->SetScale({576,767}); //크기맞춤
	//}

	{
		float4 CloseUIButtonPos = GameEngineWindow::GetScreenSize().half() + float4{ 0, 248 };
		CloseUIButton = GetLevel()->CreateActor<Button>(VSRenderOrder::LastUI);
		CloseUIButton->setting("BackBtn.bmp", "BackBtn.bmp", "BackBtn.bmp", CloseUIButtonPos, { 225, 71 }, static_cast<int>(VSRenderOrder::LastUI), false);
		CloseUIButton->GetButtonRender()->SetImage("BackBtn.bmp");
		//CloseUIButton->Off();//
		//NewCharBtn->GetButtonRender()->EffectCameraOn();
	}

	//this->Off();
}


void ObtainBox::Update(float _DeltaTime)
{
}

void ObtainBox::UIOn()
{
	float4 OpenBoxButtonPos = GameEngineWindow::GetScreenSize().half() + float4{ 0, 248 } + GetLevel()->GetCameraPos();
	OpenBoxButton->SetPos(OpenBoxButtonPos);
	this->On();
	OpenBoxButton->On();
	//CloseUIButton->On();

}
void ObtainBox::UIOff()
{
	//IsUIOnOff = false;
	OpenBoxButton->Off();
	CloseUIButton->Off();
	this->Off();
}