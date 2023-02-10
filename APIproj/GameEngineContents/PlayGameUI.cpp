#include "PlayGameUI.h"
#include "ContentsEnums.h"
#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEngineCore/GameEngineRender.h>


PlayGameUI::PlayGameUI()
{
}

PlayGameUI::~PlayGameUI()
{
}


void PlayGameUI::Start()
{
	float4 BarPos = float4::Zero;
	{
		BarPos.x = 1495;
		BarPos.y = 17.5;
		GameEngineRender* Render = CreateRender("LV.BMP", VSRenderOrder::UI);
		Render->SetScaleToImage();
		Render->SetPosition(BarPos);
		Render->EffectCameraOff();
	}

	{
		UIRender = CreateRender("ExpBar.BMP", VSRenderOrder::UI);
		UIRender->SetScaleToImage();
		BarPos.x = GameEngineWindow::GetScreenSize().hx();
		BarPos.y = UIRender->GetScale().hy();
		UIRender->SetPosition(BarPos);
		UIRender->EffectCameraOff();
		//GameEngineRender* Render = CreateRender("ExpBarBlue.BMP", VSRenderOrder::UI);
	}
	{
		BarPos.y += 50;
		GameEngineRender* Render = CreateRender("colon.BMP", VSRenderOrder::UI);
		Render->SetScaleToImage();
		Render->SetPosition(BarPos);
		Render->EffectCameraOff();
	}

	{
		BarPos.x -= 55;
		StageTimerMin.SetOwner(this);
		StageTimerMin.SetImage("Number.BMp", { 25, 30 }, static_cast<int>(VSRenderOrder::UI), RGB(255, 0, 255));
		StageTimerMin.SetRenderPos(BarPos);
		StageTimerMin.SetAlign(Align::Center);
		StageTimerMin.SetNumOfDigits(2);
		StageTimerMin.SetValue(static_cast<int>(StageTime)/60);
	}

	{
		BarPos.x += 95;
		StageTimerSec.SetOwner(this);
		StageTimerSec.SetImage("Number.BMp", { 25, 30 }, static_cast<int>(VSRenderOrder::UI), RGB(255, 0, 255));
		StageTimerSec.SetRenderPos(BarPos);
		StageTimerSec.SetAlign(Align::Center);
		StageTimerSec.SetNumOfDigits(2);
		StageTimerSec.SetValue(static_cast<int>(StageTime)%60);
	}

}

void PlayGameUI::Update(float _DeltaTime)
{
	StageTime += _DeltaTime;
	StageTimerMin.SetValue(static_cast<int>(StageTime) / 60);
	StageTimerSec.SetValue(static_cast<int>(StageTime) % 60);
}

