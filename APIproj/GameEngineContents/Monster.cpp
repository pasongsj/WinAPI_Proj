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

void Monster::Attack(float _Att) {
	Hp -= _Att;
	IsAttacked = true;
	BodyCollision->Off();
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
	SetPos(
		RandPos
		//CamPos + float4(static_cast<float>(rand() % GameEngineWindow::GetScreenSize().ix()), static_cast<float>(rand() % GameEngineWindow::GetScreenSize().iy()))
	);

	// 임시
	/*SetHp(5);
	Dmg = 5;*/
	//ChangeState(MonsterState::IDLE); // 시작 시 기본 상태 설정
}

void Monster::Setting()
{
	if ("Dust" == MonsterName)
	{
		Hp = 5;
		Dmg = 5;
		MoveSpeed = 140;
		Exp = 1;
		EndFrame[0] = 1;
		EndFrame[1] = 1;
		EndFrame[2] = 9;

	}
	else if ("Musc" == MonsterName)
	{
		//1 - 2:00, 6:00, 7:00, 17:00
		Hp = 1;
		Dmg = 2;
		MoveSpeed = 160;
		Exp = 1;
		//2 - 7:00, 8:00, 10:00, 14:00, 17:00
		Hp = 13;
		Dmg = 4;
		MoveSpeed = 160;
		Exp = 1;

		EndFrame[0] = 3;
		EndFrame[1] = 3;
		EndFrame[2] = 1;

	}
	else if ("Mummy" == MonsterName)
	{
		Hp = 15;
		Dmg = 3;
		MoveSpeed = 140;
		Exp = 2;

		EndFrame[0] = 3;
		EndFrame[1] = 2;
		EndFrame[2] = 4;

	}
	else if ("Dullahan" == MonsterName)
	{
		//2 - 6:00, 7:00, 12:00, 13:00, 16:00, 23:00
		Hp = 70;
		Dmg = 8;
		MoveSpeed = 100;
		Exp = 2;
		//3 - 16:00, 19:00, 20:00, 23:00
		Hp = 150;
		Dmg = 8;
		MoveSpeed = 100;
		Exp = 2;

		EndFrame[0] = 1;
		EndFrame[1] = 1;
		EndFrame[2] = 3;

	}
	else if ("ColossalMedusaHead" == MonsterName)
	{ // 추가설정 필요
		Hp = 1;
		Dmg = 1;
		MoveSpeed = 600;
		Exp = 1;
		//
		Hp = 25;
		Dmg = 1;
		MoveSpeed = 240;
		Exp = 2;

		EndFrame[0] = 3;
		EndFrame[1] = 3;
		EndFrame[2] = 4;

	}
	else if ("LionHead" == MonsterName) // 
	{
		Hp = 3*Player::MainPlayer->GetHp();
		Dmg = 3;
		MoveSpeed = 200;
		Exp = 2;

		EndFrame[0] = 2;
		EndFrame[1] = 2;
		EndFrame[2] = 3;

	}
	else if ("Ghost" == MonsterName)
	{
		Hp = 10;
		Dmg = 5;
		MoveSpeed = 200;
		Exp = 2;

		EndFrame[0] = 1;
		EndFrame[1] = 1;
		EndFrame[2] = 6;

	}

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