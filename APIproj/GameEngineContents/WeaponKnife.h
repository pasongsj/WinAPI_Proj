#pragma once
#include "Weapon.h"


class WeaponKnife : public Weapon
{
	//friend class Player;
public:
	// constrcuter destructer
	WeaponKnife() ;
	~WeaponKnife();

	// delete Function
	WeaponKnife(const WeaponKnife& _Other) = delete;
	WeaponKnife(WeaponKnife&& _Other) noexcept = delete;
	WeaponKnife& operator=(const WeaponKnife& _Other) = delete;
	WeaponKnife& operator=(WeaponKnife&& _Other) noexcept = delete;


protected:
	void Start() override;
	void Update(float _DeltaTime) override;
	void Init() override;
	void ReSet() override;

private:

	std::vector<GameEngineRender*> WeaponRender;
	std::vector<GameEngineCollision*> WeaponCollision;
	std::vector<float4> WeaponDir; //이동방향
	std::vector<int> Passes; // 관통

};

