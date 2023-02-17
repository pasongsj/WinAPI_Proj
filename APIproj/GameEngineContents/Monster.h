#pragma once
#include <GameEngineCore/GameEngineActor.h>

enum class MonsterState
{
	MOVE,
	BEATEN,
	DEAD,
};

class Monster : public GameEngineActor
{
public:
	// constrcuter destructer
	Monster() ;
	~Monster();

	// delete Function
	Monster(const Monster& _Other) = delete;
	Monster(Monster&& _Other) noexcept = delete;
	Monster& operator=(const Monster& _Other) = delete;
	Monster& operator=(Monster&& _Other) noexcept = delete;

	inline void Attack(int _Att) {
		Hp -= _Att;
	}
	inline void SetHp(int _Hp) {
		Hp = _Hp;
	}

	int GetHp() {
		return Hp;
	}

	inline void SetDmg(int _Dmg) {
		Dmg = _Dmg;
	}
	inline int GetDmg()
	{
		return Dmg;
	}

protected:
	void Start() override;
	void Update(float _DeltaTime) override;

private:
	float CollisionOffTime = 0.0f;
	int Hp = 0;
	int Dmg = 0;
	float MoveSpeed = 200.0f;
	float4 MoveVec = float4::Zero;

	GameEngineRender* AnimationRender = nullptr;
	GameEngineCollision* BodyCollision = nullptr;

	MonsterState StateValue = MonsterState::MOVE;
	std::string DirString = "Right_";

	void DirCheck(const std::string_view& _AnimationName);// 방향체크

	void ChangeState(MonsterState _State); // Idle, Move 상태전환
	void UpdateState(float _Time);

	void MoveStart();
	void MoveUpdate(float _Time);
	void MoveEnd();

	void BeatenStart();
	void BeatenUpdate(float _Time);
	void BeatenEnd();

	void DeadStart();
	void DeadUpdate(float _Time);
	void DeadEnd();
};

