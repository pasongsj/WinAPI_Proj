#pragma once
#include <GameEngineCore/GameEngineResources.h>
#include <GameEngineCore/GameEngineActor.h>
#include <vector>
#include "Weapon.h"

enum class PlayerState
{
	IDLE,
	MOVE,
	IDLE_DMGED,
	MOVE_DMGED,
};

class Active
{
public:

	float MaxHealth		= 100;	//최대체력 ㅇ
	float Recovery		= 0;		// 회복 ㅇ
	int	  Armor			= 0;			// 방어력 방어력1당 10%데미지 반격 ㅇ 
	float ActiveSpeed	= 100;	// 이동속도 % ㅇ

	float Might			= 100;		// 괴력 % ㅇ
	float Area			= 100;		// 공격범위 % ㅇ
	float Speed			= 100;		// 투사체 속도 % ㅇ
	float Duration		= 100;	// 지속시간 % ㅇ 
	int   Amount		= 0;			// 투사체 수 ㅇ
	float Cooldown		= 100;	// 쿨타임 % ㅇ

	float Luck			= 100;			// 행운 %
	float Growth		= 0;			// 성장% ㅇ
	int   Greed			= 100;		// 탐욕%  탐욕 수치를 통한 골드 획득량은 < (기본 수치 + 추가 능력치) x 스테이지 골드 보너스 >
	
	int   Magnet		= 0;		    // 자석 ㅇ

	int   Revival		= 0;		// 부활
	int   Reroll		= 0;			// 새로고침
	int   Skip			= 0;			// 건너뛰기
};

class ActiveLevel
{
public:
	int LevelBracer		 = 0;
	int LevelCandle		 = 0;
	int LevelClover		 = 0;
	int LevelEmptytome	 = 0;
	int LevelMagnet		 = 0;
	int LevelSpinach	 = 0;
	int LevelWing		 = 0;
	int LevelDuplicator	 = 0;
	int LevelPummarola	 = 0;
	int LevelSpellbinder = 0;
	int LevelCrown		 = 0;
	int LevelHollowHeart = 0;
	int LevelArmor		 = 0;
};


class Player : public GameEngineActor
{
public:
	static bool IsStop;

	static Player* MainPlayer;
	static std::string PlayerName;
	static std::string BasicWeapon;

	bool LevelUpUI = false;
	bool OpenBoxUI = false;
	// constrcuter destructer
	Player() ;
	~Player();

	// delete Function
	Player(const Player& _Other) = delete;
	Player(Player&& _Other) noexcept = delete;
	Player& operator=(const Player& _Other) = delete;
	Player& operator=(Player&& _Other) noexcept = delete;

	inline int GetPlayerLevel()
	{
		return PlayerLevel;
	}

	inline void Attack(float _Att) {
		Hp -= _Att;
	}
	inline void SetHp(float _Hp) {
		Hp = _Hp;
	}

	inline float GetHp() {
		return Hp;
	}

	inline float GetPlayerExp()
	{
		return PlayerExp;
	}

	inline std::string GetDirString() {
		return DirString;
	}

	inline float4 GetLastMoveVec()
	{
		return LastMoveVec;
	}
	inline void SetLastMoveVec(const float4& _Vec)
	{
		LastMoveVec = _Vec;
	}

	int GetMaxExp();

	void PushWeapon(const std::string_view& _Weapon);
	void PushActive(const std::string_view& _Active);

	Active GetPlayerActive()
	{
		return PlayerActive;
	}

	void CollisionOnOff()
	{
		BodyCollision->OnOffSwtich();
	}

	void GetHp(float _Hp)
	{
		if (Hp + _Hp > PlayerActive.MaxHealth)
		{
			Hp = PlayerActive.MaxHealth;
		}
		else Hp += _Hp;
	}
 
	void SetBGSize(const float4& _Size)
	{
		BGSize = _Size;
	}

	/*std::vector<std::pair<int, std::string>> GetWeapon()
	{
		std::vector<std::pair<int, std::string>> _Return;
		for (Weapon* _Weapon : MyWeapon)
		{
			_Return.push_back(make_pair(_Weapon->GetWeaponLevel(), _Weapon->GetWeaponName()));
		}

	}*/

protected:
	void Start() override;
	void Update(float _DeltaTime) override;
	void Render(float _DeltaTime) override;

private:
	float4 BGSize = float4::Zero;

	Active PlayerActive;
	ActiveLevel PlayerActiveLevel;

	//float AccTime = 0.0f;
	int StartFrame = 0;
	float MoveSpeed = 300.0f;
	float4 MoveVec = float4::Zero;
	float4 LastMoveVec = float4::Zero;

	float Hp = 100;
	float PlayerExp = 0;
	int PlayerLevel = 1;
	float DmgedAnimationDelay = 0.0f;//무적상태
	//float4 HpbarScale = { 70, 9 };

	PlayerState StateValue = PlayerState::IDLE;
	std::string DirString = "Right_";

	GameEngineRender* AnimationRender = nullptr;
	GameEngineCollision* BodyCollision = nullptr;
	std::vector<Weapon*> MyWeapon;

	GameEngineRender* HpRedBar = nullptr;
	float4 MaxHpScale = float4::Zero;

	void DirCheck(const std::string_view& _AnimationName);// 방향체크

	// State
	void ChangeState(PlayerState _State); // Idle, Move 상태전환
	void UpdateState(float _Time);

	// FSM 내가 어떤일을 할때 이동하면서 가만히 있을수 없다.
	void IdleStart();
	void IdleUpdate(float _Time);
	void IdleEnd();

	void MoveStart();
	void MoveUpdate(float _Time);
	void MoveEnd();

	void IdleDmgedStart();
	void IdleDmgedUpdate(float _Time);
	void IdleDmgedEnd();

	void MoveDmgedStart();
	void MoveDmgedUpdate(float _Time);
	void MoveDmgedEnd();

	// 함수분리
	void PressMove();
	bool CheckMonsterCollision();
	void Movecalculation(float _DeltaTime);


	void WeaponUpdate(float _DeltaTime);
	void CheckLevelUp();
	
	void UpdateActiveItem(float _DeltaTime);

	void CheckObtainItems();

	//GameEngineSoundPlayer ExpGemPlayer = GameEngineResources::GetInst().SoundPlayToControl("GetGem.mp3");
};

