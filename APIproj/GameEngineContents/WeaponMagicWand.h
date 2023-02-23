#pragma once
#include "Weapon.h"

class WeaponMagicWand : public Weapon
{
public:
	// constrcuter destructer
	WeaponMagicWand() ;
	~WeaponMagicWand();

	// delete Function
	WeaponMagicWand(const WeaponMagicWand& _Other) = delete;
	WeaponMagicWand(WeaponMagicWand&& _Other) noexcept = delete;
	WeaponMagicWand& operator=(const WeaponMagicWand& _Other) = delete;
	WeaponMagicWand& operator=(WeaponMagicWand&& _Other) noexcept = delete;

	void ReSet() override;

protected:

	void Start() override;
	void Update(float _DeltaTime) override;

private:
	std::vector<GameEngineRender*> WeaponRender;
	std::vector<GameEngineCollision*> WeaponCollision;
	std::vector<float4> WeaponDir;
	std::vector<int> Passes;

	//GameEngineRender* WeaponRender = nullptr;
	//GameEngineCollision* WeaponCollision = nullptr;
	//float4 WepaonDir = float4::Zero;
	//int Passes = 1;//����ü ����

	void SetWeaponDir();
};