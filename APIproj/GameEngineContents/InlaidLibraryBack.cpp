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

	{
		EndingRender = CreateRender("introBG.bmp", VSRenderOrder::MAX);
		EndingRender->SetScaleToImage();
		EndingRender->EffectCameraOff();
		EndingRender->SetPosition(EndingRender->GetScale().half());
		EndingRender->SetAlpha(90);
		EndingRender->Off();
	}
	{
		float4 _Pos = GameEngineWindow::GetScreenSize().half();
		_Pos.y -= _Pos.y * (0.3f);
		EndingUI = CreateRender("GameOverText.bmp",VSRenderOrder::MAX);
		EndingUI->EffectCameraOff();
		EndingUI->SetScaleToImage();
		EndingUI->SetPosition(_Pos);
		//EndingUI->SetAlpha(99);
		EndingUI->Off();
	}
	

}

void InlaidLibraryBack::Update(float _DeltaTime)
{
	if (nullptr == MainBackGroundRender || nullptr == RemainBackGroundRender) {
		MsgAssert("InlaidLibraryStage 배경이 렌더되지 않았습니다.");
		return;
	}
	float CamX = (GetLevel()->GetCameraPos()).x + GameEngineWindow::GetScreenSize().hx(); // player의 위치 
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

void InlaidLibraryBack::SetEndingRenderOn(bool _IsComplete)
{
	if (true == _IsComplete)
	{
		EndingUI->SetImage("stageComplete.bmp");
	}
	EndingRender->On();
	EndingUI->On();
}