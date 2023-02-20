#include "SelectCharacter.h"
#include "ContentsEnums.h"
#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEngineCore/GameEngineLevel.h>
#include <GameEngineCore/GameEngineRender.h>
#include <GameEngineCore/Button.h>
#include <GameEngineCore/GameEngineCore.h>

#include "Player.h"

SelectCharacter::SelectCharacter()
{
}

SelectCharacter::~SelectCharacter()
{
}

void ClickAntonioButton()
{
	/*if (nullptr == TitleLevel::SelectScreen)
	{
		MsgAssert("SelectScreen 액터가 생성되지 않았습니다.");
		return;
	}
	TitleLevel::SelectScreen->Activate();*/
	Player::PlayerName = "Antonio.bmp";
	GameEngineCore::GetInst()->ChangeLevel("InlaidLibraryLevel");
}

void ClickImeldaButton()
{
	Player::PlayerName = "Imelda.bmp";
	GameEngineCore::GetInst()->ChangeLevel("InlaidLibraryLevel");
}

void ClickPasqualinaButton()
{
	Player::PlayerName = "Pasqualina.bmp";
	GameEngineCore::GetInst()->ChangeLevel("InlaidLibraryLevel");
}
void ClickGennaroButton()
{
	Player::PlayerName = "Gennaro.bmp";
	GameEngineCore::GetInst()->ChangeLevel("InlaidLibraryLevel");
}

void SelectCharacter::Start()
{
	Screen = CreateRender("SelectCharScreen.bmp", VSRenderOrder::UI);
	float4 ScreenPos = GameEngineWindow::GetScreenSize().half();
	ScreenPos.y += 50;
	Screen->SetPosition(ScreenPos);
	Screen->SetScaleToImage();

	Button* AntonioButton = GetLevel()->CreateActor<Button>(VSRenderOrder::UI);
	float4 StartBPos = { 516, 300 };
	AntonioButton->setting("AntonioButton.BMP", "AntonioButton.BMP", "AntonioButton.BMP", StartBPos, { 154, 154 }, static_cast<int>(VSRenderOrder::UI), false);
	CharacterButton.push_back(AntonioButton);
	AntonioButton->SetClickCallBack(ClickAntonioButton);
	AntonioButton->Off();


	Button* ImeldaButton = GetLevel()->CreateActor<Button>(VSRenderOrder::UI);
	StartBPos = { 684, 300 };
	ImeldaButton->setting("ImeldaButton.BMP", "ImeldaButton.BMP", "ImeldaButton.BMP", StartBPos, { 154, 154 }, static_cast<int>(VSRenderOrder::UI), false);
	CharacterButton.push_back(ImeldaButton);
	ImeldaButton->SetClickCallBack(ClickImeldaButton);
	ImeldaButton->Off();

	Button* PasqualinaButton = GetLevel()->CreateActor<Button>(VSRenderOrder::UI);
	StartBPos = { 848, 300 };
	PasqualinaButton->setting("PasqualinaButton.BMP", "PasqualinaButton.BMP", "PasqualinaButton.BMP", StartBPos, { 154, 154 }, static_cast<int>(VSRenderOrder::UI), false);
	CharacterButton.push_back(PasqualinaButton);
	PasqualinaButton->SetClickCallBack(ClickPasqualinaButton);
	PasqualinaButton->Off();

	Button* GennaroButton = GetLevel()->CreateActor<Button>(VSRenderOrder::UI);
	StartBPos = { 1014, 300 };
	GennaroButton->setting("PasqualinaButton.BMP", "PasqualinaButton.BMP", "PasqualinaButton.BMP", StartBPos, { 154, 154 }, static_cast<int>(VSRenderOrder::UI), false);
	CharacterButton.push_back(GennaroButton);
	GennaroButton->SetClickCallBack(ClickGennaroButton);
	GennaroButton->Off();

	this->Off();
}

void SelectCharacter::Activate()
{
	this->On();
	for (Button* CharBtn : CharacterButton)
	{
		CharBtn->On();
	}
}
void SelectCharacter::Update(float _DeltaTime)
{

}