#pragma once
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


class Player : public GameEngineActor
{
public:
	static bool IsStop;
	static Player* MainPlayer;
	static std::string PlayerName;
	// constrcuter destructer
	Player() ;
	~Player();

	// delete Function
	Player(const Player& _Other) = delete;
	Player(Player&& _Other) noexcept = delete;
	Player& operator=(const Player& _Other) = delete;
	Player& operator=(Player&& _Other) noexcept = delete;

	inline void Attack(float _Att) {
		Hp -= _Att;
	}
	inline void SetHp(float _Hp) {
		Hp = _Hp;
	}

	inline float GetHp() {
		return Hp;
	}

	inline int GetPlayerExp()
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

protected:
	void Start() override;
	void Update(float _DeltaTime) override;
	void Render(float _DeltaTime) override;

private:
	//float AccTime = 0.0f;
	int StartFrame = 0;
	float MoveSpeed = 500.0f;
	float4 MoveVec = float4::Zero;
	float4 LastMoveVec = float4::Zero;

	float Hp = 100;
	int PlayerExp = 0;
	int PlayerLevel = 1;
	float InvincibleStateDelay = 0.0f;//무적상태
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
};

