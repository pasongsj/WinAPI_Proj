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
		MsgAssert("�÷��̾ ���õ��� �ʾҽ��ϴ�.");
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

	std::string RightChar = "Right" + PlayerName;
	std::string LeftChar = "Left" + PlayerName;

	{
		AnimationRender = CreateRender(VSRenderOrder::Player);
		AnimationRender->SetScale({ 70, 140 }); // ���� ũ�� 64 x 64
		{
			AnimationRender->CreateAnimation({ .AnimationName = "Right_Idle",  .ImageName = RightChar }); //RightAntonio.bmp
			AnimationRender->CreateAnimation({ .AnimationName = "Right_Move",  .ImageName = RightChar, .Start = 0, .End = 2, .InterTime = 0.1f });
		}
		{
			AnimationRender->CreateAnimation({ .AnimationName = "Left_Idle",  .ImageName = LeftChar });
			AnimationRender->CreateAnimation({ .AnimationName = "Left_Move",  .ImageName = LeftChar, .Start = 0, .End = 2, .InterTime = 0.1f });
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
	ChangeState(PlayerState::IDLE); // ���� �� �⺻ ���� ����
	SetHp(100);
}

void Player::Movecalculation(float _DeltaTime)
{

	// collision.bmp �������� collision üũ
	GameEngineImage* ColliImage = GameEngineResources::GetInst().ImageFind("InlaidLibraryCollision.BMP");
	if (nullptr == ColliImage)
	{
		MsgAssert("�浹�� �� �̹����� �����ϴ�.");
	}


	float4 NextPos = GetPos() + MoveVec * _DeltaTime; // �̵��� ��ġ

	// ����Ȯ��� collision Image ��ġ ���߱�  <inlaid library����>
	while (NextPos.x < 0) {
		NextPos.x += ColliImage->GetImageScale().x;
	}
	NextPos.x = static_cast<float>((NextPos.ix()) % (ColliImage->GetImageScale().ix()));

	

	if (RGB(0, 0, 0) == ColliImage->GetPixelColor(NextPos, RGB(0, 0, 0))) // ���� ��ġ�� �̵����� ���Ѵٸ�
	{
		MoveVec = float4::Zero; // �̵��� zero
	}


	SetMove(MoveVec * _DeltaTime);
	GetLevel()->SetCameraMove(MoveVec * _DeltaTime);
	MoveVec = float4::Zero; // �̵� �Ϸ�� �̵����Ͱ� �ʱ�ȭ
}

void Player::Update(float _DeltaTime)
{
	// PlayerState�� ����� �� ������ �����ؾ��Ѵ�. - �����ʿ�
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

	// ������ ȹ�� �ݸ���
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


	// ������ �ִ� ���� ��Ÿ�� ������Ʈ
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
