#include "TitleSubBack.h"

#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEngineCore/GameEngineRender.h>
#include "ContentsEnums.h"

TitleSubBack::TitleSubBack() 
{
}

TitleSubBack::~TitleSubBack() 
{
}

void TitleSubBack::Start()
{
	GameEngineRender* Render = CreateRender("TitleBackGround.bmp", BubbleRenderOrder::BackGround);
	Render->SetPosition(GameEngineWindow::GetScreenSize().half());
	Render->SetScale(GameEngineWindow::GetScreenSize());
}