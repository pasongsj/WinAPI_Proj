#include "SelectCharacter.h"
#include "ContentsEnums.h"
#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEngineCore/GameEngineLevel.h>
#include <GameEngineCore/GameEngineRender.h>
#include <GameEngineCore/Button.h>
#include <GameEngineCore/GameEngineCore.h>

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
		MsgAssert("SelectScreen ���Ͱ� �������� �ʾҽ��ϴ�.");
		return;
	}
	TitleLevel::SelectScreen->Activate();*/
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
	AntonioButton->Off();
	AntonioButton->SetClickCallBack(ClickAntonioButton);


	Button* ImeldaButton = GetLevel()->CreateActor<Button>(VSRenderOrder::UI);
	StartBPos = { 684, 300 };
	ImeldaButton->setting("ImeldaButton.BMP", "ImeldaButton.BMP", "ImeldaButton.BMP", StartBPos, { 154, 154 }, static_cast<int>(VSRenderOrder::UI), false);
	CharacterButton.push_back(ImeldaButton);
	ImeldaButton->Off();

	Button* PasqualinaButton = GetLevel()->CreateActor<Button>(VSRenderOrder::UI);
	StartBPos = { 848, 300 };
	PasqualinaButton->setting("PasqualinaButton.BMP", "PasqualinaButton.BMP", "PasqualinaButton.BMP", StartBPos, { 154, 154 }, static_cast<int>(VSRenderOrder::UI), false);
	CharacterButton.push_back(PasqualinaButton);
	PasqualinaButton->Off();

	Button* GennaroButton = GetLevel()->CreateActor<Button>(VSRenderOrder::UI);
	StartBPos = { 1014, 300 };
	GennaroButton->setting("PasqualinaButton.BMP", "PasqualinaButton.BMP", "PasqualinaButton.BMP", StartBPos, { 154, 154 }, static_cast<int>(VSRenderOrder::UI), false);
	CharacterButton.push_back(GennaroButton);
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