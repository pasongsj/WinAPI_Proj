#pragma once
#include <GameEngineCore/GameEngineActor.h>

class Player : public GameEngineActor
{
public:
	// constrcuter destructer
	Player() ;
	~Player();

	// delete Function
	Player(const Player& _Other) = delete;
	Player(Player&& _Other) noexcept = delete;
	Player& operator=(const Player& _Other) = delete;
	Player& operator=(Player&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;
	void Render(float _DeltaTime) override;
private:
	float AccTime = 0.0f;
	int StartFrame = 0;
};

