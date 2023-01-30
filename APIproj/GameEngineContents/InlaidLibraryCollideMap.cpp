#include "InlaidLibraryCollideMap.h"
#include "ContentsEnums.h"
#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEngineCore/GameEngineRender.h>

InlaidLibraryCollideMap::InlaidLibraryCollideMap() 
{
}

InlaidLibraryCollideMap::~InlaidLibraryCollideMap() 
{
}

void InlaidLibraryCollideMap::Start()
{
	float4 Size = GameEngineWindow::GetScreenSize();


	GameEngineRender* Render = CreateRender("InlaidLibraryCollision.bmp", BubbleRenderOrder::BackGround);
	Render->SetPosition(GameEngineWindow::GetScreenSize().half());
	//Render->SetScale(Render->GetImage()->GetImageScale());
	Render->SetScaleToImage();
}