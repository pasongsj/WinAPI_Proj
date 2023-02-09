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

void TitleLevel::Loading()
{

	if (false == GameEngineInput::IsKey("DebugRenderSwitch"))
	{
		GameEngineInput::CreateKey("DebugRenderSwitch", 'R');
	}
	// 만들어야할 것들을 만드는 시점이 Loading시점
	// 
	/*if (false == GameEngineInput::IsKey("LevelChange"))
	{
		GameEngineInput::CreateKey("LevelChange", 'P');
	}*/
	// back이미지 로드

	{
		GameEngineDirectory Dir;
		Dir.MoveParentToDirectory("ContentsResources");
		Dir.Move("ContentsResources");
		Dir.Move("Image");
		Dir.Move("Title");
		GameEngineImage* Image = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("TitleMainBackGround.BMP"));

		//Image = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("TitleBackGround.BMP"));

		Image = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("startbutton.BMP"));

		Image = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("CollectionButton.BMP"));

		Image = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("ExitButton.BMP"));

		Image = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("OptionButton.BMP"));

		Image = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("ReinforceButton.BMP"));
	}
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