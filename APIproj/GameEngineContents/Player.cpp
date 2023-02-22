#include "Player.h"
#include "ContentsEnums.h"

#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEngineCore/GameEngineResources.h>
#include <GameEngineCore/GameEngineLevel.h>
#include <GameEngineCore/GameEngineRender.h>
#include <GameEngineCore/GameEngineCollision.h>

//#include "Weapon.h"
#include "Monster.h"
#include "Items.h"

bool Player::IsStop = false;
Player* Player::MainPlayer;
std::string Player::PlayerName = "Antonio.bmp";

Player::Player()
{
}

Player::~Player()
{
}


void Player::Start()
{
	MainPlayer = this;
	if ("" == PlayerName) {
		MsgAssert("플레이어가 선택되지 않았습니다.");
		return;
	}

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
	if ("Antonio" == PlayerName)
	{
		Hp = 120;
	}

	std::string RImage = "Right" + PlayerName + ".BMP";
	std::string LImage = "Left" + PlayerName + ".BMP";
	std::string DmgRImage = "Right" + PlayerName + "Dmged.BMP";
	std::string DmgLImage = "Left" + PlayerName + "Dmged.BMP";

	{
		AnimationRender = CreateRender(VSRenderOrder::Player);
		AnimationRender->SetScale({ 70, 140 }); // 실제 크기 64 x 64
		{
			AnimationRender->CreateAnimation({ .AnimationName = "Right_Idle",  .ImageName = RImage, .Start = 3, .End = 3 , .Loop = false }); //RightAntonio.bmp
			AnimationRender->CreateAnimation({ .AnimationName = "Right_Move",  .ImageName = RImage, .Start = 0, .End = 3, .InterTime = 0.1f });
			AnimationRender->CreateAnimation({ .AnimationName = "Right_Idle_Dmged",  .ImageName = DmgRImage, .Start = 3, .End = 3, .Loop = false });
			AnimationRender->CreateAnimation({ .AnimationName = "Right_Move_Dmged",  .ImageName = DmgRImage, .Start = 0, .End = 3, .InterTime = 0.1f});
		}
		{
			AnimationRender->CreateAnimation({ .AnimationName = "Left_Idle",  .ImageName = LImage, .Start = 3, .End = 3, .Loop = false });
			AnimationRender->CreateAnimation({ .AnimationName = "Left_Move",  .ImageName = LImage, .Start = 0, .End = 3, .InterTime = 0.1f });
			AnimationRender->CreateAnimation({ .AnimationName = "Left_Idle_Dmged",  .ImageName = DmgLImage, .Start = 3, .End = 3, .Loop = false });
			AnimationRender->CreateAnimation({ .AnimationName = "Left_Move_Dmged",  .ImageName = DmgLImage, .Start = 0, .End = 3, .InterTime = 0.1f });
		}
	}

	{
		BodyCollision = CreateCollision(VSRenderOrder::Player);
		BodyCollision->SetScale({ 64, 64 });
		BodyCollision->SetPosition({ 0, -BodyCollision->GetScale().hy()});
	}

	{
		MyWeapon.push_back(Weapon::Weapons["Whip"]);
	}
	ChangeState(PlayerState::IDLE); // 시작 시 기본 상태 설정
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

bool Player::CheckMonsterCollision()
{
	std::vector<GameEngineCollision*> Collision;


	// PlayerState가 변경될 수 있음을 인지해야한다. - 수정필요
	if (true == BodyCollision->Collision({ .TargetGroup = static_cast<int>(VSRenderOrder::Monster) }, Collision))
	{
		for (size_t i = 0; i < Collision.size(); i++)
		{
			// Monster* FindMonster = Collision[i]->GetOwner<Monster>();
			GameEngineActor* ColActor = Collision[i]->GetActor();
			Monster* ColMonsterActor = dynamic_cast<Monster*> (ColActor);
			Hp -= ColMonsterActor->GetDmg();
			//ChangeState(PlayerState::DMGED);
		//	ColActor->Death();
		}
	}
	return Collision.size() > 0;
}

void Player::Update(float _DeltaTime)
{
	if (true == Player::IsStop)
	{
		return;
	}
	InvincibleStateDelay -= _DeltaTime;
	if (InvincibleStateDelay <= 0)
	{
		BodyCollision->On();
	}

	//	// PlayerState가 변경될 수 있음을 인지해야한다. - 수정필요
	//if (true == BodyCollision->Collision({ .TargetGroup = static_cast<int>(VSRenderOrder::Monster) }, Collision))
	//{
	//	for (size_t i = 0; i < Collision.size(); i++)
	//	{
	//		// Monster* FindMonster = Collision[i]->GetOwner<Monster>();
	//		GameEngineActor* ColActor = Collision[i]->GetActor();
	//		Monster* ColMonsterActor = dynamic_cast<Monster*> (ColActor);
	//		Hp -= ColMonsterActor->GetDmg();
	//		//ChangeState(PlayerState::DMGED);
	//	//	ColActor->Death();
	//	}
	//}

	// 아이템 획득 콜리전
	//std::vector<GameEngineCollision*> Collision;
	std::vector<GameEngineCollision*> Collision;
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


	// 가지고 있는 무기 쿨타임, 위치업데이트
	for (Weapon* arm : MyWeapon) {
		arm->SetPos(GetPos());
		arm->WaitTime += _DeltaTime;
		if (arm->WaitTime > arm->GetCoolTime())
		{
			arm->WaitTime = 0;
			arm->On();
		}

	}

	if (Hp < 100)
	{
		int a = 0;
	}
	if (Hp < 20)
	{
		int a = 0;
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
//
//void Player::Render(float _DeltaTime)
//{
//	HDC BackBufferDc = GameEngineWindow::GetDoubleBufferImage()->GetImageDC();
//	float4 HpBarPos = GetPos() - (GetLevel()->GetCameraPos()) - float4{ 0,-7 };
//	float4 HpPoint = HpbarScale;
//	HpPoint.x = HpPoint.x *(static_cast<float>(Hp) / 120);
//
//	RECT RedBar = {	
//					static_cast<LONG> (HpBarPos.x - HpbarScale.hx()),
//					static_cast<LONG> (HpBarPos.y - HpbarScale.hy()),
//					static_cast<LONG> (HpBarPos.x - HpbarScale.hx() + HpPoint.x),
//					static_cast<LONG> (HpBarPos.y + HpbarScale.hy())
//				};
//
//	RECT BlackBar = {	
//						static_cast<LONG> (HpBarPos.x - HpbarScale.hx() + HpPoint.x),
//						static_cast<LONG> (HpBarPos.y - HpbarScale.hy()),
//						static_cast<LONG> (HpBarPos.x + HpbarScale.hx()),
//						static_cast<LONG> (HpBarPos.y + HpbarScale.hy())
//					};
//
//	FillRect(
//		BackBufferDc,
//		&RedBar,
//		CreateSolidBrush(RGB(255, 0, 0))
//	);
//	FillRect(
//		BackBufferDc,
//		&BlackBar,
//		CreateSolidBrush(RGB(0, 0, 0))
//	);
//
//	/*Rectangle(BackBufferDc,
//		HpBarPos.ix() - HpbarScale.hix(),
//		HpBarPos.iy() - HpbarScale.hiy(),
//		HpBarPos.ix() + HpPoint.hx(),
//		HpBarPos.iy() + HpPoint.hy());
//
//	Rectangle(BackBufferDc,
//		HpBarPos.ix() + HpPoint.hx(),
//		HpBarPos.iy() + HpPoint.hy(),
//		HpBarPos.ix() + HpbarScale.hix(),
//		HpBarPos.iy() + HpbarScale.hiy());*/
//
//}
