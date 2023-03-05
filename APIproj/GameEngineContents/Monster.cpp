#include "Monster.h"
//#include <ctime>
#include <GameEngineBase/GameEngineRandom.h>
#include <GameEngineCore/GameEngineLevel.h>
#include <GameEngineCore/GameEngineRender.h>
#include <GameEngineCore/GameEngineCollision.h>
#include "ContentsEnums.h"
#include "Player.h"
#include "Items.h"


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

void Monster::KnockBackLessAttack(float _Att)
{
	Hp -= _Att;
	BodyCollision->Off();
	InvincibleStateDelay = 0.3f;
}

void Monster::Start()
{
	Setting();
	AnimationRender = CreateRender(VSRenderOrder::Monster);
	AnimationRender->SetScale({ 70, 140 });

	std::string RImage = "Right" + MonsterName + ".BMP";
	std::string LImage = "Left" + MonsterName + ".BMP";
	std::string DmgRImage = "Right" + MonsterName + "Dmged.BMP";
	std::string DmgLImage = "Left" + MonsterName + "Dmged.BMP";
	std::string DeadRImage = "Right" + MonsterName + "Dead.BMP";
	std::string DeadLImage = "Left" + MonsterName + "Dead.BMP";
	{
		AnimationRender->CreateAnimation({ .AnimationName = "Right_Move",  .ImageName = RImage, .Start = 0, .End = EndFrame[0], .InterTime = 0.1f});
		AnimationRender->CreateAnimation({ .AnimationName = "Right_Beaten",  .ImageName = DmgRImage, .Start = 0, .End = EndFrame[1], .InterTime = 0.1f , .Loop = false });
		AnimationRender->CreateAnimation({ .AnimationName = "Right_Dead",  .ImageName = DeadRImage, .Start = 0, .End = EndFrame[2], .InterTime = 0.05f, .Loop = false });
	}
	{
		AnimationRender->CreateAnimation({ .AnimationName = "Left_Move",  .ImageName = LImage, .Start = 0, .End = EndFrame[0], .InterTime = 0.1f });
		AnimationRender->CreateAnimation({ .AnimationName = "Left_Beaten",  .ImageName = DmgLImage, .Start = 0, .End = EndFrame[1], .InterTime = 0.1f, .Loop = false });
		AnimationRender->CreateAnimation({ .AnimationName = "Left_Dead",  .ImageName = DeadLImage, .Start = 0, .End = EndFrame[2], .InterTime = 0.05f, .Loop = false });
	}
	BodyCollision = CreateCollision(VSRenderOrder::Monster);
	BodyCollision->SetScale({ 70, 140 });
	BodyCollision->SetPosition({ 0, -30 });
	AnimationRender->ChangeAnimation("Right_Move");

	//srand(time(0));
	float4 PlayerPos = GetLevel()->GetCameraPos() + GameEngineWindow::GetScreenSize().half();
	float4 RandPos = PlayerPos + float4{ GameEngineRandom::MainRandom.RandomFloat(-1, 1) ,GameEngineRandom::MainRandom.RandomFloat(-1, 1) }*GameEngineWindow::GetScreenSize().hx();
	SetPos(RandPos);
}



void Monster::Update(float _DeltaTime)
{
	InvincibleStateDelay -= _DeltaTime;
	if (InvincibleStateDelay < 0.0f)
	{
		BodyCollision->On();
		InvincibleStateDelay = 0.0f;
		ChangeState(MonsterState::MOVE);
	}

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
	MoveVec.Normalize();
	DirCheck("Move");

	if (Hp <= 0) {
		BodyCollision->Off();
		ChangeState(MonsterState::DEAD);
	}
	else if(true == IsAttacked){
		IsAttacked = false;
		BodyCollision->Off();
		InvincibleStateDelay = 0.3f;
		ChangeState(MonsterState::BEATEN);
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
	// 타격 애니메이션 돌리고 그동안 movevec 0으로 만듦
	//if (AnimationRender->IsAnimationEnd())
	//{
	//	ChangeState(MonsterState::MOVE);
	//}//IsAnimationEnd())
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
		Items* Actor = GetLevel()->CreateActor<Items>(VSRenderOrder::Item);
		Actor->SetPos(GetPos());
		Actor->SetExp(Exp);
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