#include "Player.h"
#include <GameEnginePlatform/GameEngineWindow.h>

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

	Rectangle(
		GameEngineWindow::GetDrawHdc(),
		PlayerPos.ix() - 50,
		PlayerPos.iy() - 50,
		PlayerPos.ix() + 50,
		PlayerPos.iy() + 50
	);

}