#pragma once
#include <GameEngineCore/GameEngineActor.h>

class Items : public GameEngineActor
{
public:
	// constrcuter destructer
	Items() ;
	~Items();

	// delete Function
	Items(const Items& _Other) = delete;
	Items(Items&& _Other) noexcept = delete;
	Items& operator=(const Items& _Other) = delete;
	Items& operator=(Items&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;

private:
	GameEngineRender* ItemRender = nullptr;
	GameEngineCollision* ItemCollision = nullptr; // æ∆¿Ã≈€ »πµÊ ªÁ∞≈∏Æ

};

