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
std::string Player::PlayerName = "Antonio";
std::string Player::BasicWeapon = "Whip";
bool Player::IsStop = false;

Player::Player()
{
}

Player::~Player()
{
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
	MoveVec = float4::Zero; // 이동 완료후 이동벡터값 초기화
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
	if (0 == _DeltaTime) // 상자 or 레벨업 --> 무기선택 띄우기
	{
		return;
	}

	InvincibleStateDelay -= _DeltaTime; // 피격시 무적타임
	if (InvincibleStateDelay <= 0)
	{
		BodyCollision->On();
	}


	{ // HP바 랜더
		float4 HpScale = MaxHpScale;
		HpScale.x = HpScale.x * (Hp / 120);
		HpRedBar->SetScale(HpScale);
		HpRedBar->SetPosition({ HpScale.hx() - MaxHpScale.hx()-1, MaxHpScale.y}); // -1 pixel 보정
	}

	// 아이템 획득 콜리전
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

	if (Hp <= 0) // GameOver -- > Level에서 체크하도록 변경 필요
	{
		int a = 0;
	}


	WeaponUpdate(_DeltaTime); // Weapon의 on/off로 관리했는데 자체적으로 렌더를 교환하기 때문에 변경할 필요가 있음 -> 매직완드 교체후 삭제하기
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
	// -- 임시 Level에 Debug할 때 띄우기
	float4 ForCheck = AnimationRender->GetPosition();
	float4 _Pos = GetPos();
	std::string MouseText = "Position : ";
	MouseText += _Pos.ToString();
	GameEngineLevel::DebugTextPush(MouseText);

	std::string CameraText = "CameraPosition : ";
	CameraText += GetLevel()->GetCameraPos().ToString();
	GameEngineLevel::DebugTextPush(CameraText);



}


void Player::PressMove() // 입력관리
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
	if (float4::Zero != MoveVec)
	{
		LastMoveVec = MoveVec;
	}
	MoveVec *= MoveSpeed;
}

void Player::CheckLevelUp()//레벨업 체크
{
	int ReqExpPoint = GetMaxExp();
	if (PlayerExp >= ReqExpPoint)
	{
		++PlayerLevel;
		PlayerExp -= ReqExpPoint;
		IsStop = true; // 레벨업에 의한 stop --> 아이템선택창 띄우기
	}
}

int Player::GetMaxExp() {

	int NextLevel = PlayerLevel;
	int ReqExpPoint = 3192;// 200레벨포인트


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
	return ReqExpPoint;

}


void Player::PushWeapon(const std::string_view& _Weapon)
{
	std::string WeaponName = _Weapon.data();
	if (Weapon::Weapons.end() == Weapon::Weapons.find(WeaponName))
	{
		MsgAssert(WeaponName+"은 생성되지 않은 무기입니다.");
		return;
	}
	Weapon* _WeaponPointer = Weapon::Weapons[WeaponName];
	std::vector<Weapon*>::iterator it = find(MyWeapon.begin(), MyWeapon.end(), _WeaponPointer);
	if (it == MyWeapon.end()) // 새로 추가하기
	{
		MyWeapon.push_back(_WeaponPointer);
	}
	else // 레벨업 하기
	{

	}
}