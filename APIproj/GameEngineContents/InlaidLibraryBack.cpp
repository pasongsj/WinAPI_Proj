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
	//float4 Size = GameEngineWindow::GetScreenSize();
	{
		MainBackGroundRender = CreateRender("InlaidLibraryStage.bmp", VSRenderOrder::BackGround);
		MainBackGroundRender->SetPosition(MainBackGroundRender->GetImage()->GetImageScale().half());
		MainBackGroundRender->SetScaleToImage();
		BGSize = MainBackGroundRender->GetImage()->GetImageScale();
		lim = static_cast<float>(BGSize.hix() - GameEngineWindow::GetScreenSize().hix());
	}
	{
		RemainBackGroundRender = CreateRender("InlaidLibraryStage.bmp", VSRenderOrder::BackGround);
		float4 LeftPos = RemainBackGroundRender->GetImage()->GetImageScale().half();
		LeftPos.x -= BGSize.x;
		RemainBackGroundRender->SetPosition(LeftPos);
		RemainBackGroundRender->SetScaleToImage();
	}
	

}

void InlaidLibraryBack::Update(float _DeltaTime)
{
	float CamX = (GetLevel()->GetCameraPos()).x + GameEngineWindow::GetScreenSize().hx(); // playerÀÇ À§Ä¡ 
	if ((RemainBackGroundRender->GetPosition() - BGSize.half()).x < CamX && CamX < (RemainBackGroundRender->GetPosition() + BGSize.half()).x) {
		GameEngineRender* tmp = MainBackGroundRender;
		MainBackGroundRender = RemainBackGroundRender;
		RemainBackGroundRender = tmp;
	}

	float4 NextRenderPos = MainBackGroundRender->GetPosition();
	if (CamX - MainBackGroundRender->GetPosition().x > lim)
	{
		NextRenderPos.x += BGSize.x;
	}
	else if (CamX - MainBackGroundRender->GetPosition().x < -lim) {
		NextRenderPos.x -= BGSize.x;
	}

	if (NextRenderPos != RemainBackGroundRender->GetPosition()) {
		RemainBackGroundRender->SetPosition(NextRenderPos);
	}
	
}
