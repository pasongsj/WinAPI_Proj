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
	//{
	//	GameEngineRender* Render = CreateRender("InlaidLibraryStage.bmp", VSRenderOrder::BackGround);
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
	int RandPos = 0;
	int CamX = (GetLevel()->GetCameraPos()).x;

	if (CamX < 0) {
		RandPos -= 1;
	}
	RandPos += (CamX / BGSize.x);

	CamX = ((CamX % BGSize.ix()) + BGSize.ix()) % BGSize.ix();


	if (CamX < +200 && IsRanderPos.find(RandPos-1) == IsRanderPos.end()) {
		--RandPos;
		GameEngineRender* Render = CreateRender("InlaidLibraryStage.bmp", VSRenderOrder::BackGround);
		float4 LPos = Render->GetImage()->GetImageScale().half();
		LPos.x += RandPos * BGSize.x;
		Render->SetPosition(LPos);
		Render->SetScaleToImage();
		IsRanderPos.insert(RandPos);
		int a = 0;
	}
	else if (CamX > BGSize.ix()- GameEngineWindow::GetScreenSize().ix() - 200 && IsRanderPos.find(RandPos + 1) == IsRanderPos.end()) {
		++RandPos;
		GameEngineRender* Render = CreateRender("InlaidLibraryStage.bmp", VSRenderOrder::BackGround);
		float4 LPos = Render->GetImage()->GetImageScale().half();
		LPos.x += RandPos * BGSize.x;
		Render->SetPosition(LPos);
		Render->SetScaleToImage();
		IsRanderPos.insert(RandPos);
		int a = 0;
	}
	//if ((GetLevel()->GetCameraPos()).x < 0.0f /*|| (GetLevel()->GetCameraPos()).x + GameEngineWindow::GetScreenSize().x > 4096.0f*/) {
	//	int a = 0;
	//}
	//if ((GetLevel()->GetCameraPos()).x + GameEngineWindow::GetScreenSize().x > 4096.0f) {
	//	int a = 0;
	//}

	/*if (abs(2048.0f - (GetLevel()->GetCameraPos()).x + GameEngineWindow::GetScreenSize().half().x) < GameEngineWindow::GetScreenSize().half().x) {
		int a = 0;
	}*/

}
