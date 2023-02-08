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
		BarPos.x += 35;
		StageTimerSec.SetOwner(this);
		StageTimerSec.SetImage("Number.BMp", { 30, 35 }, static_cast<int>(VSRenderOrder::UI), RGB(255, 0, 255));
		StageTimerSec.SetRenderPos(BarPos);
		StageTimerSec.SetAlign(Align::Left);
		StageTimerSec.SetNumOfDigits(2);
		StageTimerSec.SetValue(static_cast<int>(StageTime)%60);
	}
	{
		BarPos.x -= 70;
		StageTimerMin.SetOwner(this);
		StageTimerMin.SetImage("Number.BMp", { 30, 35 }, static_cast<int>(VSRenderOrder::UI), RGB(255, 0, 255));
		StageTimerMin.SetRenderPos(BarPos);
		StageTimerMin.SetAlign(Align::Left);
		StageTimerMin.SetNumOfDigits(2);
		StageTimerMin.SetValue(static_cast<int>(StageTime)/60);
	}

}

void PlayGameUI::Update(float _DeltaTime)
{
	StageTime += _DeltaTime;
	StageTimerSec.SetValue(static_cast<int>(StageTime) % 60);
	StageTimerMin.SetValue(static_cast<int>(StageTime) / 60);
}

