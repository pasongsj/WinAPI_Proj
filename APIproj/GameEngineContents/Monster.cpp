#include "Monster.h"

#include <GameEngineCore/GameEngineRender.h>
#include <GameEngineCore/GameEngineCollision.h>
#include "ContentsEnums.h"
#include "Player.h"
Monster::Monster()
{
}

Monster::~Monster()
{
}

void Monster::Start()
{
	AnimationRender = CreateRender(VSRenderOrder::Monster);
	AnimationRender->SetScale({ 160, 160 });

	{
		AnimationRender->CreateAnimation({ .AnimationName = "Right_Idle",  .ImageName = "RightDustElemental.bmp", .Start = 0, .End = 1, .InterTime = 0.1f });
		AnimationRender->CreateAnimation({ .AnimationName = "Right_Dead",  .ImageName = "RightDustElementalDead.bmp", .Start = 0, .End = 9, .InterTime = 0.1f, .Loop = false });
	}
	{
		AnimationRender->CreateAnimation({ .AnimationName = "Left_Idle",  .ImageName = "LeftDustElemental.bmp", .Start = 0, .End = 1, .InterTime = 0.1f });
		AnimationRender->CreateAnimation({ .AnimationName = "Left_Dead",  .ImageName = "LeftDustElementalDead.bmp", .Start = 0, .End = 9, .InterTime = 0.1f, .Loop = false });
	}
	BodyCollision = CreateCollision(VSRenderOrder::Monster);
	BodyCollision->SetScale({ 60,60 });
	BodyCollision->SetDamage(10);
	BodyCollision->SetPosition({ 0, -BodyCollision->GetScale().hy() });


	AnimationRender->ChangeAnimation("Right_Idle");
	//ChangeState(MonsterState::IDLE); // 시작 시 기본 상태 설정
}



void Monster::Update(float _DeltaTime)
{
	float4 Dir = Player::MainPlayer->GetPos() - GetPos();
	// Dir.y = 0.0f;
	Dir.Normalize();
	SetMove(Dir * 200.0f * _DeltaTime);



	std::vector<GameEngineCollision*> Collision;
	if (true == BodyCollision->Collision({ .TargetGroup = static_cast<int>(VSRenderOrder::Player) }, Collision))
	{
		BodyCollision->Off(); // 계속 collision되는 것을 막기 위해
		for (size_t i = 0; i < Collision.size(); i++)
		{
			GameEngineActor* ColActor = Collision[i]->GetActor();
			ColActor->Attack(BodyCollision->GetDamage());
			int a = 0;

		}
	}

	if (BodyCollision->IsUpdate() == false) { // off상태라면
		CollisionOffTime += _DeltaTime;
	}
	if (CollisionOffTime > 1.0f) { // 1초 후 collsion on시킴
		BodyCollision->On();
		CollisionOffTime = 0.0f;
	}

	//std::vector<GameEngineActor*> Actors = GetLevel()->GetActors(BubbleRenderOrder::Player);

	//for (size_t i = 0; i < Actors.size(); i++)
	//{
	//	float4 Dir = Actors[i]->GetPos() - GetPos();
	//	if (Dir.Size() <= 100.0f)
	//	{
	//		int a = 0;
	//	}
	//}

}