#include "TitleBack.h"
#include "ContentsEnums.h"
#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEngineCore/GameEngineRender.h>

TitleBack::TitleBack()
{
}

TitleBack::~TitleBack()
{
}


void TitleBack::Start()
{
	float4 Size = GameEngineWindow::GetScreenSize();

	GameEngineRender* Render = CreateRender("TitleBackground.bmp", BubbleRenderOrder::BackGround);
	Render->SetPosition(GameEngineWindow::GetScreenSize().half());
	Render->SetScale(GameEngineWindow::GetScreenSize());
	Render->SetImage("TitleBackground.bmp");

	//titleBG
}
