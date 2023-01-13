#include "Player.h"
#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEngineCore/GameEngineResources.h>

Player::Player()
{
}

Player::~Player()
{
}


void Player::Start()
{
	SetMove(GameEngineWindow::GetScreenSize().half());
}

void Player::Update(float _DeltaTime)
{
	SetMove(float4::Left * 0.0001f* _DeltaTime);
}

void Player::Render(float _DeltaTime)
{
	AccTime += _DeltaTime;
	float4 PlayerPos = GetPos();

	GameEngineImage* Image = GameEngineResources::GetInst().ImageFind("enemiesM.bmp");
	GameEngineWindow::GetDoubleBufferImage()->TransCopy(Image, 0, PlayerPos, { 100, 200 });
}
