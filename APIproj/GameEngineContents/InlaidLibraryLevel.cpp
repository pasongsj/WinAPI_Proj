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
#include "Weapon.h"

InlaidLibraryLevel::InlaidLibraryLevel()
{
}

InlaidLibraryLevel::~InlaidLibraryLevel()
{
}
void InlaidLibraryLevel::ImageLoad()
{
	// �̹��� �ε�
	GameEngineDirectory Dir;
	Dir.MoveParentToDirectory("ContentsResources");
	Dir.Move("ContentsResources");
	Dir.Move("Image");
	{
		// ����̹��� �ε�
		Dir.MoveParentToDirectory("InlaidLibrary");
		Dir.Move("InlaidLibrary");
		GameEngineImage* Image = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("InlaidLibraryStage.BMP"));
		GameEngineImage* ColImage = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("InlaidLibraryCollision.BMP"));
		BGSize = Image->GetImageScale();
	}

	{
		// ĳ���� �̹��� �ε�
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
		// ���� �̹��� �ε�
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
		// UI �̹��� �ε�
		Dir.MoveParentToDirectory("Title");
		Dir.Move("Title");
		GameEngineImage* Image = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("ExpBar.BMP"));
		GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("colon.BMP"));
		GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("LV.BMP"));
		//Image = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("ExpBarBlue.BMP"));
	}

	{ // UI - �� ���� �̹��� �ε�
		Dir.MoveParentToDirectory("InlaidLibrary");
		Dir.Move("InlaidLibrary");
		GameEngineImage* Image2 = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("Number.BMP"));
		Image2->Cut(10, 1);
	}

	{
		Dir.MoveParentToDirectory("Weapon");
		Dir.Move("Weapon");
		GameEngineImage* Image = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("Whip.BMP"));
		Image->Cut(1, 3);
	}
}


void InlaidLibraryLevel::Loading()
{
	ImageLoad();
	// �������� �͵��� ����� ������ Loading����

	if (false == GameEngineInput::IsKey("LevelChange")) // - �ӽ� : ����ü���� 
	{
		GameEngineInput::CreateKey("LevelChange", 'P');
	}

	if (false == GameEngineInput::IsKey("DebugRenderSwitch"))
	{
		GameEngineInput::CreateKey("DebugRenderSwitch", 'R');
	}

	{
		Weapon* NewWeapon = CreateActor<Weapon>(VSRenderOrder::Weapon);
		NewWeapon->SetImage("Right_Whip", "Whip.bmp", 0, 2, 0.1f);
		NewWeapon->SetRenderScale({ 314, 280 });
		NewWeapon->SetCollisionScale({ 280, 60 });
		Weapon::Weapons["Whip"] = NewWeapon;

	}

	{
		InlaidLibraryBack* BackGround = CreateActor<InlaidLibraryBack>(); // ������ ���
	}

	{
		PlayGameUI* NewUI = CreateActor<PlayGameUI>();
	}

	{
		Player* NewPlayer = CreateActor<Player>(VSRenderOrder::Player); // �÷��̾�
		NewPlayer->SetMove(BGSize.half()); // ȭ�� �߰���ġ�� �̵�
	}

	SetCameraPos((BGSize - GameEngineWindow::GetScreenSize()).half()); // ī�޶� ��ġ �߰����� �̵�

	{
		for (int i = 0;i < 1 ;i++) 
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
	if (true == GameEngineInput::IsDown("LevelChange")) // - �ӽ� ���� ü���� ���
	{
		GameEngineCore::GetInst()->ChangeLevel("TitleLevel");
	}

	if (GameEngineInput::IsDown("DebugRenderSwitch"))
	{
		DebugRenderSwitch();
	}
}

void InlaidLibraryLevel::LevelChangeStart(GameEngineLevel* _PrevLevel)
{
	int a = 0;
}