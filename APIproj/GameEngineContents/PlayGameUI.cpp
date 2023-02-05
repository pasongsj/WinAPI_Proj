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

	{
		UIRender = CreateRender("ExpBar.BMP", VSRenderOrder::UI);
		UIRender->SetScaleToImage();
		float4 BarPos = float4::Zero;
		BarPos.x = GameEngineWindow::GetScreenSize().hx();
		BarPos.y = UIRender->GetScale().hy();

		UIRender->SetPosition(BarPos);

		UIRender->EffectCameraOff();
		//GameEngineRender* Render = CreateRender("ExpBarBlue.BMP", VSRenderOrder::UI);
	}

}

void PlayGameUI::Update(float _DeltaTime)
{

}

