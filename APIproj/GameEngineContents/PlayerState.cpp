#include "Player.h"
#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEngineBase/GameEnginePath.h>
#include <GameEngineCore/GameEngineResources.h>
#include <GameEngineCore/GameEngineRender.h>
#include <GameEnginePlatform/GameEngineInput.h>
#include "ContentsEnums.h"


// State
void Player::ChangeState(PlayerState _State)
{
	PlayerState NextState = _State;
	PlayerState PrevState = StateValue;

	StateValue = NextState;

	switch (NextState)
	{
	case PlayerState::IDLE:
		IdleStart();
		break;
	case PlayerState::MOVE:
		MoveStart();
		break;
	default:
		break;
	}

	switch (PrevState)
	{
	case PlayerState::IDLE:
		IdleEnd();
		break;
	case PlayerState::MOVE:
		MoveEnd();
		break;
	default:
		break;
	}

}

void Player::UpdateState(float _Time)
{
	switch (StateValue)
	{
	case PlayerState::IDLE:
		IdleUpdate(_Time);
		break;
	case PlayerState::MOVE:
		MoveUpdate(_Time);
		break;
	default:
		break;
	}

}

// FSM ���� ����� �Ҷ� �̵��ϸ鼭 ������ ������ ����.
void Player::IdleStart()
{
	DirCheck("Idle");
}
void Player::IdleUpdate(float _Time)
{
	DirCheck("Idle");
	if (GameEngineInput::IsPress("LeftMove") || GameEngineInput::IsPress("RightMove"))
	{
		ChangeState(PlayerState::MOVE);
		return; // ���� ������Ʈ�� ü�����ϸ� �Ʒ� �ڵ带 ����Ǹ� 
	}
}
void Player::IdleEnd() {

}

void Player::MoveStart()
{
	DirCheck("Move");
}
void Player::MoveUpdate(float _Time)
{
	DirCheck("Move");
	if (
		false == GameEngineInput::IsPress("LeftMove") &&
		false == GameEngineInput::IsPress("RightMove")
		)
	{
		// 
		ChangeState(PlayerState::IDLE);
		return;
	}
	float4 MoveRange;

	if (true == GameEngineInput::IsPress("LeftMove"))
	{
		MoveRange += float4::Left;
		//SetMove(float4::Left * MoveSpeed * _Time);
	}

	if (true == GameEngineInput::IsPress("RightMove"))
	{
		MoveRange += float4::Right;
		//SetMove(float4::Right * MoveSpeed * _Time);
	}

	if (true == GameEngineInput::IsPress("UpMove"))
	{
		MoveRange += float4::Up;
		//SetMove(float4::Up * MoveSpeed * _Time);
	}
	else if (true == GameEngineInput::IsPress("DownMove"))
	{
		MoveRange += float4::Down;
		//SetMove(float4::Down * MoveSpeed * _Time);
	}
	SetMove(MoveRange * MoveSpeed * _Time);
}
void Player::MoveEnd() {

}
