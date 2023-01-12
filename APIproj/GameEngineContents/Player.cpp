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

void Player::Update()
{
	SetMove(float4::Left * 0.0001f);
}

void Player::Render()
{
	float4 PlayerPos = GetPos();

	GameEngineImage* Image = GameEngineResources::GetInst().ImageFind("enemiesM.bmp");
	GameEngineWindow::GetDoubleBufferImage()->TransCopy(Image, 0, PlayerPos, { 100, 200 });
}
