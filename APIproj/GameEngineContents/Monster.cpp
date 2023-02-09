#include "Monster.h"
#include <ctime>
#include <GameEngineCore/GameEngineLevel.h>
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
	BodyCollision->SetPosition({ 0, -BodyCollision->GetScale().hy() });

	//srand(time(0));
	float4 CamPos = GetLevel()->GetCameraPos();
	SetMove(
		CamPos + float4(static_cast<float>(rand() % GameEngineWindow::GetScreenSize().ix()), static_cast<float>(rand() % GameEngineWindow::GetScreenSize().iy()))
	);
	AnimationRender->ChangeAnimation("Right_Idle");
	//ChangeState(MonsterState::IDLE); // ���� �� �⺻ ���� ����
}



void Monster::Update(float _DeltaTime)
{
	float4 Dir = Player::MainPlayer->GetPos() - GetPos();
	// Dir.y = 0.0f;
	Dir.Normalize();
	SetMove(Dir * 200.0f * _DeltaTime);

	/*if (false == BodyCollision->GetIsDmg()) {
		BodyCollision->CheckOffTime(_DeltaTime);
	}*/

	std::vector<GameEngineCollision*> Collision;
	if (true == BodyCollision->Collision({ .TargetGroup = static_cast<int>(VSRenderOrder::Player) }, Collision))
	{
		//BodyCollision->Off(); // ��� collision�Ǵ� ���� ���� ����
		for (size_t i = 0; i < Collision.size(); i++)
		{
			GameEngineActor* ColActor = Collision[i]->GetActor();
			int a = 0;

		}
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