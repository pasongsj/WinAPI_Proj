#include <GameEngineBase/GameEnginePath.h>
#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEngineCore/GameEngineResources.h>
#include <GameEngineCore/GameEngineLevel.h>
#include <GameEngineCore/GameEngineRender.h>
#include "ContentsEnums.h"
#include "Player.h"


// State
void Player::ChangeState(PlayerState _State)
{
	PlayerState NextState = _State;
	PlayerState PrevState = StateValue;

	StateValue = NextState;

	switch (PrevState)
	{
	case PlayerState::IDLE:
		IdleEnd();
		break;
	case PlayerState::MOVE:
		MoveEnd();
		break;
	case PlayerState::IDLE_DMGED:
		IdleDmgedEnd();
		break;
	case PlayerState::MOVE_DMGED:
		MoveDmgedEnd();
		break;
	default:
		break;
	}


	switch (NextState)
	{
	case PlayerState::IDLE:
		IdleStart();
		break;
	case PlayerState::MOVE:
		MoveStart();
		break;
	case PlayerState::IDLE_DMGED:
		IdleDmgedStart();
		break;
	case PlayerState::MOVE_DMGED:
		MoveDmgedStart();
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
	case PlayerState::IDLE_DMGED:
		IdleDmgedUpdate(_Time);
		break;
	case PlayerState::MOVE_DMGED:
		MoveDmgedUpdate(_Time);
		break;
	default:
		break;
	}

}

// FSM 내가 어떤일을 할때 이동하면서 가만히 있을수 없다.
void Player::IdleStart()
{
	DirCheck("Idle");
}
void Player::IdleUpdate(float _Time)
{
	DirCheck("Idle");
	bool is_Col = CheckMonsterCollision(); //충돌했다면
	if (GameEngineInput::IsPress("LeftMove") || GameEngineInput::IsPress("RightMove") || GameEngineInput::IsPress("DownMove") || GameEngineInput::IsPress("UpMove"))
	{
		if (true == is_Col)
		{
			InvincibleStateDelay = 0.5f;
			BodyCollision->Off();
			ChangeState(PlayerState::MOVE_DMGED);
		}
		else
		{
			ChangeState(PlayerState::MOVE);
		}
		//return; // 보통 스테이트를 체인지하면 아래 코드를 실행되면 
	}
	else if (true == is_Col)
	{
		InvincibleStateDelay = 0.5f;
		BodyCollision->Off();
		ChangeState(PlayerState::IDLE_DMGED);
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
	if(true == CheckMonsterCollision()) //충돌했다면
	{
		InvincibleStateDelay = 0.5f;
		BodyCollision->Off();
		ChangeState(PlayerState::MOVE_DMGED);
	}
	PressMove();
	DirCheck("Move");
}
void Player::MoveEnd() {

}


void Player::IdleDmgedStart()
{
	DirCheck("Idle_Dmged");
}
void Player::IdleDmgedUpdate(float _Time)
{
	DirCheck("Idle_Dmged");
	PressMove();
	/*DmgStateDelay -= _Time;
	if (DmgStateDelay <= 0)
	{
		ChangeState(PlayerState::IDLE);
	}*/
}
void Player::IdleDmgedEnd() {

}


void Player::MoveDmgedStart()
{
	DirCheck("Move_Dmged");
}
void Player::MoveDmgedUpdate(float _Time)
{
	DirCheck("Move_Dmged");
	PressMove();

	/*DmgStateDelay -= _Time;
	if (DmgStateDelay <= 0)
	{
		ChangeState(PlayerState::IDLE);
	}*/
}
void Player::MoveDmgedEnd() {

}