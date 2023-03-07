#include "TitleLevel.h"

#include <GameEngineBase/GameEngineDirectory.h>
#include <GameEngineBase/GameEngineFile.h>
#include <GameEngineCore/GameEngineResources.h>
#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEngineCore/GameEngineCore.h>
#include <GameEngineCore/Button.h>
#include "TitleSubBack.h"
#include "TitleMainBack.h"
#include "MouseObject.h"
#include "SelectCharacter.h"
#include "ContentsEnums.h"
//
// test
//
SelectCharacter* TitleLevel::SelectScreen = nullptr;
GameEngineSoundPlayer TitleLevel::ClickButtonDown;

TitleLevel::TitleLevel()
{
}

TitleLevel::~TitleLevel()
{
}

void ClickStartButton()
{
	if (nullptr == TitleLevel::SelectScreen)
	{
		MsgAssert("SelectScreen 액터가 생성되지 않았습니다.");
		return;
	}
	TitleLevel::SelectScreen->Activate();
	GameEngineSoundPlayer BtnDown = GameEngineResources::GetInst().SoundPlayToControl("ButtonDown.mp3");
	BtnDown.Volume(0.3f);
	BtnDown.LoopCount(1);
}


void TitleLevel::SoundLoad()
{
	GameEngineDirectory Dir;
	Dir.MoveParentToDirectory("ContentsResources");
	Dir.Move("ContentsResources");
	Dir.Move("Sound");

	GameEngineResources::GetInst().SoundLoad(Dir.GetPlusFileName("intro.mp3"));
	GameEngineResources::GetInst().SoundLoad(Dir.GetPlusFileName("ButtonDown.mp3"));
	GameEngineResources::GetInst().SoundLoad(Dir.GetPlusFileName("ButtonQuit.mp3"));

}
void TitleLevel::ImageLoad()
{
	GameEngineDirectory Dir;
	Dir.MoveParentToDirectory("ContentsResources");
	Dir.Move("ContentsResources");
	Dir.Move("Image");
	Dir.Move("Title");
	std::vector<GameEngineFile> Files = Dir.GetAllFile();

	for (size_t i = 0; i < Files.size(); i++)
	{
		GameEngineResources::GetInst().ImageLoad(Files[i].GetFullPath());
	}
	//	GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("TitleMainBackGround.BMP"));

	//	//Image = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("TitleBackGround.BMP"));

	//	GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("startbutton.BMP"));

	//	GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("CollectionButton.BMP"));

	//	GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("ExitButton.BMP"));

	//	GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("OptionButton.BMP"));

	//	GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("ReinforceButton.BMP"));
	//}

}

void TitleLevel::Loading()
{
	SoundLoad();
	ImageLoad();

	if (false == GameEngineInput::IsKey("DebugRenderSwitch"))
	{
		GameEngineInput::CreateKey("DebugRenderSwitch", 'R');
	}

	MouseObject* MouseObjectInst = CreateActor<MouseObject>();

	CreateActor<TitleMainBack>(VSRenderOrder::BackGround);

	Button* NewStartButton = CreateActor<Button>();
	float4 StartBPos = { 768, 610 };
	NewStartButton->setting("startbutton.BMP", "startbutton.BMP", "startbutton.BMP", StartBPos, { 268, 83 }, static_cast<int>(VSRenderOrder::UI), false);
	NewStartButton->SetClickCallBack(ClickStartButton);


	Button* NewReinForceButton = CreateActor<Button>();
	float4 ReinForceBPos = { 768, 780 };
	NewReinForceButton->setting("ReinforceButton.BMP", "ReinforceButton.BMP", "ReinforceButton.BMP", ReinForceBPos, { 221, 83 }, static_cast<int>(VSRenderOrder::UI), false);

	SelectScreen = CreateActor<SelectCharacter>(VSRenderOrder::UI);
	//SelectScreen->Off();

}

void TitleLevel::Update(float _DeltaTime)
{
	if (GameEngineInput::IsDown("DebugRenderSwitch"))
	{
		DebugRenderSwitch();
		// Player::MainPlayer->Death();
	}
	//if (true == GameEngineInput::IsDown("LevelChange"))
	//{
	//	GameEngineCore::GetInst()->ChangeLevel("InlaidLibraryLevel");
	//}
	
}


void TitleLevel::LevelChangeStart(GameEngineLevel* _PrevLevel)
{
	BGMPlayer = GameEngineResources::GetInst().SoundPlayToControl("intro.mp3");
	BGMPlayer.LoopCount(1);
	BGMPlayer.Volume(0.2f);


}

void TitleLevel::LevelChangeEnd(GameEngineLevel* _NextLevel)
{
	BGMPlayer.Stop();
}
