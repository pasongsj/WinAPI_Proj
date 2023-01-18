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
		//Render->SetFrame(0);
	}
	/*SetMove(GameEngineWindow::GetScreenSize().half());*/
	/*{ // 예시내용
		AnimationRender = CreateRender(BubbleRenderOrder::BackGround);
		AnimationRender->SetScale({ 100, 100 });

		AnimationRender->CreateAnimation({ .AnimationName = "Test0",  .ImageName = "Heros.bmp", .Start = 0, .End = 5 });
		AnimationRender->CreateAnimation({ .AnimationName = "Test1",  .ImageName = "Heros.bmp", .Start = 20, .End = 26 });
		AnimationRender->ChangeAnimation("Test0");
	}*/
}

void Player::Update(float _DeltaTime)
{
	if (true == GameEngineInput::IsPress("LeftMove"))
	{
		SetMove(float4::Left * MoveSpeed * _DeltaTime);
	}

	if (true == GameEngineInput::IsPress("RightMove"))
	{
		SetMove(float4::Right * MoveSpeed * _DeltaTime);
	}

	if (true == GameEngineInput::IsPress("UpMove"))
	{
		SetMove(float4::Up * MoveSpeed * _DeltaTime);
	}

	if (true == GameEngineInput::IsPress("DownMove"))
	{
		SetMove(float4::Down * MoveSpeed * _DeltaTime);
	}
}

void Player::Render(float _DeltaTime)
{
	/*AccTime += _DeltaTime;
	float4 PlayerPos = GetPos();

	GameEngineImage* Image = GameEngineResources::GetInst().ImageFind("InlaidLibraryStage.bmp");
	GameEngineWindow::GetDoubleBufferImage()->TransCopy(Image, 0, PlayerPos, { 100, 200 });*/
}
