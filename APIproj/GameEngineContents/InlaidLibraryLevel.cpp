#include "InlaidLibraryLevel.h"
#include <GameEngineBase/GameEngineDirectory.h>
#include <GameEngineBase/GameEngineFile.h>
#include <GameEngineCore/GameEngineResources.h>
#include <GameEngineCore/GameEngineCore.h>
#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEngineCore/GameEngineCollision.h>

#include "InlaidLibraryBack.h"
#include "Player.h"
#include "ContentsEnums.h"
#include "Monster.h"
#include "PlayGameUI.h"
#include "Weapon.h"
#include  "Items.h"

#include "WeaponWhip.h"
#include "WeaponMagicWand.h"

InlaidLibraryLevel::InlaidLibraryLevel()
{
}

InlaidLibraryLevel::~InlaidLibraryLevel()
{
}
void InlaidLibraryLevel::ImageLoad()
{

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
		BGSize = Image->GetImageScale(); // AllImage에서 find로 찾아서 설정하면 될듯?
	}

	{
		// 캐릭터 이미지 로드
		Dir.MoveParentToDirectory("Player");
		Dir.Move("Player");

		std::vector<GameEngineFile> Files = Dir.GetAllFile();

		for (size_t i = 0; i < Files.size(); i++)
		{
			GameEngineImage* Image = GameEngineResources::GetInst().ImageLoad(Files[i].GetFullPath());
			Image->Cut(4, 1);
		}
		/*{
			GameEngineImage* Image = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("RightAntonio.BMP"));
			Image->Cut(4, 1);
		}
		{
			GameEngineImage* Image = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("LeftAntonio.BMP"));
			Image->Cut(4, 1);
		}*/

	}

	{
		// 몬스터 이미지 로드
		Dir.MoveParentToDirectory("Monster");
		Dir.Move("Monster");
		// MoveState
		{
			GameEngineImage* Image = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("RightDust.BMP"));
			Image->Cut(2, 1);
		}
		{
			GameEngineImage* Image = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("LeftDust.BMP"));
			Image->Cut(2, 1);
		}
		// BeatenState
		{
			GameEngineImage* Image = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("RightDustDmged.BMP"));
			Image->Cut(2, 1);
		}
		{
			GameEngineImage* Image = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("LeftDustDmged.BMP"));
			Image->Cut(2, 1);
		}
		//DeadState
		{
			GameEngineImage* Image = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("RightDustDead.BMP"));
			Image->Cut(5, 2);
		}
		{
			GameEngineImage* Image = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("LeftDustDead.BMP"));
			Image->Cut(5, 2);
		}
	}

	{
		// UI 이미지 로드
		Dir.MoveParentToDirectory("UI");
		Dir.Move("UI");
		GameEngineImage* Image = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("ExpBar.BMP"));
		GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("colon.BMP"));
		GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("LV.BMP"));
		GameEngineImage* Image2 = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("Number.BMP"));
		Image2->Cut(10, 1);
		//Image = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("ExpBarBlue.BMP"));
	}

	//{ // UI - 맵 숫자 이미지 로드
	//	Dir.MoveParentToDirectory("InlaidLibrary");
	//	Dir.Move("InlaidLibrary");
	//}

	{
		Dir.MoveParentToDirectory("Weapon");
		Dir.Move("Weapon");
		std::vector<GameEngineFile> Files = Dir.GetAllFile();

		for (size_t i = 0; i < Files.size(); i++)
		{
			GameEngineImage* Image = GameEngineResources::GetInst().ImageLoad(Files[i].GetFullPath());
			Image->Cut(1, 6);
		}
		{
			Dir.Move("MagicWand");
			GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("MagicWandTmp.BMP"));
		}
		/*GameEngineImage* Image = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("Whip.BMP"));
		Image->Cut(1, 3);*/
	}

	{

	}

	{
		Dir.MoveParentToDirectory("Item");
		Dir.Move("Item");
		GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("exp0.BMP"));
	}
}

void InlaidLibraryLevel::SoundLoad()
{
	//GameEngineDirectory Dir;
	//Dir.MoveParentToDirectory("ContentsResources");
	//Dir.Move("ContentsResources");
	//Dir.Move("Sound");

	//GameEngineResources::GetInst().SoundLoad(Dir.GetPlusFileName("intro.mp3"));

}


void InlaidLibraryLevel::Loading()
{
	ImageLoad();
	SoundLoad();
	// 만들어야할 것들을 만드는 시점이 Loading시점

	if (false == GameEngineInput::IsKey("StopDebug")) // - 임시 : 레벨체인지 
	{
		GameEngineInput::CreateKey("StopDebug", 'P');
		//GameEngineInput::CreateKey("RLevelChange", 'I');
	}
	

	if (false == GameEngineInput::IsKey("DebugRenderSwitch"))
	{
		GameEngineInput::CreateKey("DebugRenderSwitch", 'R');
	}

	{
		CreateActor<WeaponWhip>(VSRenderOrder::Weapon);
		CreateActor<WeaponMagicWand>(VSRenderOrder::Weapon);
	}

	{
		InlaidLibraryBack* BackGround = CreateActor<InlaidLibraryBack>(VSRenderOrder::BackGround); // 가시적 배경
	}

	{
		PlayGameUI* NewUI = CreateActor<PlayGameUI>(VSRenderOrder::UI);
	}

	//{
	//	Player* NewPlayer = CreateActor<Player>(VSRenderOrder::Player); // 플레이어
	//	NewPlayer->SetMove(BGSize.half()); // 화면 중간위치로 이동
	//}

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
	if (true == GameEngineInput::IsDown("StopDebug"))
	{
		Player::IsStop = !Player::IsStop;
	}

	if (true == Player::IsStop)
	{
		//GameEngineCore::GetInst()->ChangeLevel("TitleLevel");
		SetTimeScale(VSRenderOrder::BackGround, 0);
		SetTimeScale(VSRenderOrder::Map, 0);
		SetTimeScale(VSRenderOrder::Player, 0);
		SetTimeScale(VSRenderOrder::Monster, 0);
		SetTimeScale(VSRenderOrder::Item, 0);
		SetTimeScale(VSRenderOrder::Weapon, 0);
		SetTimeScale(VSRenderOrder::UI, 0);
	}
	else
	{
		SetTimeScale(VSRenderOrder::BackGround, 1);
		SetTimeScale(VSRenderOrder::Map, 1);
		SetTimeScale(VSRenderOrder::Player, 1);
		SetTimeScale(VSRenderOrder::Monster, 1);
		SetTimeScale(VSRenderOrder::Item, 1);
		SetTimeScale(VSRenderOrder::Weapon, 1);
		SetTimeScale(VSRenderOrder::UI, 1);
	}

	if (GameEngineInput::IsDown("DebugRenderSwitch"))
	{
		DebugRenderSwitch();
		/*if (false == BGMPlayer.GetPause())
		{
			BGMPlayer.PauseOn();
		}
		else
		{
			BGMPlayer.PauseOff();
		}*/
	}

}

void InlaidLibraryLevel::LevelChangeStart(GameEngineLevel* _PrevLevel)
{
	{
		Player* NewPlayer = CreateActor<Player>(VSRenderOrder::Player); // 플레이어
		NewPlayer->SetMove(BGSize.half()); // 화면 중간위치로 이동
	}
	/*int a = 0;
	BGMPlayer = GameEngineResources::GetInst().SoundPlayToControl("intro.mp3");
	BGMPlayer.LoopCount(100);*/
}