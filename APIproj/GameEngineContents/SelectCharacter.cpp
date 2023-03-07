#include "SelectCharacter.h"
#include "ContentsEnums.h"
#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEngineCore/GameEngineLevel.h>
#include <GameEngineCore/GameEngineRender.h>
#include <GameEngineCore/Button.h>
#include <GameEngineCore/GameEngineCore.h>
#include <GameEngineCore/GameEngineResources.h>

#include "Player.h"


SelectCharacter* SelectCharacter::MainScreen = nullptr;

void Disable()
{
	if (nullptr == SelectCharacter::MainScreen) {
		MsgAssert("ĳ���� ����â�� ����� �������� �ʾҽ��ϴ�.");
	}
	for (Button* CharBtn : SelectCharacter::MainScreen->GetCharacterButtons())
	{
		CharBtn->Off();
	}
	SelectCharacter::MainScreen->GetBackBtn()->Off();
	SelectCharacter::MainScreen->Off();

	GameEngineSoundPlayer Dwn = GameEngineResources::GetInst().SoundPlayToControl("ButtonQuit.mp3");
	Dwn.Volume(0.7f);
	Dwn.LoopCount(1);

}

SelectCharacter::SelectCharacter()
{
}

SelectCharacter::~SelectCharacter()
{
}

// ��ư
void ClickAntonioButton()
{
	Player::PlayerName = "Antonio";
	GameEngineCore::GetInst()->ChangeLevel("InlaidLibraryLevel");
	Disable();
	Player::BasicWeapon = "Whip";
	GameEngineSoundPlayer Dwn = GameEngineResources::GetInst().SoundPlayToControl("ButtonDown.mp3");
	Dwn.Volume(0.7f);
	Dwn.LoopCount(1);
}

void ClickImeldaButton()
{
	Player::PlayerName = "Imelda";
	GameEngineCore::GetInst()->ChangeLevel("InlaidLibraryLevel");
	Disable();
	Player::BasicWeapon = "MagicWand";
	GameEngineSoundPlayer Dwn = GameEngineResources::GetInst().SoundPlayToControl("ButtonDown.mp3");
	Dwn.Volume(0.7f);
	Dwn.LoopCount(1);
}

void ClickPasqualinaButton()
{
	Player::PlayerName = "Pasqualina";
	GameEngineCore::GetInst()->ChangeLevel("InlaidLibraryLevel");
	Disable();
	Player::BasicWeapon = "RuneTracer";
	GameEngineSoundPlayer Dwn = GameEngineResources::GetInst().SoundPlayToControl("ButtonDown.mp3");
	Dwn.Volume(0.7f);
	Dwn.LoopCount(1);
}
void ClickGennaroButton()
{
	Player::PlayerName = "Gennaro";
	GameEngineCore::GetInst()->ChangeLevel("InlaidLibraryLevel");
	Disable();
	Player::BasicWeapon = "Knife";
	GameEngineSoundPlayer Dwn = GameEngineResources::GetInst().SoundPlayToControl("ButtonDown.mp3");
	Dwn.Volume(0.7f);
	Dwn.LoopCount(1);
}

void SelectCharacter::Start()
{
	MainScreen = this;
	// �����̹���
	GameEngineRender* Screen = CreateRender("SelectCharScreen.bmp", VSRenderOrder::UI);
	float4 ScreenPos = GameEngineWindow::GetScreenSize().half();
	ScreenPos.y += 50;
	Screen->SetPosition(ScreenPos);
	Screen->SetScaleToImage();

	GameEngineRender* AlphaBG = CreateRender("LineBG.bmp", VSRenderOrder::UI); //�����̹��� ��� ����
	AlphaBG->SetScaleToImage();
	AlphaBG->SetAlpha(140);
	float4 LineBGPos = GameEngineWindow::GetScreenSize().half();
	LineBGPos.y = AlphaBG->GetImage()->GetImageScale().hy();
	AlphaBG->SetPosition(LineBGPos);
	
	//���ư

	BackBtn = GetLevel()->CreateActor<Button>(VSRenderOrder::UI);
	float4 BackBtnScale = GameEngineResources::GetInst().ImageFind("ExitButton.BMP")->GetImageScale();
	BackBtn->setting("ExitButton.BMP", "ExitButton.BMP", "ExitButton.BMP", {1000,45}, BackBtnScale, static_cast<int>(VSRenderOrder::UI), false);
	BackBtn->Off();
	BackBtn->SetClickCallBack(Disable);

	//--
	CharName.push_back("Antonio");
	CharName.push_back("Imelda");
	CharName.push_back("Pasqualina");
	CharName.push_back("Gennaro");

	// ���� ��ư

	for (std::string _Name : CharName)
	{
		Button* NewCharBtn = GetLevel()->CreateActor<Button>(VSRenderOrder::UI);
		float4 BtnScale = GameEngineResources::GetInst().ImageFind(_Name + "Button.BMP")->GetImageScale();
		NewCharBtn->setting(_Name + "Button.BMP", _Name +"Button.BMP", _Name + "Button.BMP", ButtonPos, BtnScale, static_cast<int>(VSRenderOrder::UI), false);
		CharacterButtons.push_back(NewCharBtn);
		NewCharBtn->Off();
		SetNextBtnPos();
	}
	CharacterButtons[0]->SetClickCallBack(ClickAntonioButton);
	CharacterButtons[1]->SetClickCallBack(ClickImeldaButton);
	CharacterButtons[2]->SetClickCallBack(ClickPasqualinaButton);
	CharacterButtons[3]->SetClickCallBack(ClickGennaroButton);

	this->Off();
}

void SelectCharacter::SetNextBtnPos() // ĳ���� ��ư ���� - ��ġ ����ȭ �ʿ�
{
	if (CharacterButtons.size() % 4 == 0) {
		ButtonPos.x = 516;
		ButtonPos.y += 168;
	}
	else
	{
		ButtonPos.x += 168;
	}
}

void SelectCharacter::Activate()
{
	this->On();
	BackBtn->On();
	for (Button* CharBtn : CharacterButtons)
	{
		CharBtn->On();
	}
}
