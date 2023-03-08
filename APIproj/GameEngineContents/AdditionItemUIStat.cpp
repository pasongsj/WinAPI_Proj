#include "ContentsEnums.h"
#include "AdditionItemUI.h"
#include <GameEnginePlatform/GameEngineWindow.h>

void AdditionItemUI::SetStatNumber()
{
	float interval = 18.6f;
	GameEngineRender* ZeroPoint = CreateRender("0point.bmp",VSRenderOrder::MAX);
	ZeroPoint->SetScaleToImage();
	ZeroPoint->EffectCameraOff();

	float4 ActiveStatUIPos = { 210,205 };
	for (int i = 0; i < 17; i++)
	{
		if (1 == i)
		{
			ZeroPoint->SetPosition(ActiveStatUIPos - float4{27, 0});
		}

		ActiveStatUI[i].SetOrder(static_cast<int> (VSRenderOrder::MAX));
		float4 BarPos = GameEngineWindow::GetScreenSize().half();
		//BarPos.y -= 55;
		ActiveStatUI[i].SetOwner(this);
		ActiveStatUI[i].SetImage("Number.BMp", { 12, 15 }, static_cast<int>(VSRenderOrder::MAX), RGB(255, 0, 255), "Negative.bmp", "Percent.bmp");
		ActiveStatUI[i].SetRenderPos(ActiveStatUIPos);
		ActiveStatUI[i].SetAlign(Align::Right);
		ActiveStatUI[i].SetValue(0);


		ActiveStatUIPos.y += interval;
		if ((3 == i) || (i == 9) || (i == 12) || (i == 13))
		{
			ActiveStatUIPos.y += interval;
		}
	}
}