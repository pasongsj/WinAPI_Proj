#pragma once
#include "Weapon.h"

class WeaponWhip : public Weapon
{
public:
	// constrcuter destructer
	WeaponWhip() ;
	~WeaponWhip();

	// delete Function
	WeaponWhip(const WeaponWhip& _Other) = delete;
	WeaponWhip(WeaponWhip&& _Other) noexcept = delete;
	WeaponWhip& operator=(const WeaponWhip& _Other) = delete;
	WeaponWhip& operator=(WeaponWhip&& _Other) noexcept = delete;

protected:

	void Start() override;
	void Update(float _DeltaTime) override;

private:
	GameEngineRender* WeaponRender = nullptr;
	GameEngineCollision* WeaponCollision = nullptr;
};

