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
	// 만들어야할 것들을 만드는 시점이 Loading시점
	// 
	if (false == GameEngineInput::IsKey("LevelChange"))
	{
		GameEngineInput::CreateKey("LevelChange", 'P');
	}
	// back이미지 로드

	GameEngineDirectory Dir;
	{
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

	/*MouseObjectInst->GetMouseRender()->EffectCameraOff();
	MouseObjectInst->GetMouseRender()->SetOrder(100);
	MouseObjectInst->GetMouseRender()->SetScale({ 20, 20 });*/

	//CreateActor<TitleSubBack>();
	CreateActor<TitleMainBack>();

	Button* NewButton = CreateActor<Button>();
	NewButton->GetButtonRender()->EffectCameraOff();
	float4 ButtonPos = GameEngineWindow::GetScreenSize().half();
	ButtonPos.y += GameEngineWindow::GetScreenSize().half().hy();
	NewButton->SetPos(ButtonPos);
	NewButton->SetHoverImage("startbutton.BMP");
	NewButton->SetPressImage("startbutton.BMP");
	NewButton->SetReleaseImage("startbutton.BMP");
	NewButton->SetScale({ 270, 84 });
	NewButton->SetClickCallBack(ClickStartbutton);
	NewButton->SetOrder(static_cast<int>(VSRenderOrder::UI));
}

void TitleLevel::Update(float _DeltaTime)
{

	//if (true == GameEngineInput::IsDown("LevelChange"))
	//{
	//	GameEngineCore::GetInst()->ChangeLevel("InlaidLibraryLevel");
	//}
	
}