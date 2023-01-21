#include "TitleLevel.h"

#include <GameEngineBase/GameEngineDirectory.h>
#include <GameEngineCore/GameEngineResources.h>
#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEngineCore/GameEngineCore.h>

#include "TitleSubBack.h"
#include "TitleMainBack.h"

TitleLevel::TitleLevel()
{
}

TitleLevel::~TitleLevel()
{
}

void TitleLevel::Loading()
{
	// �������� �͵��� ����� ������ Loading����
	// 
	if (false == GameEngineInput::IsKey("LevelChange"))
	{
		GameEngineInput::CreateKey("LevelChange", 'P');
	}
	// back�̹��� �ε�

	GameEngineDirectory Dir;
	{
		Dir.MoveParentToDirectory("ContentsResources");
		Dir.Move("ContentsResources");
		Dir.Move("Image");
		Dir.Move("Title");
		GameEngineImage* Image = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("TitleMainBackGround.BMP"));

		Image = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("TitleBackGround.BMP"));
	}

	CreateActor<TitleSubBack>();
}

void TitleLevel::Update(float _DeltaTime)
{
	if (true == GameEngineInput::IsAnyKey())
	{
		CreateActor<TitleMainBack>();
	}

	if (true == GameEngineInput::IsDown("LevelChange"))
	{
		GameEngineCore::GetInst()->ChangeLevel("InlaidLibraryLevel");
	}
	
}