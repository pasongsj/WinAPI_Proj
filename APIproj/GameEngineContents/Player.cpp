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


Player* Player::MainPlayer;
std::string Player::PlayerName = "";
bool Player::IsStop = false;

Player::Player()
{
}

Player::~Player()
{
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
	MoveVec = float4::Zero; // �̵� �Ϸ��� �̵����Ͱ� �ʱ�ȭ
}

bool Player::CheckMonsterCollision()
{
	std::vector<GameEngineCollision*> Collision;


	// PlayerState�� ����� �� ������ �����ؾ��Ѵ�. - �����ʿ�
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
	if (0 == _DeltaTime) // ���� or ������ --> ���⼱�� ����
	{
		return;
	}

	InvincibleStateDelay -= _DeltaTime; // �ǰݽ� ����Ÿ��
	if (InvincibleStateDelay <= 0)
	{
		BodyCollision->On();
	}

	// ������ ȹ�� �ݸ���
	std::vector<GameEngineCollision*> Collision;
	Collision.clear();
	if (true == BodyCollision->Collision({ .TargetGroup = static_cast<int>(VSRenderOrder::Item) , .TargetColType  = CollisionType::CT_Rect}, Collision))
	{
		for (size_t i = 0; i < Collision.size(); i++)
		{
			GameEngineActor* ColActor = Collision[i]->GetActor();
			Items* ColItemActor = dynamic_cast<Items*> (ColActor);
			PlayerExp += ColItemActor->GetExp();
			ColItemActor->Death();
			//	ColActor->Death();

		}
	}

	if (Hp <= 0) // GameOver -- > Level���� üũ�ϵ��� ���� �ʿ�
	{
		int a = 0;
	}


	WeaponUpdate(_DeltaTime); // Weapon�� on/off�� �����ߴµ� ��ü������ ������ ��ȯ�ϱ� ������ ������ �ʿ䰡 ���� -> �����ϵ� ��ü�� �����ϱ�
	UpdateState(_DeltaTime);
	Movecalculation(_DeltaTime);
	CheckLevelUp();
}

void Player::WeaponUpdate(float _DeltaTime)
{
	for (Weapon* arm : MyWeapon) {
		arm->WaitTime += _DeltaTime;
		if (arm->WaitTime > arm->GetCoolTime())
		{
			arm->ReSet();
		}

	}
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
	// -- �ӽ� Level�� Debug�� �� ����
	/*float4 ForCheck = AnimationRender->GetPosition();
	float4 _Pos = GetPos();
	std::string MouseText = "Position : ";
	MouseText += _Pos.ToString();
	GameEngineLevel::DebugTextPush(MouseText);

	std::string CameraText = "CameraPosition : ";
	CameraText += GetLevel()->GetCameraPos().ToString();
	GameEngineLevel::DebugTextPush(CameraText);*/


	////float4 _Pos = Player::MainPlayer->GetPos();
	HDC DoubleDC = GameEngineWindow::GetDoubleBufferImage()->GetImageDC();

	float4 HpBarPos = GetPos() - (GetLevel()->GetCameraPos()) - float4{ 0,-7 };
	float4 HpPoint = HpbarScale;
	HpPoint.x = HpPoint.x *(static_cast<float>(Hp) / 120);


	// -- RedBar
	HBRUSH myBrush = (HBRUSH)CreateSolidBrush(RGB(255, 0, 0));
	HBRUSH oldBrush = (HBRUSH)SelectObject(DoubleDC, myBrush);

	Rectangle(DoubleDC,
		(HpBarPos.ix() - HpbarScale.hix()),
		(HpBarPos.iy() - HpbarScale.hiy()),
		(HpBarPos.ix() - HpbarScale.hix() + HpPoint.ix()),
		(HpBarPos.iy() + HpbarScale.hiy())
	);

	SelectObject(DoubleDC, oldBrush);
	DeleteObject(myBrush);

	// -- BlackBar
	myBrush = (HBRUSH)CreateSolidBrush(RGB(0, 0, 0));

	oldBrush = (HBRUSH)SelectObject(DoubleDC, myBrush);

	Rectangle(DoubleDC,
		(HpBarPos.ix() - HpbarScale.hix() + HpPoint.ix()),
		(HpBarPos.iy() - HpbarScale.hiy()),
		(HpBarPos.ix() + HpbarScale.hix()),
		(HpBarPos.iy() + HpbarScale.hiy())
	);

	SelectObject(DoubleDC, oldBrush);
	DeleteObject(myBrush);

	// - �� ����? ��? ��? ��????
	/*RECT RedBar = {	
					static_cast<LONG> (HpBarPos.x - HpbarScale.hx()),
					static_cast<LONG> (HpBarPos.y - HpbarScale.hy()),
					static_cast<LONG> (HpBarPos.x - HpbarScale.hx() + HpPoint.x),
					static_cast<LONG> (HpBarPos.y + HpbarScale.hy())
				};*/

	//RECT BlackBar = {	
	//					static_cast<LONG> (HpBarPos.x - HpbarScale.hx() + HpPoint.x),
	//					static_cast<LONG> (HpBarPos.y - HpbarScale.hy()),
	//					static_cast<LONG> (HpBarPos.x + HpbarScale.hx()),
	//					static_cast<LONG> (HpBarPos.y + HpbarScale.hy())
	//				};

	/*FillRect(
		DoubleDC,
		&RedBar,
		CreateSolidBrush(RGB(255, 0, 0))
	);*/
	//FillRect(
	//	BackBufferDc,
	//	&BlackBar,
	//	CreateSolidBrush(RGB(0, 0, 0))
	//);

}


void Player::PressMove() // �Է°���
{
	if (
		false == GameEngineInput::IsPress("LeftMove") &&
		false == GameEngineInput::IsPress("RightMove") &&
		false == GameEngineInput::IsPress("DownMove") &&
		false == GameEngineInput::IsPress("UpMove")
		)
	{
		// 
		ChangeState(PlayerState::IDLE);
		return;
	}

	MoveVec = float4::Zero;
	//float4 MoveRange = float4::Zero;

	if (true == GameEngineInput::IsPress("LeftMove"))
	{
		MoveVec += float4::Left;
	}

	if (true == GameEngineInput::IsPress("RightMove"))
	{
		MoveVec += float4::Right;
	}

	if (true == GameEngineInput::IsPress("UpMove"))
	{
		MoveVec += float4::Up;
	}

	if (true == GameEngineInput::IsPress("DownMove"))
	{
		MoveVec += float4::Down;
	}
	MoveVec.Normalize();
	MoveVec *= MoveSpeed;
}

void Player::CheckLevelUp()//������ üũ
{
	int NextLevel = PlayerLevel;
	int ReqExpPoint = 3192;// 200��������Ʈ


	if (20 > NextLevel)
	{
		ReqExpPoint = (NextLevel * 10) - 5;
	}
	else if (20 == NextLevel)
	{
		ReqExpPoint = (NextLevel * 10) - 5 + 600;
	}
	else if (20 < NextLevel && 40 > NextLevel)
	{
		ReqExpPoint = (NextLevel * 13) - 6;
	}
	else if (40 == NextLevel)
	{
		ReqExpPoint = (NextLevel * 13) - 6 + 2400;
	}
	else if (40 < NextLevel)
	{
		ReqExpPoint = (NextLevel * 16) - 8;
	}

	if (PlayerExp >= ReqExpPoint)
	{
		++PlayerLevel;
		PlayerExp -= ReqExpPoint;
		IsStop = true; // �������� ���� stop --> �����ۼ���â ����
	}
}