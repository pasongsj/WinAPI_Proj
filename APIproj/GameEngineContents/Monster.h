#pragma once
#include <GameEngineCore/GameEngineActor.h>
#include <GameEngineCore/GameEngineResources.h>
#include <queue>

enum class MonsterState
{
	MOVE,
	BEATEN,
	DEAD,
};

class Monster : public GameEngineActor
{
public:
	
	static std::vector<Monster*> DeadMonsters;
	static std::string MonsterName;
	// constrcuter destructer
	Monster() ;
	~Monster();

	// delete Function
	Monster(const Monster& _Other) = delete;
	Monster(Monster&& _Other) noexcept = delete;
	Monster& operator=(const Monster& _Other) = delete;
	Monster& operator=(Monster&& _Other) noexcept = delete;

	void Attack(float _Att, float _KnockBack = 0.0f);

	void KnockBackLessAttack(float _Att,float _StateDelay = 0.2f);


	inline void SetHp(float _Hp) {
		Hp = _Hp;
	}

	float GetHp() {
		return Hp;
	}

	inline void SetDmg(float _Dmg) {
		Dmg = _Dmg;
	}
	inline float GetDmg()
	{
		return Dmg;
	}

	inline void SetInvincibleStateDelay(const float& _Time)
	{
		InvincibleStateDelay = _Time;
	}

	void Reset();

	void SetBoxBossOn()
	{
		IsBoxBoss = true;
	}

protected:
	void Start() override;
	void Update(float _DeltaTime) override;

private:

	std::string Name = "";

	bool IsBoxBoss = false; // 박스를 return하는 보스

	float InvincibleStateDelay = 0.0f;//무적상태

	bool IsAttacked = false;
	float KnockBack = 0.0f;
	//float CollisionOffTime = 0.0f;

	float Hp = 0.0f;
	float Dmg = 0.0f;
	float MoveSpeed = 100.0f;

	float Exp = 0.0f;
	
	float4 MonsterRenderScale = float4{ 70, 140 };
	float4 MonsterCollisionScale = float4{ 40, 50 };

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

	void Setting();
	//int* EndFrame = nullptr;
	int EndFrame[3] = { 0,0,0 };

	float4 GetReGenPos();

	void MonsterMoveCheck(float _DeltaTime);
};

