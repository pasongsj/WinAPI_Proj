#include "Player.h"
#include "ContentsEnums.h"

#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEngineCore/GameEngineResources.h>
#include <GameEngineCore/GameEngineLevel.h>
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

void Player::Movecalculation(float _DeltaTime)
{

	if (false == GameEngineInput::IsPress("LeftMove") && false == GameEngineInput::IsPress("RightMove") && false == GameEngineInput::IsPress("DownMove") && false == GameEngineInput::IsPress("UpMove"))
	{
		MoveVec *= 0.01f;
	}

	// ColMap.BMP 이걸 변수로하면 
	GameEngineImage* ColImage = GameEngineResources::GetInst().ImageFind("InlaidLibraryCollision.BMP");
	if (nullptr == ColImage)
	{
		MsgAssert("충돌용 맵 이미지가 없습니다.");
	}


	// 내 미래의 위치는 여기인데/.

	bool Check = true;
	float4 NextPos = GetPos() + MoveVec * _DeltaTime;

	//NextPos -= GetLevel()->GetCameraPos();
	/*float4 CameraPos = float4::Zero;
	if (true == IsCameraEffect)
	{
		CameraPos = GetActor()->GetLevel()->GetCameraPos();
	}
	float4 RenderPos = GetActor()->GetPos() + Position - CameraPos;*/

	if (RGB(0, 0, 0) == ColImage->GetPixelColor(NextPos, RGB(0, 0, 0)))
	{
		Check = false;
		// MoveDir = float4::Zero;
	}

	//if (false == Check)
	//{
	//	while (true)
	//	{
	//		MoveVec.y -= 1;

	//		float4 NextPos = GetPos() + MoveVec * _DeltaTime;

	//		if (RGB(0, 0, 0) == ColImage->GetPixelColor(NextPos, RGB(0, 0, 0)))
	//		{
	//			continue;
	//		}

	//		break;
	//	}
	//}

	SetMove(MoveVec * _DeltaTime);
	GetLevel()->SetCameraMove(MoveVec * _DeltaTime);
}

void Player::Update(float _DeltaTime)
{
	UpdateState(_DeltaTime);
	Movecalculation(_DeltaTime);
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
