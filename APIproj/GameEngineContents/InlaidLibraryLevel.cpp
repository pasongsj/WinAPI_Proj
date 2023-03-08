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
#include "Items.h"
#include "AdditionItemUI.h"
#include "ItemIcon.h"

#include "MouseObject.h"
#include "ObtainBox.h"


#include "WeaponWhip.h"
#include "WeaponMagicWand.h"
#include "WeaponKnife.h"
#include "WeaponRuneTracer.h"
#include "WeaponKingBible.h"
#include "WeaponFireWand.h"


void ChangeLevelToTitle()
{
	GameEngineCore::GetInst()->ChangeLevel("TitleLevel"); // 결과창 띄워주고 나가기
	GameEngineSoundPlayer Dwn = GameEngineResources::GetInst().SoundPlayToControl("ButtonDown.mp3");
	Dwn.Volume(0.3f);
	Dwn.LoopCount(1);
}

InlaidLibraryLevel::InlaidLibraryLevel()
{
}

InlaidLibraryLevel::~InlaidLibraryLevel()
{

}

void InlaidLibraryLevel::SoundLoad()
{
	GameEngineDirectory Dir;
	Dir.MoveParentToDirectory("ContentsResources");
	Dir.Move("ContentsResources");
	Dir.Move("Sound");

	GameEngineResources::GetInst().SoundLoad(Dir.GetPlusFileName("bgm_elrond_library.mp3"));
	GameEngineResources::GetInst().SoundLoad(Dir.GetPlusFileName("EnemyHit.mp3"));
	GameEngineResources::GetInst().SoundLoad(Dir.GetPlusFileName("GameOver.mp3"));
	GameEngineResources::GetInst().SoundLoad(Dir.GetPlusFileName("GetGem.mp3"));
	GameEngineResources::GetInst().SoundLoad(Dir.GetPlusFileName("LevelUp.mp3"));
	GameEngineResources::GetInst().SoundLoad(Dir.GetPlusFileName("PlayerAttacked.mp3"));
	GameEngineResources::GetInst().SoundLoad(Dir.GetPlusFileName("ProjectileKnife.mp3"));
	GameEngineResources::GetInst().SoundLoad(Dir.GetPlusFileName("ProjectileMagic.mp3"));
	GameEngineResources::GetInst().SoundLoad(Dir.GetPlusFileName("TreasureFound.mp3"));
	GameEngineResources::GetInst().SoundLoad(Dir.GetPlusFileName("TreasureOpening.mp3"));

}


void InlaidLibraryLevel::Loading()
{
	ImageLoad();
	SoundLoad();
	// 만들어야할 것들을 만드는 시점이 Loading시점

	if (false == GameEngineInput::IsKey("GetItem")) // - 임시 : 레벨체인지 
	{
		GameEngineInput::CreateKey("GetItem", 'P');
		GameEngineInput::CreateKey("SpeedUp", 'I');
		GameEngineInput::CreateKey("SpeedReset", 'O');
		GameEngineInput::CreateKey("Cheat", 'L');
		GameEngineInput::CreateKey("GetBox", 'M');
	}
	MouseObject* MouseObjectInst = CreateActor<MouseObject>(); //마우스 오브젝트 생성

	if (false == GameEngineInput::IsKey("DebugRenderSwitch"))
	{
		GameEngineInput::CreateKey("DebugRenderSwitch", 'R');
	}
	//SetCameraPos((BGSize - GameEngineWindow::GetScreenSize()).half()); // 카메라 위치 중간으로 이동

	{
		// 무기 액터생성
		CreateActor<WeaponWhip>(VSRenderOrder::Weapon);
		CreateActor<WeaponMagicWand>(VSRenderOrder::Weapon);
		CreateActor<WeaponKnife>(VSRenderOrder::Weapon);
		CreateActor<WeaponRuneTracer>(VSRenderOrder::Weapon);
		CreateActor<WeaponKingBible>(VSRenderOrder::Weapon);
		CreateActor<WeaponFireWand>(VSRenderOrder::Weapon);
	}

	{
		// 배경 액터 생성
		BackGround = CreateActor<InlaidLibraryBack>(VSRenderOrder::BackGround); // 가시적 배경
	}

	{
		// UI 액터생성
		AdditionItemUI* SelectItemUI = CreateActor<AdditionItemUI>(VSRenderOrder::LastUI);
		/*SelectItemUI->Off();*/
		NewUI = CreateActor<PlayGameUI>(VSRenderOrder::UI);
		CreateActor<ItemIcon>(VSRenderOrder::LastUI);
	}

	{ // 박스 액터
		ObtainBoxUI = CreateActor<ObtainBox>(VSRenderOrder::UI);
	}

	{
		BackButton = CreateActor<Button>();
		float4 BtnScale = GameEngineResources::GetInst().ImageFind("BackBtn.bmp")->GetImageScale();
		//float4 BtnScale = { 203,63 };
		/*float4 BtnPos = GameEngineWindow::GetScreenSize().half();
		BtnPos.y += BtnPos.y * (1.2f);*/
		BackButton->setting("BackBtn.bmp", "BackBtn.bmp", "BackBtn.bmp", {0,0}, BtnScale, static_cast<int>(VSRenderOrder::UI), false);
		BackButton->GetButtonRender()->SetImage("BackBtn.bmp");
		BackButton->GetButtonRender()->EffectCameraOn();
		BackButton->SetClickCallBack(ChangeLevelToTitle);
		BackButton->Off();
	}
}

void InlaidLibraryLevel::Update(float _DeltaTime)
{
	if (true == GameEngineInput::IsDown("GetItem"))
	{
		Player::MainPlayer->LevelUpUI = !Player::MainPlayer->LevelUpUI;
		//Player::IsStop = !Player::IsStop;
	}
	if (true == GameEngineInput::IsDown("GetBox"))
	{
		Player::MainPlayer->OpenBoxUI = !Player::MainPlayer->OpenBoxUI;
	}

	CheckLevelUpUI();
	ControlTimeScale();

	CheckDebugInput();

	SetState();
	ReGenMonster();
	CheckEnd();
}

void InlaidLibraryLevel::CheckDebugInput()
{
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

	if (GameEngineInput::IsDown("Cheat"))
	{
		Player::MainPlayer->CollisionOnOff();
	}
	if (GameEngineInput::IsDown("SpeedUp"))
	{
		float beforeSpeed = GameEngineCore::GetSpeed();
		GameEngineCore::SetSpeedUp(beforeSpeed * 5.0f);
	}
	if (GameEngineInput::IsDown("SpeedReset"))
	{
		float beforeSpeed = GameEngineCore::GetSpeed();
		GameEngineCore::SetSpeedUp(beforeSpeed * 0.2f);
	}
}

void InlaidLibraryLevel::CheckLevelUpUI()
{
	if (true == Player::MainPlayer->LevelUpUI || true == Player::MainPlayer->OpenBoxUI)
	{
		if (true == Player::MainPlayer->LevelUpUI)
		{
			if (false == AdditionItemUI::SelectUI->IsUpdate())
			{
				AdditionItemUI::SelectUI->UIOn();
				//GameEngineCore::GetInst()->ChangeLevel("TitleLevel");
			
			}
		}
		else
		{
			ObtainBoxUI->UIOn();
			Player::IsStop = true;
		}
		Player::IsStop = true;
	}
	else
	{
		AdditionItemUI::SelectUI->UIOff();
		AdditionItemUI::SelectUI->ReSetOff();
		ObtainBoxUI->UIOff();
		Player::IsStop = false;
	}

}
//void InlaidLibraryLevel::CheckBoxOpenUI()
//{
//	if (true == Player::MainPlayer->OpenBoxUI)
//	{
//		ObtainBoxUI->UIOn();
//		Player::IsStop = true;
//	}
//	else
//	{
//		ObtainBoxUI->UIOff();
//		Player::IsStop = false;
//	}
//}

void InlaidLibraryLevel::ControlTimeScale()
{
	if (true == Player::IsStop)
	{
		BGMPlayer.PauseOn();
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

		BGMPlayer.PauseOff();
		//NewUI->LevelUpUIRenderOff();
		SetTimeScale(VSRenderOrder::BackGround, 1);
		SetTimeScale(VSRenderOrder::Map, 1);
		SetTimeScale(VSRenderOrder::Player, 1);
		SetTimeScale(VSRenderOrder::Monster, 1);
		SetTimeScale(VSRenderOrder::Item, 1);
		SetTimeScale(VSRenderOrder::Weapon, 1);
		SetTimeScale(VSRenderOrder::UI, 1);
	}
}
void InlaidLibraryLevel::ReGenMonster()
{
	if (Player::IsStop == true|| NewUI == nullptr|| SponableMonster.size() == 0)
	{
		return;
	}
	float StageTime = NewUI->GetStageTime();

	if (StageTime - LastReGenTime >= RegenInterval)
	{
		LastReGenTime = StageTime;
		int DeadMonsterCnt = static_cast<int>(Monster::DeadMonsters.size());
		int MonsterCnt = static_cast<int>(GetActors(VSRenderOrder::Monster).size()) - DeadMonsterCnt;
		int ReGenCnt = ((MaxMonster - MonsterCnt) > (MaxMonster / 2) ? (MaxMonster / 2) : (MaxMonster - MonsterCnt));
		if (ReGenCnt <= 0)
		{
			return;
		}
		for (int i = 0;i < ReGenCnt;i++)
		{
			int RandNum = GameEngineRandom::MainRandom.RandomInt(0, static_cast<int>(SponableMonster.size()) - 1);
			Monster::MonsterName = SponableMonster[RandNum];
			if (i < DeadMonsterCnt) // 죽은 몬스터 액터 재활용
			{
				Monster* _DeadMonster = Monster::DeadMonsters.front();
				Monster::DeadMonsters.pop();
				_DeadMonster->Reset();
			}
			else
			{
				Monster* Actor = CreateActor<Monster>(VSRenderOrder::Monster);
			}

		}
	}

	//// - 몬스터 젠 테스트용입니다.
	//RegenInterval = 15.0f;
	//if (StageTime - LastReGenTime >= RegenInterval)
	//{
	//	LastReGenTime = StageTime;
	//	for (int i = 0;i < 1;i++)
	//	{
	//		int RandNum = GameEngineRandom::MainRandom.RandomInt(0, static_cast<int>(SponableMonster.size()) - 1);
	//		Monster::MonsterName = SponableMonster[RandNum];

	//		Monster* Actor = CreateActor<Monster>(VSRenderOrder::Monster);

	//	}
	//}

}

void InlaidLibraryLevel::LevelChangeStart(GameEngineLevel* _PrevLevel)
{
	BGMPlayer = GameEngineResources::GetInst().SoundPlayToControl("bgm_elrond_library.mp3");
	BGMPlayer.LoopCount(400);
	BGMPlayer.Volume(0.2f);

	{ // 플레이어 생성
		Player* NewPlayer = CreateActor<Player>(VSRenderOrder::Player); // 플레이어
		NewPlayer->SetMove(BGSize.half()); // 화면 중간위치로 이동
		SetCameraPos((BGSize - GameEngineWindow::GetScreenSize()).half());

	}
	{
		// 몬스터 액터 생성
		for (int i = 0;i < 20;i++)
		{
			Monster* Actor = CreateActor<Monster>(VSRenderOrder::Monster);
		}
	}
	/*int a = 0;
	BGMPlayer = GameEngineResources::GetInst().SoundPlayToControl("intro.mp3");
	BGMPlayer.LoopCount(100);*/
}

void InlaidLibraryLevel::CheckEnd()
{
	if (Player::MainPlayer->GetHp() <= 0)
	{
		BGMPlayer.Stop();
		float4 BtnPos = Player::MainPlayer->GetPos();
		BtnPos.y += (2.5f) * (BackButton->GetButtonRender()->GetScale()).y;
		BackButton->On();
		BackButton->SetPos(BtnPos);
		SetTimeScale(VSRenderOrder::BackGround, 0);
		SetTimeScale(VSRenderOrder::Map, 0);
		SetTimeScale(VSRenderOrder::Player, 0);
		SetTimeScale(VSRenderOrder::Monster, 0);
		SetTimeScale(VSRenderOrder::Item, 0);
		SetTimeScale(VSRenderOrder::Weapon, 0);
		SetTimeScale(VSRenderOrder::UI, 0);
		SetTimeScale(VSRenderOrder::LastUI, 0);
		//SetTimeScale(VSRenderOrder::MAX, 0);

		float StageTime = NewUI->GetStageTime();
		if (StageTime > 30 * 60)
		{
			BackGround->SetEndingRenderOn(true);
			//stageComplete
		}
		else
		{
			BackGround->SetEndingRenderOn(false);
			// 사망
		}
	}

}

void InlaidLibraryLevel::LevelChangeEnd(GameEngineLevel* _NextLevel)
{
	BackButton->Off();
	BackGround->SetEndingRenderOff();
}