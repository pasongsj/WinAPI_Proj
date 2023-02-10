#include "InlaidLibraryLevel.h"
#include <GameEngineBase/GameEngineDirectory.h>
#include <GameEngineCore/GameEngineResources.h>
#include <GameEngineCore/GameEngineCore.h>
#include <GameEnginePlatform/GameEngineInput.h>

#include "InlaidLibraryBack.h"
#include "Player.h"
#include "ContentsEnums.h"
#include "Monster.h"
#include "PlayGameUI.h"

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

	if (false == GameEngineInput::IsKey("DebugRenderSwitch"))
	{
		GameEngineInput::CreateKey("DebugRenderSwitch", 'R');
	}

	float4 BGSize = float4::Zero;
	// 이미지 로드
	GameEngineDirectory Dir;
	Dir.MoveParentToDirectory("ContentsResources");
	Dir.Move("ContentsResources");
	Dir.Move("Image");
	{
		// 배경이미지 로드
		Dir.MoveParentToDirectory("InlaidLibrary");
		Dir.Move("InlaidLibrary");
		GameEngineImage* Image = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("InlaidLibraryStage.BMP"));
		GameEngineImage* ColImage = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("InlaidLibraryCollision.BMP"));
		BGSize = Image->GetImageScale();
	}

	{
		// 캐릭터 이미지 로드
		Dir.MoveParentToDirectory("Player");
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
	
	{
		// 몬스터 이미지 로드
		Dir.MoveParentToDirectory("Monster");
		Dir.Move("Monster");
		{
			GameEngineImage* Image = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("RightDustElemental.BMP"));
			Image->Cut(2, 1);
		}
		{
			GameEngineImage* Image = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("LeftDustElemental.BMP"));
			Image->Cut(2, 1);
		}

		{
			GameEngineImage* Image = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("RightDustElementalDead.BMP"));
			Image->Cut(5, 2);
		}
		{
			GameEngineImage* Image = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("LeftDustElementalDead.BMP"));
			Image->Cut(5, 2);
		}
	}

	{
		// UI 이미지 로드
		Dir.MoveParentToDirectory("Title");
		Dir.Move("Title");
		GameEngineImage* Image = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("ExpBar.BMP"));
		GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("colon.BMP"));
		GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("LV.BMP"));
		//Image = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("ExpBarBlue.BMP"));
	}

	{ // UI - 맵 숫자 이미지 로드
		Dir.MoveParentToDirectory("InlaidLibrary");
		Dir.Move("InlaidLibrary");
		GameEngineImage* Image2 = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("Number.BMP"));
		Image2->Cut(10, 1);
	}

	{
		InlaidLibraryBack* BackGround = CreateActor<InlaidLibraryBack>(); // 가시적 배경
	}

	{
		PlayGameUI* NewUI = CreateActor<PlayGameUI>();
	}

	{
		Player* NewPlayer = CreateActor<Player>(VSRenderOrder::Player); // 플레이어
		NewPlayer->SetMove(BGSize.half()); // 화면 중간위치로 이동
	}

	SetCameraPos((BGSize - GameEngineWindow::GetScreenSize()).half()); // 카메라 위치 중간으로 이동

	{
		for (int i = 0;i < 15 ;i++) 
		{
			Monster* Actor = CreateActor<Monster>(VSRenderOrder::Monster);

			/*Actor->SetMove(
				BGSize.half() + float4(static_cast<float>(rand() % GameEngineWindow::GetScreenSize().hix()), static_cast<float>(rand() % GameEngineWindow::GetScreenSize().hiy()))
			);*/
		}
	}

}

void InlaidLibraryLevel::Update(float _DeltaTime)
{
	if (true == GameEngineInput::IsDown("LevelChange")) // - 임시 레벨 체인지 기능
	{
		GameEngineCore::GetInst()->ChangeLevel("TitleLevel");
	}

	if (GameEngineInput::IsDown("DebugRenderSwitch"))
	{
		DebugRenderSwitch();
		// Player::MainPlayer->Death()p;
	}
}

void InlaidLibraryLevel::LevelChangeStart(GameEngineLevel* _PrevLevel)
{
	int a = 0;
}