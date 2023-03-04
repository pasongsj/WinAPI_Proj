#pragma once
#include "Weapon.h"

class WeaponKingBible : public Weapon
{
public:
	// constrcuter destructer
	WeaponKingBible() ;
	~WeaponKingBible();

	// delete Function
	WeaponKingBible(const WeaponKingBible& _Other) = delete;
	WeaponKingBible(WeaponKingBible&& _Other) noexcept = delete;
	WeaponKingBible& operator=(const WeaponKingBible& _Other) = delete;
	WeaponKingBible& operator=(WeaponKingBible&& _Other) noexcept = delete;

protected:

	void Start() override;
	void Update(float _DeltaTime) override;
	void Init() override;
	void ReSet() override;
	void LevelUp() override;

private:
	std::vector<GameEngineRender*> WeaponRender;
	std::vector<GameEngineCollision*> WeaponCollision;
	std::vector<float4> WeaponPos;

	float4 StandardPos = { 0,-32 };
	float WeaponRange = 64;
};

