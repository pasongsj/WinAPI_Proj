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

protected:

	void Start() override;
	void Update(float _DeltaTime) override;

private:

};
