#include "Monster.h"
//#include <ctime>
#include <GameEngineBase/GameEngineRandom.h>
#include <GameEngineCore/GameEngineLevel.h>
#include <GameEngineCore/GameEngineRender.h>
#include <GameEngineCore/GameEngineCollision.h>
#include "ContentsEnums.h"
#include "Player.h"
#include "Items.h"

Monster::Monster()
{
}

Monster::~Monster()
{
}

void Monster::Attack(int _Att) {
	Hp -= _Att;
	IsAttacked = true;
	BodyCollision->Off();
}

void Monster::Start()
{
	AnimationRender = CreateRender(VSRenderOrder::Monster);
	AnimationRender->SetScale({ 70, 140 });

	{
		AnimationRender->CreateAnimation({ .AnimationName = "Right_Move",  .ImageName = "RightDust.bmp", .Start = 0, .End = 1, .InterTime = 0.1f });
		AnimationRender->CreateAnimation({ .AnimationName = "Right_Beaten",  .ImageName = "RightDustDmged.bmp", .Start = 0, .End = 1, .InterTime = 0.1f , .Loop = false });
		AnimationRender->CreateAnimation({ .AnimationName = "Right_Dead",  .ImageName = "RightDustDead.bmp", .Start = 0, .End = 9, .InterTime = 0.05f, .Loop = false });
	}
	{
		AnimationRender->CreateAnimation({ .AnimationName = "Left_Move",  .ImageName = "LeftDust.bmp", .Start = 0, .End = 1, .InterTime = 0.1f });
		AnimationRender->CreateAnimation({ .AnimationName = "Left_Beaten",  .ImageName = "LeftDustDmged.bmp", .Start = 0, .End = 1, .InterTime = 0.1f, .Loop = false });
		AnimationRender->CreateAnimation({ .AnimationName = "Left_Dead",  .ImageName = "LeftDustDead.bmp", .Start = 0, .End = 9, .InterTime = 0.05f, .Loop = false });
	}
	BodyCollision = CreateCollision(VSRenderOrder::Monster);
	BodyCollision->SetScale({ 70, 140 });
	BodyCollision->SetPosition({ 0, -30 });

	//srand(time(0));
	float4 PlayerPos = GetLevel()->GetCameraPos() + GameEngineWindow::GetScreenSize().half();
	float4 RandPos = PlayerPos + float4{ GameEngineRandom::MainRandom.RandomFloat(-1, 1) ,GameEngineRandom::MainRandom.RandomFloat(-1, 1) }*GameEngineWindow::GetScreenSize().hix();
	SetPos(
		RandPos
		//CamPos + float4(static_cast<float>(rand() % GameEngineWindow::GetScreenSize().ix()), static_cast<float>(rand() % GameEngineWindow::GetScreenSize().iy()))
	);
	AnimationRender->ChangeAnimation("Right_Move");
	
	
	// 임시
	SetHp(20);
	Dmg = 5;
	//ChangeState(MonsterState::IDLE); // 시작 시 기본 상태 설정
}



void Monster::Update(float _DeltaTime)
{
	UpdateState(_DeltaTime);
	SetMove(MoveVec * MoveSpeed * _DeltaTime); // if state == attacted면 멈추게 한다.

	int a = 0;

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
	MoveVec.Normalize();
	DirCheck("Move");

	if (Hp <= 0) {
		ChangeState(MonsterState::DEAD);
		//this->Death();
		//break;
	}
	else if(true == IsAttacked){
		IsAttacked = false;
		ChangeState(MonsterState::BEATEN);
		//break;
	}

}
void Monster::MoveEnd() {
	MoveVec = (- MoveVec) * 3; // 넉백?
}


void Monster::BeatenStart()
{
	DirCheck("Beaten");
}
void Monster::BeatenUpdate(float _Time)
{
	MoveVec = float4::Zero;
	DirCheck("Beaten");
	// 타격 애니메이션 돌리고 그동안 movevec 0으로 만듦
	if (AnimationRender->IsAnimationEnd())
	{
		ChangeState(MonsterState::MOVE);
	}//IsAnimationEnd())
}
void Monster::BeatenEnd()
{
	BodyCollision->On();
}


void Monster::DeadStart()
{
	BodyCollision->Off(); // 죽는동안 피격 x효과
	MoveVec = float4::Zero;
	DirCheck("Dead");
}
void Monster::DeadUpdate(float _Time)
{
	DirCheck("Dead");
	if (AnimationRender->IsAnimationEnd())
	{
		GetLevel();
		Items* Actor = GetLevel()->CreateActor<Items>(VSRenderOrder::Item);
		Actor->SetPos(GetPos());
		this->Death();
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