#include "InlaidLibraryLevel.h"
#include "InlaidLibraryBack.h"
#include "Player.h"
#include "InlaidLibraryCollideMap.h"
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

	if (false == GameEngineInput::IsKey("LevelChange")) // - 임시 : 레벨체인지 
	{
		GameEngineInput::CreateKey("LevelChange", 'P');
	}

	/*if (false == GameEngineInput::IsKey("CameraLeftMove")) // 시점(카메라) 버튼 이동
	{
		GameEngineInput::CreateKey("CameraLeftMove", VK_LEFT);
		GameEngineInput::CreateKey("CameraRightMove", VK_RIGHT);
		GameEngineInput::CreateKey("CameraDownMove", VK_DOWN);
		GameEngineInput::CreateKey("CameraUpMove", VK_UP);
	}*/

	// 이미지 로드
	{
		GameEngineDirectory Dir; // 배경이미지 로드
		Dir.MoveParentToDirectory("ContentsResources");
		Dir.Move("ContentsResources");
		Dir.Move("Image");
		Dir.Move("InlaidLibrary");
		GameEngineImage* Image = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("InlaidLibraryStage.BMP"));
		GameEngineImage* ColImage = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("InlaidLibraryCollision.BMP"));
	}

	{
		GameEngineDirectory Dir; // 캐릭터 이미지 로드
		Dir.MoveParentToDirectory("ContentsResources");
		Dir.Move("ContentsResources");
		Dir.Move("Image");
		Dir.Move("Player");
		{
			GameEngineImage* Image = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("RightAntonio.BMP"));
			Image->Cut(4, 1);
		}
		{
			GameEngineImage* Image = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("LeftAntonio.BMP"));
			Image->Cut(4, 1);
		}
	}
	InlaidLibraryCollideMap* MapCollision = CreateActor<InlaidLibraryCollideMap>(); // 충돌 배경 
	InlaidLibraryBack* BackGround = CreateActor<InlaidLibraryBack>(); // 가시적 배경

	Player* NewPlayer = CreateActor<Player>(); // 플레이어
}

void InlaidLibraryLevel::Update(float _DeltaTime)
{
	if (true == GameEngineInput::IsDown("LevelChange")) // - 임시 레벨 체인지 기능
	{
		GameEngineCore::GetInst()->ChangeLevel("TitleLevel");
	}

}
