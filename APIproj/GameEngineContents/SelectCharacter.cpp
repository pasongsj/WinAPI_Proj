#include "SelectCharacter.h"
#include "ContentsEnums.h"
#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEngineCore/GameEngineLevel.h>
#include <GameEngineCore/GameEngineRender.h>
#include <GameEngineCore/Button.h>
#include <GameEngineCore/GameEngineCore.h>
#include <GameEngineCore/GameEngineResources.h>

#include "Player.h"

void SelectCharacter::Disable()
{
	for (Button* CharBtn : CharacterButton)
	{
		CharBtn->Off();
	}
	this->Off();

}

SelectCharacter::SelectCharacter()
{
}

SelectCharacter::~SelectCharacter()
{
}

// 버튼
void ClickAntonioButton()
{
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
	// 랜더이미지
	GameEngineRender* Screen = CreateRender("SelectCharScreen.bmp", VSRenderOrder::UI);
	float4 ScreenPos = GameEngineWindow::GetScreenSize().half();
	ScreenPos.y += 50;
	Screen->SetPosition(ScreenPos);
	Screen->SetScaleToImage();

	GameEngineRender* AlphaBG = CreateRender("LineBG.bmp", VSRenderOrder::UI);
	AlphaBG->SetScaleToImage();
	AlphaBG->SetAlpha(140);
	float4 LineBGPos = GameEngineWindow::GetScreenSize().half();
	LineBGPos.y = AlphaBG->GetImage()->GetImageScale().hy();
	AlphaBG->SetPosition(LineBGPos);
	
	//백버튼

	BackBtn = GetLevel()->CreateActor<Button>(VSRenderOrder::UI);
	float4 BackBtnScale = GameEngineResources::GetInst().ImageFind("ExitButton.BMP")->GetImageScale();
	BackBtn->setting("ExitButton.BMP", "ExitButton.BMP", "ExitButton.BMP", {1000,45}, BackBtnScale, static_cast<int>(VSRenderOrder::UI), false);
	BackBtn->Off();
	//BackBtn->SetClickCallBack(Disable);
	//--
	CharName.push_back("Antonio");
	CharName.push_back("Imelda");
	CharName.push_back("Pasqualina");
	CharName.push_back("Gennaro");

	// 랜더 버튼

	for (std::string _Name : CharName)
	{
		Button* NewCharBtn = GetLevel()->CreateActor<Button>(VSRenderOrder::UI);
		float4 BtnScale = GameEngineResources::GetInst().ImageFind(_Name + "Button.BMP")->GetImageScale();
		NewCharBtn->setting(_Name + "Button.BMP", _Name +"Button.BMP", _Name + "Button.BMP", ButtonPos, BtnScale, static_cast<int>(VSRenderOrder::UI), false);
		CharacterButton.push_back(NewCharBtn);
		NewCharBtn->Off();
		SetNextBtnPos();
	}
	CharacterButton[0]->SetClickCallBack(ClickAntonioButton);
	CharacterButton[1]->SetClickCallBack(ClickImeldaButton);
	CharacterButton[2]->SetClickCallBack(ClickPasqualinaButton);
	CharacterButton[3]->SetClickCallBack(ClickGennaroButton);

	this->Off();
}

void SelectCharacter::SetNextBtnPos()
{
	if (CharacterButton.size() % 4 == 0) {
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
	for (Button* CharBtn : CharacterButton)
	{
		CharBtn->On();
	}
}
void SelectCharacter::Update(float _DeltaTime)
{

}