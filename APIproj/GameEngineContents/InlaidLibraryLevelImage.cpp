#include "InlaidLibraryLevel.h"
#include <GameEngineBase/GameEngineDirectory.h>
#include <GameEngineBase/GameEngineFile.h>

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
		std::vector<GameEngineFile> Files = Dir.GetAllFile();
		for (size_t i = 0; i < Files.size(); i++)
		{
			GameEngineImage* Image = GameEngineResources::GetInst().ImageLoad(Files[i].GetFullPath());
		}

		GameEngineImage* Image = GameEngineResources::GetInst().ImageFind("InlaidLibraryStage.BMP");
		BGSize = Image->GetImageScale();

	}

	{
		// ĳ���� �̹��� �ε�
		Dir.MoveParentToDirectory("Player");
		Dir.Move("Player");
		Dir.Move("Characters");

		std::vector<GameEngineFile> Files = Dir.GetAllFile();

		for (size_t i = 0; i < Files.size(); i++)
		{
			GameEngineImage* Image = GameEngineResources::GetInst().ImageLoad(Files[i].GetFullPath());
			Image->Cut(4, 1);
		}

		Dir.MoveParentToDirectory("Addition");
		Dir.Move("Addition");

		Files.clear();
		Files = Dir.GetAllFile();
		for (size_t i = 0; i < Files.size(); i++)
		{
			GameEngineImage* Image = GameEngineResources::GetInst().ImageLoad(Files[i].GetFullPath());
		}
		int a = 0;

	}

	{	// ���� �̹��� �ε�
		Dir.MoveParentToDirectory("Monster");
		Dir.Move("Monster");
		{
			Dir.Move("Cut21");
			std::vector<GameEngineFile> Files = Dir.GetAllFile();
			for (size_t i = 0; i < Files.size(); i++)
			{
				GameEngineImage* Image = GameEngineResources::GetInst().ImageLoad(Files[i].GetFullPath());
				Image->Cut(2, 1);
			}
		}

		{
			Dir.MoveParent();
			Dir.Move("Cut31");
			std::vector<GameEngineFile> Files = Dir.GetAllFile();
			for (size_t i = 0; i < Files.size(); i++)
			{
				GameEngineImage* Image = GameEngineResources::GetInst().ImageLoad(Files[i].GetFullPath());
				Image->Cut(3, 1);
			}
		}

		{
			Dir.MoveParent();
			Dir.Move("Cut41");
			std::vector<GameEngineFile> Files = Dir.GetAllFile();
			for (size_t i = 0; i < Files.size(); i++)
			{
				GameEngineImage* Image = GameEngineResources::GetInst().ImageLoad(Files[i].GetFullPath());
				Image->Cut(4, 1);
			}
		}

		{
			Dir.MoveParent();
			Dir.Move("Cut51");
			std::vector<GameEngineFile> Files = Dir.GetAllFile();
			for (size_t i = 0; i < Files.size(); i++)
			{
				GameEngineImage* Image = GameEngineResources::GetInst().ImageLoad(Files[i].GetFullPath());
				Image->Cut(5, 1);
			}
		}

		{
			Dir.MoveParent();
			Dir.Move("Cut52");
			std::vector<GameEngineFile> Files = Dir.GetAllFile();
			for (size_t i = 0; i < Files.size(); i++)
			{
				GameEngineImage* Image = GameEngineResources::GetInst().ImageLoad(Files[i].GetFullPath());
				Image->Cut(5, 2);
			}
		}
		{
			Dir.MoveParent();
			Dir.Move("Cut61");
			std::vector<GameEngineFile> Files = Dir.GetAllFile();
			for (size_t i = 0; i < Files.size(); i++)
			{
				GameEngineImage* Image = GameEngineResources::GetInst().ImageLoad(Files[i].GetFullPath());
				Image->Cut(6, 1);
			}
		}

		{
			Dir.MoveParent();
			Dir.Move("Cut71");
			std::vector<GameEngineFile> Files = Dir.GetAllFile();
			for (size_t i = 0; i < Files.size(); i++)
			{
				GameEngineImage* Image = GameEngineResources::GetInst().ImageLoad(Files[i].GetFullPath());
				Image->Cut(7, 1);
			}
		}
	}

	{
		// UI �̹��� �ε�

		// ĳ���� �̹��� �ε�
		Dir.MoveParentToDirectory("UI");
		Dir.Move("UI");

		std::vector<GameEngineFile> Files = Dir.GetAllFile();

		for (size_t i = 0; i < Files.size(); i++)
		{
			GameEngineImage* Image = GameEngineResources::GetInst().ImageLoad(Files[i].GetFullPath());
		}

		// �����̹��� �ε�
		Dir.Move("number");
		GameEngineImage* Image2 = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("Number.BMP"));
		Image2->Cut(10, 1);
	}

	{   //���� �̹��� �ε�
		Dir.MoveParentToDirectory("Weapon");
		Dir.Move("Weapon");
		std::vector<GameEngineFile> Files = Dir.GetAllFile();

		for (size_t i = 0; i < Files.size(); i++)
		{
			GameEngineResources::GetInst().ImageLoad(Files[i].GetFullPath());
		}
		
		Dir.Move("Cut16");
		Files.clear();
		Files = Dir.GetAllFile();

		for (size_t i = 0; i < Files.size(); i++)
		{
			GameEngineImage* Image = GameEngineResources::GetInst().ImageLoad(Files[i].GetFullPath());
			Image->Cut(1, 6);
		}
	}



	{
		Dir.MoveParentToDirectory("Item");
		Dir.Move("Item");
		std::vector<GameEngineFile> Files = Dir.GetAllFile();
		for (size_t i = 0; i < Files.size(); i++)
		{
			GameEngineResources::GetInst().ImageLoad(Files[i].GetFullPath());
		}
	}
}