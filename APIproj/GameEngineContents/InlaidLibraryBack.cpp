#include "InlaidLibraryBack.h"
#include "ContentsEnums.h"
#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEngineCore/GameEngineRender.h>
#include <GameEngineCore/GameEngineLevel.h>

InlaidLibraryBack::InlaidLibraryBack()
{
}

InlaidLibraryBack::~InlaidLibraryBack()
{
}

void InlaidLibraryBack::Start()
{
	float4 Size = GameEngineWindow::GetScreenSize();

	{
		GameEngineRender* Render = CreateRender("InlaidLibraryStage.bmp", BubbleRenderOrder::BackGround);
		Render->SetPosition(Render->GetImage()->GetImageScale().half());
		Render->SetScaleToImage();
		//BG_Order.push_back(0);
	}
	//{
	//	GameEngineRender* Render = CreateRender("InlaidLibraryStage.bmp", BubbleRenderOrder::BackGround);
	//	//Render->SetPosition(GameEngineWindow::GetScreenSize().half());
	//	float4 LPos = Render->GetImage()->GetImageScale().half();
	//	LPos.x -= 4096;
	//	Render->SetPosition(LPos);
	//	//Render->SetScale(Render->GetImage()->GetImageScale());
	//	Render->SetScaleToImage();
	//}
}

void InlaidLibraryBack::Update(float _DeltaTime)
{

}
