#include "Monster.h"
//#include <ctime>
#include <GameEngineBase/GameEngineRandom.h>
#include <GameEngineCore/GameEngineLevel.h>
#include <GameEngineCore/GameEngineRender.h>
#include <GameEngineCore/GameEngineCollision.h>
#include "ContentsEnums.h"
#include "Player.h"
#include "Items.h"

std::queue<Monster*> Monster::DeadMonsters;
std::string Monster::MonsterName = "Dust";


Monster::Monster()
{
}

Monster::~Monster()
{
}

void Monster::Attack(float _Att, float _KnockBack) {
	Hp -= _Att;
	IsAttacked = true;
	BodyCollision->Off();
	KnockBack = _KnockBack;
}

void Monster::KnockBackLessAttack(float _Att, float _StateDelay)
{
	Hp -= _Att;
	BodyCollision->Off();
	InvincibleStateDelay = _StateDelay;
}
void Monster::Reset()
{
	IsBoxBoss = false;
	Setting();
	AnimationRender = CreateRender(VSRenderOrder::Monster);
	AnimationRender->SetScale(MonsterRenderScale);

	std::string RImage = "Right" + MonsterName + ".BMP";
	std::string LImage = "Left" + MonsterName + ".BMP";
	std::string DmgRImage = "Right" + MonsterName + "Dmged.BMP";
	std::string DmgLImage = "Left" + MonsterName + "Dmged.BMP";
	std::string DeadRImage = "Right" + MonsterName + "Dead.BMP";
	std::string DeadLImage = "Left" + MonsterName + "Dead.BMP";
	{
		AnimationRender->CreateAnimation({ .AnimationName = "Right_Move",  .ImageName = RImage, .Start = 0, .End = EndFrame[0], .InterTime = 0.1f });
		AnimationRender->CreateAnimation({ .AnimationName = "Right_Beaten",  .ImageName = DmgRImage, .Start = 0, .End = EndFrame[1], .InterTime = 0.1f , .Loop = false });
		AnimationRender->CreateAnimation({ .AnimationName = "Right_Dead",  .ImageName = DeadRImage, .Start = 0, .End = EndFrame[2], .InterTime = 0.05f, .Loop = false });
	}
	{
		AnimationRender->CreateAnimation({ .AnimationName = "Left_Move",  .ImageName = LImage, .Start = 0, .End = EndFrame[0], .InterTime = 0.1f });
		AnimationRender->CreateAnimation({ .AnimationName = "Left_Beaten",  .ImageName = DmgLImage, .Start = 0, .End = EndFrame[1], .InterTime = 0.1f, .Loop = false });
		AnimationRender->CreateAnimation({ .AnimationName = "Left_Dead",  .ImageName = DeadLImage, .Start = 0, .End = EndFrame[2], .InterTime = 0.05f, .Loop = false });
	}
	BodyCollision = CreateCollision(VSRenderOrder::Monster);
	BodyCollision->SetScale(MonsterCollisionScale);
	BodyCollision->SetPosition({ 0, -(MonsterCollisionScale.hy() / 2) });
	IsAttacked = false;
	StateValue = MonsterState::MOVE;
	//AnimationRender->ChangeAnimation("Right_Move");
	SetPos(GetReGenPos());
	this->On();
}

void Monster::Start()
{
	Reset();
}

float4 Monster::GetReGenPos()
{
	float PosX = GetLevel()->GetCameraPos().x + GameEngineWindow::GetScreenSize().hx();
	int RandNum = GameEngineRandom::MainRandom.RandomInt(0, 9);
	if (0 == (RandNum & 1))
	{
		PosX += GameEngineWindow::GetScreenSize().hx() * 1.1f;
	}
	else
	{
		PosX -= GameEngineWindow::GetScreenSize().hx() * 1.1f;
	}
	float PosY = GameEngineRandom::MainRandom.RandomFloat(480,1375);//임시
	return float4{ PosX,PosY };
}



void Monster::Update(float _DeltaTime)
{

	UpdateState(_DeltaTime);
	SetMove(MoveVec * MoveSpeed * _DeltaTime); // if state == attacted면 멈추게 한다.

}

void Monster::DirCheck(const std::string_view& _AnimationName)
{
	std::string PrevDirString = DirString;
	AnimationRender->ChangeAnimation(DirString + _AnimationName.data());
	if (MoveVec.x < 0)
	{
		DirString = "Left_";
	}
	else if (MoveVec.x > 0)
	{
		DirString = "Right_";
	}
	if (PrevDirString != DirString)
	{
		AnimationRender->ChangeAnimation(DirString + _AnimationName.data());
	}
}


// FSM
void Monster::MoveStart()
{
	DirCheck("Move");
}
void Monster::MoveUpdate(float _Time)
{
	MoveVec = Player::MainPlayer->GetPos() - GetPos();
	if (MoveVec.Size() > GameEngineWindow::GetScreenSize().x * 2.5f) // 거리가 너무 멀어지는 경우 근처로 리젠
	{
		SetPos(GetReGenPos());
		MoveVec = Player::MainPlayer->GetPos() - GetPos();
	}
	MoveVec.Normalize();
	DirCheck("Move");
	if (false == BodyCollision->IsUpdate())
	{
		InvincibleStateDelay -= _Time;
		if (InvincibleStateDelay < 0.0f)
		{
			BodyCollision->On();
			InvincibleStateDelay = 0.0f;
		}
	}
	if (Hp <= 0) {
		BodyCollision->Off();
		ChangeState(MonsterState::DEAD);
		return;
	}
	else if(true == IsAttacked){
		IsAttacked = false;
		BodyCollision->Off();
		InvincibleStateDelay = 0.2f;
		ChangeState(MonsterState::BEATEN);
		return;
	}

}
void Monster::MoveEnd() {

	if (0.0f != KnockBack)
	{
		SetMove((- MoveVec) * KnockBack); // 넉백?
		KnockBack = 0;
	}
}


void Monster::BeatenStart()
{
	DirCheck("Beaten");
}
void Monster::BeatenUpdate(float _Time)
{
	MoveVec = float4::Zero;
	DirCheck("Beaten");
	InvincibleStateDelay -= _Time;
	if (InvincibleStateDelay < 0.0f)
	{
		BodyCollision->On();
		InvincibleStateDelay = 0.0f;
		ChangeState(MonsterState::MOVE);
	}

}
void Monster::BeatenEnd()
{
	//BodyCollision->On();
}


void Monster::DeadStart()
{
	//BodyCollision->Off(); // 죽는동안 피격 x효과
	MoveVec = float4::Zero;
	DirCheck("Dead");
}
void Monster::DeadUpdate(float _Time)
{
	DirCheck("Dead");
	if (AnimationRender->IsAnimationEnd())
	{
		// 아이템설정
		Items* Actor = nullptr;
		if (true == Items::ObtainedItems.empty()) // 생성
		{
			Actor = GetLevel()->CreateActor<Items>(VSRenderOrder::Item);
		}
		else // 재사용
		{
			Actor = Items::ObtainedItems.front();
			Items::ObtainedItems.pop();
			Actor->Reset();
		}
		Actor->SetPos(GetPos());
		Actor->SetExp(Exp);
		Actor->SetOwner(GetLevel());

		if (true == IsBoxBoss)
		{
			Items* Box = GetLevel()->CreateActor<Items>(VSRenderOrder::Item);
			Box->SetPos(GetPos());
			Box->SetExp(0, true);
			Box->SetOwner(GetLevel());
		}


		this->Off();
		DeadMonsters.push(this);
	}
}
void Monster::DeadEnd() {
}


// State
void Monster::ChangeState(MonsterState _State)
{
	MonsterState NextState = _State;
	MonsterState PrevState = StateValue;

	StateValue = NextState;

	switch (PrevState)
	{
	case MonsterState::MOVE:
		MoveEnd();
		break;
	case MonsterState::BEATEN:
		BeatenEnd();
		break;
	case MonsterState::DEAD:
		DeadEnd();
		break;
	default:
		break;
	}

	switch (NextState)
	{
	case MonsterState::MOVE:
		MoveStart();
		break;
	case MonsterState::BEATEN:
		BeatenStart();
		break;
	case MonsterState::DEAD:
		DeadStart();
		break;
	default:
		break;
	}


}

void Monster::UpdateState(float _Time)
{

	switch (StateValue)
	{
	case MonsterState::MOVE:
		MoveUpdate(_Time);
		break;
	case MonsterState::BEATEN:
		BeatenUpdate(_Time);
		break;
	case MonsterState::DEAD:
		DeadUpdate(_Time);
		break;
	default:
		break;
	}

}