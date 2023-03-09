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
	GameEngineCore::GetInst()->ChangeLevel("TitleLevel"); // ���â ����ְ� ������
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
	// �������� �͵��� ����� ������ Loading����

	if (false == GameEngineInput::IsKey("GetItem")) // - �ӽ� : ����ü���� 
	{
		GameEngineInput::CreateKey("GetItem", 'P');
		GameEngineInput::CreateKey("SpeedUp", 'I');
		GameEngineInput::CreateKey("SpeedReset", 'O');
		GameEngineInput::CreateKey("Cheat", 'L');
		GameEngineInput::CreateKey("GetBox", 'M');
	}
	MouseObject* MouseObjectInst = CreateActor<MouseObject>(VSRenderOrder::MAX); //���콺 ������Ʈ ����

	if (false == GameEngineInput::IsKey("DebugRenderSwitch"))
	{
		GameEngineInput::CreateKey("DebugRenderSwitch", 'R');
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
			ObtainBox::ObtainBoxAni->UIOn();
			Player::IsStop = true;
		}
		Player::IsStop = true;
	}
	else
	{
		AdditionItemUI::SelectUI->UIOff();
		AdditionItemUI::SelectUI->ReSetOff();
		ObtainBox::ObtainBoxAni->UIOff();
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
			if (i < DeadMonsterCnt) // ���� ���� ���� ��Ȱ��
			{
				Monster* _DeadMonster = Monster::DeadMonsters.back();
				Monster::DeadMonsters.pop_back();
				_DeadMonster->Reset();
			}
			else
			{
				Monster* Actor = CreateActor<Monster>(VSRenderOrder::Monster);
			}

		}
	}

	//// - ���� �� �׽�Ʈ���Դϴ�.
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
	BGMPlayer.Volume(0.5f);
	{
		// ���� ���ͻ���
		CreateActor<WeaponWhip>(VSRenderOrder::Weapon);
		CreateActor<WeaponMagicWand>(VSRenderOrder::Weapon);
		CreateActor<WeaponKnife>(VSRenderOrder::Weapon);
		CreateActor<WeaponRuneTracer>(VSRenderOrder::Weapon);
		CreateActor<WeaponKingBible>(VSRenderOrder::Weapon);
		CreateActor<WeaponFireWand>(VSRenderOrder::Weapon);
	}

	{
		// ��� ���� ����
		BackGround = CreateActor<InlaidLibraryBack>(VSRenderOrder::BackGround); // ������ ���
	}

	{
		// UI ���ͻ���
		AdditionItemUI* SelectItemUI = CreateActor<AdditionItemUI>(VSRenderOrder::LastUI);
		/*SelectItemUI->Off();*/
		NewUI = CreateActor<PlayGameUI>(VSRenderOrder::UI);
		CreateActor<ItemIcon>(VSRenderOrder::LastUI);
	}

	{ // �ڽ� ����
		CreateActor<ObtainBox>(VSRenderOrder::LastUI);

	}

	{
		BackButton = CreateActor<Button>();
		float4 BtnScale = GameEngineResources::GetInst().ImageFind("BackBtn.bmp")->GetImageScale();
		BackButton->setting("BackBtn.bmp", "BackBtn.bmp", "BackBtn.bmp", { 0,0 }, BtnScale, static_cast<int>(VSRenderOrder::MAX), false);
		BackButton->GetButtonRender()->SetImage("BackBtn.bmp");
		BackButton->GetButtonRender()->EffectCameraOn();
		BackButton->SetClickCallBack(ChangeLevelToTitle);
		BackButton->Off();
	}

	{ // �÷��̾� ����
		Player* NewPlayer = CreateActor<Player>(VSRenderOrder::Player); // �÷��̾�
		NewPlayer->SetMove(BGSize.half()); // ȭ�� �߰���ġ�� �̵�
		SetCameraPos((BGSize - GameEngineWindow::GetScreenSize()).half());

	}
	{
		// ���� ���� ����
		for (int i = 0;i < 20;i++)
		{
			Monster* Actor = CreateActor<Monster>(VSRenderOrder::Monster);
		}
	}

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
		//SetTimeScale(VSRenderOrder::LastUI, 0);
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
			// ���
		}
	}

}

void InlaidLibraryLevel::LevelChangeEnd(GameEngineLevel* _NextLevel)
{
	/*BackButton->Off();
	BackGround->SetEndingRenderOff();*/
	{
		// ���� ���� ����
		Weapon::Weapons.clear();
		for (GameEngineActor* _Actor : GetActors(VSRenderOrder::Weapon))
		{
			_Actor->Death();
		}
	}

	{
		// ��� ���� ����
		/*for (GameEngineActor* _Actor : GetActors(VSRenderOrder::BackGround))
		{
			_Actor->Death();
		}*/
		BackGround->Death();
		NewUI->Death();
		//BackGround = CreateActor<InlaidLibraryBack>(VSRenderOrder::BackGround); // ������ ���
	}

	
	{	// �ڽ� ����
		// UI ��������
		// ��ư ����
		NewUI->Death();
		ObtainBox::ObtainBoxAni->Death();
		BackButton->Death();
		for (GameEngineActor* _Actor : GetActors(VSRenderOrder::LastUI))
		{
			_Actor->Death();
		}
		for (GameEngineActor* _Actor : GetActors(VSRenderOrder::UI))
		{
			_Actor->Death();
		}
	}
	{
		Monster::DeadMonsters.clear();
		for (GameEngineActor* _Actor : GetActors(VSRenderOrder::Monster))
		{
			_Actor->Death();
		}
		Items::ObtainedItems.clear();
		for (GameEngineActor* _Actor : GetActors(VSRenderOrder::Item))
		{
			_Actor->Death();
		}
		Player::MainPlayer->Death();
		SponableMonster.clear();


	}
	{
		Monster::MonsterName = "Dust";
		MaxMonster = 50;
		RegenInterval = 3.0f;
		NextSettingTime = 0;
		LastReGenTime = 0;
	}
}