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

protected:
	void Start() override;
	void Update(float _DeltaTime) override;

private:
	GameEngineRender* AnimationRender = nullptr;
	GameEngineCollision* BodyCollision = nullptr;
};

