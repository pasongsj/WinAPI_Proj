#include "GameEngineRender.h"
#include "GameEngineActor.h"
#include "GameEngineLevel.h"
#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEngineCore/GameEngineResources.h>

GameEngineRender::GameEngineRender()
{
}

GameEngineRender::~GameEngineRender()
{
}


void GameEngineRender::SetOrder(int _Order)
{
	Order = _Order;
	Owner->GetLevel()->PushRender(this); // actor levelÀÇ private¸É¹öÇÔ¼ö
}

void GameEngineRender::Render(float _DeltaTime)
{
	float4 RenderPos = Owner->GetPos() + Position;

	if (true == Image->IsImageCutting())
	{
		GameEngineWindow::GetDoubleBufferImage()->TransCopy(Image, Frame, RenderPos, Scale);
	}
	else
	{
		GameEngineWindow::GetDoubleBufferImage()->TransCopy(Image, RenderPos, { 100, 200 }, { 0, 0 }, Image->GetImageScale());
	}
}

void GameEngineRender::SetImage(const std::string_view& _ImageName)
{
	Image = GameEngineResources::GetInst().ImageFind(_ImageName);
}