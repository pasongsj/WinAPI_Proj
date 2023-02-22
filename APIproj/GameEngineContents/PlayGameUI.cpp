#include "PlayGameUI.h"
#include "ContentsEnums.h"
#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEngineCore/GameEngineRender.h>
#include "Player.h"

PlayGameUI::PlayGameUI()
{
}

PlayGameUI::~PlayGameUI()
{
}


void PlayGameUI::Start()
{
	float4 BarPos = float4::Zero;

	{ // ExpBar
		GameEngineRender* Render = CreateRender("ExpBar.BMP", VSRenderOrder::UI);
		Render->SetScaleToImage();
		BarPos.x = GameEngineWindow::GetScreenSize().hx(); //768
		BarPos.y = Render->GetScale().hy(); //17.5
		Render->SetPosition(BarPos);
		Render->EffectCameraOff();
	}

	{ // LV 
		GameEngineRender* Render = CreateRender("LV.BMP", VSRenderOrder::UI);
		Render->SetScaleToImage();
		BarPos.x = GameEngineWindow::GetScreenSize().x - (Render->GetScale()).x;

		Render->SetPosition(BarPos);
		Render->EffectCameraOff();
	}

	{ // time - colon
		BarPos.x = GameEngineWindow::GetScreenSize().hx();
		BarPos.y += 50;
		GameEngineRender* Render = CreateRender("colon.BMP", VSRenderOrder::UI);
		Render->SetScaleToImage();
		Render->SetPosition(BarPos);
		Render->EffectCameraOff();
	}


	{ // time - min
		StageTimerMin.SetOrder(static_cast<int> (VSRenderOrder::UI));
		BarPos.x = GameEngineWindow::GetScreenSize().hx() - 35;
		//BarPos.y -= 55;
		StageTimerMin.SetOwner(this);
		StageTimerMin.SetImage("Number.BMp", { 25, 30 }, static_cast<int>(VSRenderOrder::UI), RGB(255, 0, 255));
		StageTimerMin.SetRenderPos(BarPos);
		StageTimerMin.SetAlign(Align::Center);
		StageTimerMin.SetNumOfDigits(2);
		StageTimerMin.SetValue(static_cast<int>(StageTime)/60);
	}

	{// time - sec
		StageTimerSec.SetOrder(static_cast<int> (VSRenderOrder::UI));
		BarPos.x = GameEngineWindow::GetScreenSize().hx() + 35;
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
	/*if (true == Player::IsStop)
	{
		return;
	}*/
	StageTime += _DeltaTime;
	StageTimerMin.SetValue(static_cast<int>(StageTime) / 60);
	StageTimerSec.SetValue(static_cast<int>(StageTime) % 60);
}

