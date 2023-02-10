#include "TitleLevel.h"

#include <GameEngineBase/GameEngineDirectory.h>
#include <GameEngineCore/GameEngineResources.h>
#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEngineCore/GameEngineCore.h>
#include <GameEngineCore/Button.h>
#include "TitleSubBack.h"
#include "TitleMainBack.h"
#include "MouseObject.h"
#include "ContentsEnums.h"

TitleLevel::TitleLevel()
{
}

TitleLevel::~TitleLevel()
{
}

void ClickStartButton()
{
	GameEngineCore::GetInst()->ChangeLevel("InlaidLibraryLevel");
}


void TitleLevel::SoundLoad()
{
	GameEngineDirectory Dir;
	Dir.MoveParentToDirectory("ContentsResources");
	Dir.Move("ContentsResources");
	Dir.Move("Sound");

	{
		//GameEngineResources::GetInst().SoundLoad(Dir.GetPlusFileName("Intro.mp3"));
	}

	// GameEngineResources::GetInst().SoundPlay("Appear.wav");

}
void TitleLevel::ImageLoad()
{

	{
		GameEngineDirectory Dir;
		Dir.MoveParentToDirectory("ContentsResources");
		Dir.Move("ContentsResources");
		Dir.Move("Image");
		Dir.Move("Title");
		GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("TitleMainBackGround.BMP"));

		//Image = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("TitleBackGround.BMP"));

		GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("startbutton.BMP"));

		GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("CollectionButton.BMP"));

		GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("ExitButton.BMP"));

		GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("OptionButton.BMP"));

		GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("ReinforceButton.BMP"));
	}

}

void TitleLevel::Loading()
{
	SoundLoad();
	ImageLoad();

	if (false == GameEngineInput::IsKey("DebugRenderSwitch"))
	{
		GameEngineInput::CreateKey("DebugRenderSwitch", 'R');
	}

	// back이미지 로드
	//{
	//	GameEngineDirectory Dir;
	//	Dir.MoveParentToDirectory("ContentsResources");
	//	Dir.Move("ContentsResources");
	//	Dir.Move("Image");
	//	Dir.Move("Title");
	//	GameEngineImage* Image = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("TitleMainBackGround.BMP"));

	//	//Image = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("TitleBackGround.BMP"));

	//	Image = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("startbutton.BMP"));

	//	Image = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("CollectionButton.BMP"));

	//	Image = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("ExitButton.BMP"));

	//	Image = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("OptionButton.BMP"));

	//	Image = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("ReinforceButton.BMP"));
	//}
	MouseObject* MouseObjectInst = CreateActor<MouseObject>();

	CreateActor<TitleMainBack>();

	Button* NewStartButton = CreateActor<Button>();
	float4 StartBPos = { 768, 610 };
	NewStartButton->setting("startbutton.BMP", "OptionButton.BMP", "CollectionButton.BMP", StartBPos, { 268, 83 }, static_cast<int>(VSRenderOrder::UI), false);
	NewStartButton->SetClickCallBack(ClickStartButton);


	Button* NewReinForceButton = CreateActor<Button>();
	float4 ReinForceBPos = { 768, 780 };
	NewReinForceButton->setting("ReinforceButton.BMP", "OptionButton.BMP", "CollectionButton.BMP", ReinForceBPos, { 221, 83 }, static_cast<int>(VSRenderOrder::UI), false);
}

void TitleLevel::Update(float _DeltaTime)
{
	if (GameEngineInput::IsDown("DebugRenderSwitch"))
	{
		DebugRenderSwitch();
		// Player::MainPlayer->Death()p;
	}
	//if (true == GameEngineInput::IsDown("LevelChange"))
	//{
	//	GameEngineCore::GetInst()->ChangeLevel("InlaidLibraryLevel");
	//}
	
}

void TitleLevel::LevelChangeStart(GameEngineLevel* _PrevLevel)
{
	/*BGMPlayer = GameEngineResources::GetInst().SoundPlayToControl("Intro.mp3");
	BGMPlayer.LoopCount(100);
	BGMPlayer.Volume(0.2f);*/
}
