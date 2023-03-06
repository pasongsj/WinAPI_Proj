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

#include "MouseObject.h"

#include "WeaponWhip.h"
#include "WeaponMagicWand.h"
#include "WeaponKnife.h"
#include "WeaponRuneTracer.h"
#include "WeaponKingBible.h"
#include "WeaponFireWand.h"


void ChangeLevelToTitle()
{
	GameEngineCore::GetInst()->ChangeLevel("TitleLevel"); // ���â ����ְ� ������
}

InlaidLibraryLevel::InlaidLibraryLevel()
{
}

InlaidLibraryLevel::~InlaidLibraryLevel()
{

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
	// �������� �͵��� ����� ������ Loading����

	if (false == GameEngineInput::IsKey("StopDebug")) // - �ӽ� : ����ü���� 
	{
		GameEngineInput::CreateKey("StopDebug", 'P');
		GameEngineInput::CreateKey("SpeedUp", 'I');
		GameEngineInput::CreateKey("SpeedReset", 'O');
		GameEngineInput::CreateKey("Cheat", 'L');
	}
	MouseObject* MouseObjectInst = CreateActor<MouseObject>(); //���콺 ������Ʈ ����

	if (false == GameEngineInput::IsKey("DebugRenderSwitch"))
	{
		GameEngineInput::CreateKey("DebugRenderSwitch", 'R');
	}
	//SetCameraPos((BGSize - GameEngineWindow::GetScreenSize()).half()); // ī�޶� ��ġ �߰����� �̵�

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
	}


	//{
	//	// ���� ���� ����
	//	for (int i = 0;i < 10 ;i++) 
	//	{
	//		Monster* Actor = CreateActor<Monster>(VSRenderOrder::Monster);
	//	}
	//}

	{
		BackButton = CreateActor<Button>();
		float4 BtnScale = GameEngineResources::GetInst().ImageFind("BackBtn.bmp")->GetImageScale();
		//float4 BtnScale = { 203,63 };
		/*float4 BtnPos = GameEngineWindow::GetScreenSize().half();
		BtnPos.y += BtnPos.y * (1.2f);*/
		BackButton->setting("BackBtn.bmp", "BackBtn.bmp", "BackBtn.bmp", {0,0}, BtnScale, static_cast<int>(VSRenderOrder::MAX), false);
		BackButton->GetButtonRender()->SetImage("BackBtn.bmp");
		BackButton->GetButtonRender()->EffectCameraOn();
		BackButton->SetClickCallBack(ChangeLevelToTitle);
		BackButton->Off();
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

	if (GameEngineInput::IsDown("Cheat"))
	{
		Player::MainPlayer->CollisionOnOff();
	}
	if (GameEngineInput::IsDown("SpeedUp"))
	{
		float beforeSpeed = GameEngineCore::GetSpeed();
		GameEngineCore::SetSpeedUp(beforeSpeed*5.0f);
	}
	if (GameEngineInput::IsDown("SpeedReset"))
	{
		float beforeSpeed = GameEngineCore::GetSpeed();
		GameEngineCore::SetSpeedUp(beforeSpeed*0.2f);
	}

	SetState();
	ReGenMonster();
	CheckEnd();
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
		
		for (int i = 0;i < MaxMonster- GetActors(VSRenderOrder::Monster).size();i++)
		{
			int RandNum = GameEngineRandom::MainRandom.RandomInt(0, static_cast<int>(SponableMonster.size()) - 1);
			Monster::MonsterName = SponableMonster[RandNum];
			if (i < DeadMonsterCnt) // ���� ���� ���� ��Ȱ��
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

	//// - ���� �� �׽�Ʈ���Դϴ�.
	/*RegenInterval = 15.0f;
	if (StageTime - LastReGenTime >= RegenInterval)
	{
		LastReGenTime = StageTime;
		for (int i = 0;i < 1;i++)
		{
			int RandNum = GameEngineRandom::MainRandom.RandomInt(0, static_cast<int>(SponableMonster.size()) - 1);
			Monster::MonsterName = SponableMonster[RandNum];

			Monster* Actor = CreateActor<Monster>(VSRenderOrder::Monster);

		}
	}*/

}

void InlaidLibraryLevel::LevelChangeStart(GameEngineLevel* _PrevLevel)
{
	{
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
	/*int a = 0;
	BGMPlayer = GameEngineResources::GetInst().SoundPlayToControl("intro.mp3");
	BGMPlayer.LoopCount(100);*/
}

void InlaidLibraryLevel::CheckEnd()
{
	if (Player::MainPlayer->GetHp() <= 0)
	{
	
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
			// ���
		}
	}

}

void InlaidLibraryLevel::LevelChangeEnd(GameEngineLevel* _NextLevel)
{
	BackButton->Off();
	BackGround->SetEndingRenderOff();
}