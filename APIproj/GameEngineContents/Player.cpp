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
		AnimationRender = CreateRender(BubbleRenderOrder::Player);
		AnimationRender->SetScale({ 100, 100 });
		AnimationRender->CreateAnimation({ .AnimationName = "Right_Idle",  .ImageName = "RightAntonio.bmp" });
		AnimationRender->CreateAnimation({ .AnimationName = "Right_Move",  .ImageName = "RightAntonio.bmp", .Start = 0, .End = 2, .InterTime = 0.1f });

		
		AnimationRender->CreateAnimation({ .AnimationName = "Left_Idle",  .ImageName = "LeftAntonio.bmp" });
		AnimationRender->CreateAnimation({ .AnimationName = "Left_Move",  .ImageName = "LeftAntonio.bmp", .Start = 0, .End = 2, .InterTime = 0.1f });
	}
	ChangeState(PlayerState::IDLE);
}

void Player::Update(float _DeltaTime)
{
	UpdateState(_DeltaTime);
}

void Player::DirCheck(const std::string_view& _AnimationName)
{
	std::string PrevDirString = DirString;
	AnimationRender->ChangeAnimation(DirString + _AnimationName.data());
	if (GameEngineInput::IsPress("LeftMove"))
	{
		DirString = "Left_";
	}
	else if (GameEngineInput::IsPress("RightMove"))
	{
		DirString = "Right_";
	}
	if (PrevDirString != DirString)
	{
		AnimationRender->ChangeAnimation(DirString + _AnimationName.data());
	}
}

void Player::Render(float _DeltaTime)
{
	/*AccTime += _DeltaTime;
	float4 PlayerPos = GetPos();

	GameEngineImage* Image = GameEngineResources::GetInst().ImageFind("InlaidLibraryStage.bmp");
	GameEngineWindow::GetDoubleBufferImage()->TransCopy(Image, 0, PlayerPos, { 100, 200 });*/
}
