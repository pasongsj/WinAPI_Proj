#include "TitleMainBack.h"

#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEngineCore/GameEngineRender.h>
#include "ContentsEnums.h"

TitleMainBack::TitleMainBack() 
{
}

TitleMainBack::~TitleMainBack() 
{
}


void TitleMainBack::Start()
{
	GameEngineRender* Render = CreateRender("TitleMainBackGround.bmp", BubbleRenderOrder::BackGround);
	Render->SetPosition(GameEngineWindow::GetScreenSize().half());
	Render->SetScale(GameEngineWindow::GetScreenSize());
}