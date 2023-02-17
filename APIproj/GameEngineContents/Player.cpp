#include "Player.h"
#include "ContentsEnums.h"

#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEngineCore/GameEngineResources.h>
#include <GameEngineCore/GameEngineLevel.h>
#include <GameEngineCore/GameEngineRender.h>
#include <GameEngineCore/GameEngineCollision.h>

#include "Weapon.h"
#include "Monster.h"
#include "Items.h"
Player* Player::MainPlayer;

Player::Player()
{
}

Player::~Player()
{
}


void Player::Start()
{
	MainPlayer = this;

	//SetMove(GameEngineWindow::GetScreenSize().half());
	//SetPos(GameEngineWindow::GetScreenSize().half());
	//SetMove(float4{2048,948});

	if (false == GameEngineInput::IsKey("LeftMove"))
	{
		GameEngineInput::CreateKey("LeftMove", 'A');
		GameEngineInput::CreateKey("RightMove", 'D');
		GameEngineInput::CreateKey("DownMove", 'S');
		GameEngineInput::CreateKey("UpMove", 'W');
	}


	{
		AnimationRender = CreateRender(VSRenderOrder::Player);
		AnimationRender->SetScale({ 130, 130 }); // 실제 크기 64 x 64
		{
			AnimationRender->CreateAnimation({ .AnimationName = "Right_Idle",  .ImageName = "RightAntonio.bmp" });
			AnimationRender->CreateAnimation({ .AnimationName = "Right_Move",  .ImageName = "RightAntonio.bmp", .Start = 0, .End = 2, .InterTime = 0.1f });
		}
		{
			AnimationRender->CreateAnimation({ .AnimationName = "Left_Idle",  .ImageName = "LeftAntonio.bmp" });
			AnimationRender->CreateAnimation({ .AnimationName = "Left_Move",  .ImageName = "LeftAntonio.bmp", .Start = 0, .End = 2, .InterTime = 0.1f });
		}

		{
			BodyCollision = CreateCollision(VSRenderOrder::Player);
			BodyCollision->SetScale({ 64, 64 });
			BodyCollision->SetPosition({ 0, -BodyCollision->GetScale().hy()});
		}
	}
	{
		MyWeapon.push_back(Weapon::Weapons["Whip"]);
		MyWeapon.back()->On();
		MyWeapon.back()->SetWeaponPos({120, -25});
		//MyWeapon.back()->SetDmg(5);

	}
	ChangeState(PlayerState::IDLE); // 시작 시 기본 상태 설정
	SetHp(100);
}

void Player::Movecalculation(float _DeltaTime)
{

	// collision.bmp 기준으로 collision 체크
	GameEngineImage* ColliImage = GameEngineResources::GetInst().ImageFind("InlaidLibraryCollision.BMP");
	if (nullptr == ColliImage)
	{
		MsgAssert("충돌용 맵 이미지가 없습니다.");
	}


	float4 NextPos = GetPos() + MoveVec * _DeltaTime; // 이동할 위치

	// 무한확장맵 collision Image 위치 맞추기  <inlaid library기준>
	while (NextPos.x < 0) {
		NextPos.x += ColliImage->GetImageScale().x;
	}
	NextPos.x = static_cast<float>((NextPos.ix()) % (ColliImage->GetImageScale().ix()));

	

	if (RGB(0, 0, 0) == ColliImage->GetPixelColor(NextPos, RGB(0, 0, 0))) // 다음 위치로 이동하지 못한다면
	{
		MoveVec = float4::Zero; // 이동값 zero
	}


	SetMove(MoveVec * _DeltaTime);
	GetLevel()->SetCameraMove(MoveVec * _DeltaTime);
	MoveVec = float4::Zero; // 이동 완료수 이동벡터값 초기화
}

void Player::Update(float _DeltaTime)
{
	// PlayerState가 변경될 수 있음을 인지해야한다. - 수정필요
	std::vector<GameEngineCollision*> Collision;
	if (true == BodyCollision->Collision({ .TargetGroup = static_cast<int>(VSRenderOrder::Monster) }, Collision))
	{
		for (size_t i = 0; i < Collision.size(); i++)
		{
			// Monster* FindMonster = Collision[i]->GetOwner<Monster>();

			GameEngineActor* ColActor = Collision[i]->GetActor();
			Monster* ColMonsterActor = dynamic_cast<Monster*> (ColActor);
			Hp -= ColMonsterActor->GetDmg();
		//	ColActor->Death();

		}
	}

	// 아이템 획득 콜리전
	//std::vector<GameEngineCollision*> Collision;
	Collision.clear();
	if (true == BodyCollision->Collision({ .TargetGroup = static_cast<int>(VSRenderOrder::Item) , .TargetColType  = CollisionType::CT_Rect}, Collision))
	{
		for (size_t i = 0; i < Collision.size(); i++)
		{
			GameEngineActor* ColActor = Collision[i]->GetActor();
			Items* ColItemActor = dynamic_cast<Items*> (ColActor);
			Exp += ColItemActor->GetExp();
			ColItemActor->Death();
			//	ColActor->Death();

		}
	}


	// 가지고 있는 무기 쿨타임 업데이트
	for (Weapon* arm : MyWeapon) {
		//float4 _Pos = GetPos();
		arm->SetPos(GetPos()+arm->GetWeaponPos());
		arm->WaitTime += _DeltaTime;
		if (arm->WaitTime > arm->GetCoolTime())
		{
			arm->WaitTime = 0;
			arm->On();
		}

	}

	
	UpdateState(_DeltaTime);
	Movecalculation(_DeltaTime);
}

void Player::DirCheck(const std::string_view& _AnimationName)
{
	std::string PrevDirString = DirString;
	AnimationRender->ChangeAnimation(DirString + _AnimationName.data());
	if (GameEngineInput::IsPress("LeftMove"))
	{
		DirString = "Left_";
	}
	else if (GameEngineInput::IsPress("RightMove"))
	{
		DirString = "Right_";
	}
	if (PrevDirString != DirString)
	{
		AnimationRender->ChangeAnimation(DirString + _AnimationName.data());
	}
}

void Player::Render(float _DeltaTime)
{

}
