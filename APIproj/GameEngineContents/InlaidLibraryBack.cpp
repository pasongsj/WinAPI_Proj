#include "InlaidLibraryBack.h"
#include "ContentsEnums.h"
#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEngineCore/GameEngineRender.h>
#include <GameEngineCore/GameEngineLevel.h>
#include <cmath>
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
		GameEngineRender* Render = CreateRender("InlaidLibraryStage.bmp", VSRenderOrder::BackGround);
		Render->SetPosition(Render->GetImage()->GetImageScale().half());
		Render->SetScaleToImage();
		BGSize = Render->GetImage()->GetImageScale();
		IsRanderPos.insert(0);
	}

}

void InlaidLibraryBack::Update(float _DeltaTime)
{
	int CamX = (GetLevel()->GetCameraPos()).x;
	int RenderPos = (CamX / BGSize.x);
	if (CamX < 0) {
		RenderPos -= 1;
	}
	CamX = ((CamX % BGSize.ix()) + BGSize.ix()) % BGSize.ix();


	if (CamX < +200 && 
		IsRanderPos.find(RenderPos-1) == IsRanderPos.end()) 
	{
		GameEngineRender* Render = CreateRender("InlaidLibraryStage.bmp", VSRenderOrder::BackGround);
		float4 LPos = Render->GetImage()->GetImageScale().half();
		LPos.x += --RenderPos * BGSize.x;
		Render->SetPosition(LPos);
		Render->SetScaleToImage();
		IsRanderPos.insert(RenderPos);
	}
	else if (CamX > BGSize.ix()- GameEngineWindow::GetScreenSize().ix() - 200 && 
			IsRanderPos.find(RenderPos + 1) == IsRanderPos.end()) 
	{
		GameEngineRender* Render = CreateRender("InlaidLibraryStage.bmp", VSRenderOrder::BackGround);
		float4 RPos = Render->GetImage()->GetImageScale().half();
		RPos.x += ++RenderPos * BGSize.x;
		Render->SetPosition(RPos);
		Render->SetScaleToImage();
		IsRanderPos.insert(RenderPos);
	}

}
