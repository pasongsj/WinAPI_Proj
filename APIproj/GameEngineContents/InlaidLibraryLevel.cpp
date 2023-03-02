#include "InlaidLibraryLevel.h"
#include <GameEngineBase/GameEngineDirectory.h>
#include <GameEngineBase/GameEngineFile.h>
#include <GameEngineBase/GameEngineRandom.h>
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
#include "AdditionItemUI.h"

#include "MouseObject.h"

#include "WeaponWhip.h"
#include "WeaponMagicWand.h"
#include "WeaponKnife.h"

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

	{	// 몬스터 이미지 로드
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
		// UI 이미지 로드

		// 캐릭터 이미지 로드
		Dir.MoveParentToDirectory("UI");
		Dir.Move("UI");

		std::vector<GameEngineFile> Files = Dir.GetAllFile();

		for (size_t i = 0; i < Files.size(); i++)
		{
			GameEngineImage* Image = GameEngineResources::GetInst().ImageLoad(Files[i].GetFullPath());
		}

		// 숫자이미지 로드
		Dir.Move("number");
		GameEngineImage* Image2 = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("Number.BMP"));
		Image2->Cut(10, 1);
	}

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
			GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("MagicWand.BMP"));
			GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("MagicWandBlack.BMP"));

		}
		{
			Dir.MoveParentToDirectory("Knife");
			Dir.Move("Knife");
			GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("Knife.BMP"));
			GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("KnifeBlack.BMP"));
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
		GameEngineInput::CreateKey("SpeedUp", 'I');
	}
	MouseObject* MouseObjectInst = CreateActor<MouseObject>(); //마우스 오브젝트 생성

	if (false == GameEngineInput::IsKey("DebugRenderSwitch"))
	{
		GameEngineInput::CreateKey("DebugRenderSwitch", 'R');
	}
	SetCameraPos((BGSize - GameEngineWindow::GetScreenSize()).half()); // 카메라 위치 중간으로 이동

	{
		// 무기 액터생성
		CreateActor<WeaponWhip>(VSRenderOrder::Weapon);
		CreateActor<WeaponMagicWand>(VSRenderOrder::Weapon);
		CreateActor<WeaponKnife>(VSRenderOrder::Weapon);
	}

	{
		// 배경 액터 생성
		InlaidLibraryBack* BackGround = CreateActor<InlaidLibraryBack>(VSRenderOrder::BackGround); // 가시적 배경
	}

	{
		// UI 액터생성
		AdditionItemUI* SelectItemUI = CreateActor<AdditionItemUI>(VSRenderOrder::LastUI);
		/*SelectItemUI->Off();*/
		NewUI = CreateActor<PlayGameUI>(VSRenderOrder::UI);
	}


	{
		// 몬스터 액터 생성
		for (int i = 0;i < 10 ;i++) 
		{
			Monster* Actor = CreateActor<Monster>(VSRenderOrder::Monster);
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
		AdditionItemUI::SelectUI->UIOn();
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
		AdditionItemUI::SelectUI->UIOff();
		AdditionItemUI::SelectUI->ReSetOff();
		//NewUI->LevelUpUIRenderOff();
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

	/*if (GameEngineInput::IsDown("SpeedUp"))
	{
		SetTimeScale(VSRenderOrder::BackGround, 2);
		SetTimeScale(VSRenderOrder::Map, 2);
		SetTimeScale(VSRenderOrder::Player, 2);
		SetTimeScale(VSRenderOrder::Monster, 2);
		SetTimeScale(VSRenderOrder::Item, 2);
		SetTimeScale(VSRenderOrder::Weapon, 2);
		SetTimeScale(VSRenderOrder::UI, 2);
		SetTimeScale(VSRenderOrder::LastUI, 2);
	}*/
	SetState(_DeltaTime);
	ReGenMonster(_DeltaTime);
}
void InlaidLibraryLevel::SetState(float _DeltaTime)
{
	if (Player::IsStop == true)
	{
		return;
	}
	LevelTime += _DeltaTime;
	if (0 <= LevelTime && LevelTime < 1 * 60)
	{
		MaxMonster = 50;
		RegenInterval = 3.0f;
		SponableMonster.insert("Dust");
	}
	else if(1 * 60 <= LevelTime && LevelTime < 2 * 60)
	{
		MaxMonster = 80;
		RegenInterval = 3.0f;
	}
	else if (2 * 60 <= LevelTime && LevelTime < 3 * 60)
	{
		MaxMonster = 100;
		RegenInterval = 4.0f;
		SponableMonster.insert("Musc");
	}
	else if (3 * 60 <= LevelTime && LevelTime < 4 * 60)
	{
		MaxMonster = 60;
		RegenInterval = 4.0f;
		SponableMonster.clear();
		SponableMonster.insert("Mummy");
	}
	else if (4 * 60 <= LevelTime && LevelTime < 5 * 60)
	{
		MaxMonster = 100;
		RegenInterval = 4.0f;
		SponableMonster.insert("Dust");
	}
	else if (5 * 60 <= LevelTime && LevelTime < 6 * 60)
	{
		MaxMonster = 100;
		RegenInterval = 4.0f;
		SponableMonster.erase("Dust");
	}
	else if (6 * 60 <= LevelTime && LevelTime < 7 * 60)
	{
		MaxMonster = 30;
		RegenInterval = 2.0f;
		SponableMonster.clear();
		SponableMonster.insert("Dullahan");
		SponableMonster.insert("Musc");
	}
	else if (7 * 60 <= LevelTime && LevelTime < 8 * 60)
	{
		MaxMonster = 80;
		RegenInterval = 2.0f;
	}
	else if (8 * 60 <= LevelTime && LevelTime < 9 * 60)
	{
		MaxMonster = 80;
		RegenInterval = 1.0f;
		SponableMonster.erase("Dullahan");
		SponableMonster.insert("Ghost");
	}
	else if (9 * 60 <= LevelTime && LevelTime < 10 * 60)
	{
		MaxMonster = 200;
		RegenInterval = 0.5f;
		SponableMonster.erase("Musc");
		SponableMonster.insert("Mummy");
	}
	else if (10 * 60 <= LevelTime && LevelTime < 11 * 60)
	{
		MaxMonster = 100;
		RegenInterval = 0.5f;
		SponableMonster.clear();
		SponableMonster.insert("Musc");
	}
	else if (11 * 60 <= LevelTime && LevelTime < 12 * 60)
	{
		MaxMonster = 120;
		RegenInterval = 2.0f;
		SponableMonster.clear();
		SponableMonster.insert("ColossalMedusaHead");
		SponableMonster.insert("LionHead");
	}
	else if (12 * 60 <= LevelTime && LevelTime < 13 * 60)
	{
		MaxMonster = 80;
		RegenInterval = 1.0f;
		SponableMonster.erase("LionHead");
		SponableMonster.insert("Dullahan");
	}
	else if (13 * 60 <= LevelTime && LevelTime < 14 * 60)
	{
		MaxMonster = 120;
		RegenInterval = 0.5f;
		SponableMonster.erase("ColossalMedusaHead");
		SponableMonster.insert("Mummy");
	}
	else if (14 * 60 <= LevelTime && LevelTime < 15 * 60)
	{
		MaxMonster = 300;
		RegenInterval = 0.1f;
		SponableMonster.erase("Dullahan");
		SponableMonster.insert("ColossalMedusaHead");
		SponableMonster.insert("Musc");
	}
	else if (15 * 60 <= LevelTime && LevelTime < 16 * 60)
	{
		MaxMonster = 100;
		RegenInterval = 0.1f;
	}
	else if (16 * 60 <= LevelTime && LevelTime < 17 * 60)
	{
		MaxMonster = 100;
		RegenInterval = 1.0f;
	}
	else if (17 * 60 <= LevelTime && LevelTime < 18 * 60)
	{
		MaxMonster = 200;
		RegenInterval = 1.0f;
	}
	else if (18 * 60 <= LevelTime && LevelTime < 19 * 60)
	{
		MaxMonster = 60;
		RegenInterval = 0.5f;
	}
	else if (19 * 60 <= LevelTime && LevelTime < 20 * 60)
	{
		MaxMonster = 120;
		RegenInterval = 0.5f;
	}
	else if (20 * 60 <= LevelTime && LevelTime < 21 * 60)
	{
		MaxMonster = 100;
		RegenInterval = 0.1f;
	}
	else if (21 * 60 <= LevelTime && LevelTime < 22 * 60)
	{
		MaxMonster = 100;
		RegenInterval = 0.1f;
	}
	else if (22 * 60 <= LevelTime && LevelTime < 23 * 60)
	{
		MaxMonster = 80;
		RegenInterval = 1.0f;
	}
	else if (23 * 60 <= LevelTime && LevelTime < 24 * 60)
	{
		MaxMonster = 120;
		RegenInterval = 0.1f;
	}
	else if (24 * 60 <= LevelTime && LevelTime < 25 * 60)
	{
		MaxMonster = 300;
		RegenInterval = 0.1f;
	}
	else if (25 * 60 <= LevelTime && LevelTime < 26 * 60)
	{
		MaxMonster = 300;
		RegenInterval = 0.1f;
	}
	else if (26 * 60 <= LevelTime && LevelTime < 27 * 60)
	{
		MaxMonster = 100;
		RegenInterval = 0.1f;
	}
	else if (27 * 60 <= LevelTime && LevelTime < 28 * 60)
	{
		MaxMonster = 300;
		RegenInterval = 0.1f;
	}
	else if (28 * 60 <= LevelTime && LevelTime < 29 * 60)
	{
		MaxMonster = 250;
		RegenInterval = 0.1f;
	}
	else if (29 * 60 <= LevelTime && LevelTime < 30 * 60)
	{
		MaxMonster = 250;
		RegenInterval = 0.1f;
	}
	else
	{
		MaxMonster = 1;
		RegenInterval = 10.0f;
	}

}
void InlaidLibraryLevel::ReGenMonster(float _DeltaTime)
{

	MonsterReGenTime += _DeltaTime;
	if (GetActors(VSRenderOrder::Monster).size() >= MaxMonster) {
		return;
	}
	if (MonsterReGenTime >= RegenInterval)
	{
		std::set<std::string>::iterator it = SponableMonster.begin();
		int RandNum = GameEngineRandom::MainRandom.RandomInt(0, SponableMonster.size() - 1);
		while (RandNum)
		{
			it++;
			--RandNum;
		}
		Monster::MonsterName = *it;
		MonsterReGenTime = 0.0f;
		Monster* Actor = CreateActor<Monster>(VSRenderOrder::Monster);
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