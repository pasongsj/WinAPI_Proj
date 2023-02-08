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
		StageTimerMin.SetOwner(this);
		StageTimerMin.SetImage("Number.BMp", { 30, 35 }, static_cast<int>(VSRenderOrder::UI), RGB(255, 0, 255));
		StageTimerMin.SetRenderPos(BarPos);
		StageTimerMin.SetAlign(Align::Right);
		StageTimerMin.SetNumOfDigits(2);
		StageTimerMin.SetValue(static_cast<int>(StageTime));
	}

}

void PlayGameUI::Update(float _DeltaTime)
{
	StageTime += _DeltaTime;
	StageTimerMin.SetValue(static_cast<int>(StageTime));
}

