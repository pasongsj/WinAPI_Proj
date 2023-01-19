#include "InlaidLibraryLevel.h"
#include "InlaidLibraryBack.h"
#include "Player.h"
#include <GameEngineBase/GameEngineDirectory.h>
#include <GameEngineCore/GameEngineResources.h>
#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEngineCore/GameEngineCore.h>

InlaidLibraryLevel::InlaidLibraryLevel()
{
}

InlaidLibraryLevel::~InlaidLibraryLevel()
{
}


void InlaidLibraryLevel::Loading()
{
	// 만들어야할 것들을 만드는 시점이 Loading시점

	if (false == GameEngineInput::IsKey("LevelChange"))
	{
		GameEngineInput::CreateKey("LevelChange", 'P');
	}

	if (false == GameEngineInput::IsKey("CameraLeftMove"))
	{
		GameEngineInput::CreateKey("CameraLeftMove", VK_LEFT);
		GameEngineInput::CreateKey("CameraRightMove", VK_RIGHT);
		GameEngineInput::CreateKey("CameraDownMove", VK_DOWN);
		GameEngineInput::CreateKey("CameraUpMove", VK_UP);
	}

	// 이미지 로드
	GameEngineDirectory Dir;
	{
		Dir.MoveParentToDirectory("ContentsResources");
		Dir.Move("ContentsResources");
		Dir.Move("Image");
		Dir.Move("InlaidLibrary");
		GameEngineImage* Image = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("InlaidLibraryStage.BMP"));
	}

	{
		Dir.MoveParentToDirectory("ContentsResources");
		Dir.Move("ContentsResources");
		Dir.Move("Image");
		Dir.Move("Player");
		GameEngineImage* Image = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("RightAntonio.BMP"));
		Image->Cut(4, 1);
	}
	{
		Dir.MoveParentToDirectory("ContentsResources");
		Dir.Move("ContentsResources");
		Dir.Move("Image");
		Dir.Move("Player");
		GameEngineImage* Image = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("LeftAntonio.BMP"));
		Image->Cut(4, 1);
	}
	CreateActor<InlaidLibraryBack>();
	CreateActor<Player>();
}

void InlaidLibraryLevel::Update(float _DeltaTime)
{
	if (true == GameEngineInput::IsDown("LevelChange"))
	{
		GameEngineCore::GetInst()->ChangeLevel("TitleLevel");
	}

	//
	float CameraMoveSpeed = 100.0f;
	float4 CameraMoveResult = float4::Zero;
	if (true == GameEngineInput::IsPress("CameraLeftMove"))
	{
		CameraMoveResult += float4::Left;
	}
	if (true == GameEngineInput::IsPress("CameraRightMove"))
	{
		CameraMoveResult += float4::Right;
	}
	if (true == GameEngineInput::IsPress("CameraDownMove"))
	{
		CameraMoveResult += float4::Down;
	}
	if (true == GameEngineInput::IsPress("CameraUpMove"))
	{
		CameraMoveResult += float4::Up;
	}
	SetCameraMove(CameraMoveResult * _DeltaTime * CameraMoveSpeed);

}
