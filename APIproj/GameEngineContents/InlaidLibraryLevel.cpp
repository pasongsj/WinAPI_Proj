#include "InlaidLibraryLevel.h"
#include <GameEngineBase/GameEngineDirectory.h>
#include <GameEngineCore/GameEngineResources.h>
#include <GameEngineCore/GameEngineCore.h>
#include <GameEnginePlatform/GameEngineInput.h>

#include "InlaidLibraryBack.h"
#include "Player.h"
#include "ContentsEnums.h"
#include "Monster.h"

InlaidLibraryLevel::InlaidLibraryLevel()
{
}

InlaidLibraryLevel::~InlaidLibraryLevel()
{
}


void InlaidLibraryLevel::Loading()
{
	// �������� �͵��� ����� ������ Loading����

	if (false == GameEngineInput::IsKey("LevelChange")) // - �ӽ� : ����ü���� 
	{
		GameEngineInput::CreateKey("LevelChange", 'P');
	}
	float4 BGSize = float4::Zero;
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
		InlaidLibraryBack* BackGround = CreateActor<InlaidLibraryBack>(); // ������ ���
	}
	//{
	//	//InlaidLibraryCollideMap* MapCollision = CreateActor<InlaidLibraryCollideMap>(); // �浹 ��� ���� Ȯ�ο�
	//}
	{
		Player* NewPlayer = CreateActor<Player>(VSRenderOrder::Player); // �÷��̾�
		NewPlayer->SetMove(BGSize.half()); // ȭ�� �߰���ġ�� �̵�
	}
	SetCameraPos((BGSize - GameEngineWindow::GetScreenSize()).half()); // ī�޶� ��ġ �߰����� �̵�

	{
		Monster* Actor = CreateActor<Monster>(VSRenderOrder::Monster);

		Actor->SetMove(
			BGSize.half() + float4(static_cast<float>(rand() % GameEngineWindow::GetScreenSize().hix()), static_cast<float>(rand() % GameEngineWindow::GetScreenSize().hiy()))
		);
	}

}

void InlaidLibraryLevel::Update(float _DeltaTime)
{
	if (true == GameEngineInput::IsDown("LevelChange")) // - �ӽ� ���� ü���� ���
	{
		GameEngineCore::GetInst()->ChangeLevel("TitleLevel");
	}

}
