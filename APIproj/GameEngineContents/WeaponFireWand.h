#pragma once
#include "Weapon.h"

class WeaponFireWand : public Weapon
{
public:
	// constrcuter destructer
	WeaponFireWand() ;
	~WeaponFireWand();

	// delete Function
	WeaponFireWand(const WeaponFireWand& _Other) = delete;
	WeaponFireWand(WeaponFireWand&& _Other) noexcept = delete;
	WeaponFireWand& operator=(const WeaponFireWand& _Other) = delete;
	WeaponFireWand& operator=(WeaponFireWand&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;
	void Init() override;
	void ReSet() override;

private:
	std::vector<GameEngineRender*> WeaponRender;
	std::vector<GameEngineCollision*> WeaponCollision;
	std::vector<float4> WeaponDir; //�̵�����
	std::vector<int> Passes; // ����
	std::vector<float> DelayTime;
	float ProjectileInterval = 0.02f;

	bool IsInScreen(float4 _Pos);

};

