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
	//Render->SetPosition(GameEngineWindow::GetScreenSize().half());
	Render->SetPosition(Render->GetImage()->GetImageScale().half());
	//Render->SetScale(Render->GetImage()->GetImageScale());
	Render->SetScaleToImage();
}