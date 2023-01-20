#include "InlaidLibraryBack.h"
#include "ContentsEnums.h"
#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEngineCore/GameEngineRender.h>

InlaidLibraryBack::InlaidLibraryBack()
{
}

InlaidLibraryBack::~InlaidLibraryBack()
{
}

void InlaidLibraryBack::Start()
{
	float4 Size = GameEngineWindow::GetScreenSize();


	GameEngineRender* Render = CreateRender("InlaidLibraryStage.bmp", BubbleRenderOrder::BackGround);
	Render->SetPosition(GameEngineWindow::GetScreenSize().half());
	Render->SetScale(GameEngineWindow::GetScreenSize()); // 464

}