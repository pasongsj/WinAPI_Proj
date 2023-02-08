#pragma once
#include <GameEngineCore/GameEngineActor.h>

enum class MonsterState
{
	IDLE,
	Dead,
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

protected:
	void Start() override;
	void Update(float _DeltaTime) override;

private:
	float CollisionOffTime = 0.0f;
	int Hp = 0;

	GameEngineRender* AnimationRender = nullptr;
	GameEngineCollision* BodyCollision = nullptr;
};

