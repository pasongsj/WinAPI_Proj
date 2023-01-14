#include "Player.h"
#include "ContentsEnums.h"

#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEngineCore/GameEngineResources.h>
#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEngineCore/GameEngineRender.h>

Player* Player::MainPlayer;

Player::Player()
{
}

Player::~Player()
{
}


void Player::Start()
{
	MainPlayer = this;

	SetMove(GameEngineWindow::GetScreenSize().half());


	if (false == GameEngineInput::IsKey("LeftMove"))
	{
		GameEngineInput::CreateKey("LeftMove", 'A');
		GameEngineInput::CreateKey("RightMove", 'D');
		GameEngineInput::CreateKey("DownMove", 'S');
		GameEngineInput::CreateKey("UpMove", 'W');
	}

	{
		GameEngineRender* Render = CreateRender("enemiesM.bmp", BubbleRenderOrder::BackGround);
		Render->SetScale({ 100, 100 });
		Render->SetFrame(0);
	}
	/*SetMove(GameEngineWindow::GetScreenSize().half());*/
}

void Player::Update(float _DeltaTime)
{
//	SetMove(float4::Left * 0.0001f* _DeltaTime);
}

void Player::Render(float _DeltaTime)
{
	/*AccTime += _DeltaTime;
	float4 PlayerPos = GetPos();

	GameEngineImage* Image = GameEngineResources::GetInst().ImageFind("InlaidLibraryStage.bmp");
	GameEngineWindow::GetDoubleBufferImage()->TransCopy(Image, 0, PlayerPos, { 100, 200 });*/
}
