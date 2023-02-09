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

void ClickStartbutton()
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

	Button* NewButton = CreateActor<Button>();
	float4 StartBPos = { 774, 610 };
	/*NewButton->GetButtonRender()->EffectCameraOff();
	NewButton->SetPos(StartBPos);
	NewButton->SetHoverImage("startbutton.BMP");
	NewButton->SetPressImage("CollectionButton.BMP");
	NewButton->SetReleaseImage("OptionButton.BMP");
	NewButton->SetScale({ 270, 84 });
	NewButton->SetClickCallBack(ClickStartbutton);*/
	//NewButton->GetButtonCollision()->SetDebugRenderType(CollisionType::CT_Rect);
	NewButton->setting("startbutton.BMP", "OptionButton.BMP", "CollectionButton.BMP", StartBPos, { 270, 84 }, static_cast<int>(VSRenderOrder::UI), false);
	NewButton->SetClickCallBack(ClickStartbutton);
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