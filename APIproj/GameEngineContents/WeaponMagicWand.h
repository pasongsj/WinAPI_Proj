#pragma once
class WeaponMagicWand
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

private:

};

