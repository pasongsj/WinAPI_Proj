#include "OpeningLevel.h"
#include <GameEngineBase/GameEngineDirectory.h>
#include <GameEngineCore/GameEngineResources.h>
#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEngineCore/GameEngineCore.h>
#include "TitleSubBack.h"
#include "ContentsEnums.h"

OpeningLevel::OpeningLevel()
{
}

OpeningLevel::~OpeningLevel()
{
}


void OpeningLevel::Loading() 
{
	{
		GameEngineDirectory Dir;
		Dir.MoveParentToDirectory("ContentsResources");
		Dir.Move("ContentsResources");
		Dir.Move("Image");
		Dir.Move("Title");
		Dir.Move("Opening");
		GameEngineImage* Image = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("TitleBackground.BMP"));
	}
	OpeningBackGround = CreateActor<TitleSubBack>(VSRenderOrder::BackGround);
}

void OpeningLevel::Update(float _DeltaTime)
{
	if (true == GameEngineInput::IsAnyKey())
	{
		GameEngineCore::GetInst()->ChangeLevel("TitleLevel");
		OpeningBackGround->Death(); // 다시 돌아오지 않을 페이지
	}
}