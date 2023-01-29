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
	// �������� �͵��� ����� ������ Loading����

	if (false == GameEngineInput::IsKey("LevelChange")) // - �ӽ� : ����ü���� 
	{
		GameEngineInput::CreateKey("LevelChange", 'P');
	}

	/*if (false == GameEngineInput::IsKey("CameraLeftMove")) // ����(ī�޶�) ��ư �̵�
	{
		GameEngineInput::CreateKey("CameraLeftMove", VK_LEFT);
		GameEngineInput::CreateKey("CameraRightMove", VK_RIGHT);
		GameEngineInput::CreateKey("CameraDownMove", VK_DOWN);
		GameEngineInput::CreateKey("CameraUpMove", VK_UP);
	}*/

	// �̹��� �ε�
	{
		GameEngineDirectory Dir; // ����̹��� �ε�
		Dir.MoveParentToDirectory("ContentsResources");
		Dir.Move("ContentsResources");
		Dir.Move("Image");
		Dir.Move("InlaidLibrary");
		GameEngineImage* Image = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("InlaidLibraryStage.BMP"));
		GameEngineImage* ColImage = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("InlaidLibraryCollision.BMP"));
	}

	{
		GameEngineDirectory Dir; // ĳ���� �̹��� �ε�
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
	InlaidLibraryCollideMap* MapCollision = CreateActor<InlaidLibraryCollideMap>(); // �浹 ��� 
	InlaidLibraryBack* BackGround = CreateActor<InlaidLibraryBack>(); // ������ ���

	Player* NewPlayer = CreateActor<Player>(); // �÷��̾�
}

void InlaidLibraryLevel::Update(float _DeltaTime)
{
	if (true == GameEngineInput::IsDown("LevelChange")) // - �ӽ� ���� ü���� ���
	{
		GameEngineCore::GetInst()->ChangeLevel("TitleLevel");
	}

}
