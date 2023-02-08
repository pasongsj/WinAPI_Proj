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
		StageTimerNum.SetOwner(this);
		StageTimerNum.SetImage("Number.BMp", { 30, 30 }, static_cast<int>(VSRenderOrder::UI), RGB(255, 0, 255));
		StageTimerNum.SetPos(BarPos);
		StageTimerNum.SetValue(static_cast<int>(StageTime));
		StageTimerNum.SetAlign(Align::Left);
	}

}

void PlayGameUI::Update(float _DeltaTime)
{
	StageTime += _DeltaTime;
	StageTimerNum.SetValue(static_cast<int>(StageTime));
}

