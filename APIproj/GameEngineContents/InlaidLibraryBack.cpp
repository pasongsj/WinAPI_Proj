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
		RenPos = 0;
		IsRanderPos.insert(RenPos);
	}

}

void InlaidLibraryBack::Update(float _DeltaTime)
{
	int CamX = (GetLevel()->GetCameraPos()).x; // player�� ��ġ�� �� �� ����
	
	//RenderingMapPos Update
	RenPos = (CamX / BGSize.x);
	if (CamX < 0) {
		RenPos -= 1;
	}

	//���� ���� ������ �������� �ȵ����� ���
	if (CamX < BGSize.ix() * RenPos + 200 &&
		IsRanderPos.find(RenPos - 1) == IsRanderPos.end())
	{
		GameEngineRender* Render = CreateRender("InlaidLibraryStage.bmp", VSRenderOrder::BackGround);
		float4 LPos = BGSize.half(); //InlaidLibraryStage.bmp�� �߾�
		LPos.x += (RenPos -1) * BGSize.x; // ���� RenPos ���� (������) ����
		Render->SetPosition(LPos);
		Render->SetScaleToImage();
		IsRanderPos.insert(RenPos - 1);
	}

	//���� ���� ������ �������� �ȵ����� ���
	else if (CamX > BGSize.ix() * (RenPos + 1) - GameEngineWindow::GetScreenSize().ix() - 200 &&
		IsRanderPos.find(RenPos + 1) == IsRanderPos.end())
	{
		GameEngineRender* Render = CreateRender("InlaidLibraryStage.bmp", VSRenderOrder::BackGround);
		float4 RPos = BGSize.half(); //InlaidLibraryStage.bmp�� �߾�
		RPos.x += (RenPos + 1) * BGSize.x; // ���� RenPos ������ (������) ����
		Render->SetPosition(RPos);
		Render->SetScaleToImage();
		IsRanderPos.insert(RenPos + 1);
	}
}
