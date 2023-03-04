#pragma once
#include "Weapon.h"

class WeaponMagicWand : public Weapon
{
	//friend class Player;
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
	void Init() override;
	void ReSet() override;
	void LevelUp() override;

private:
	std::vector<GameEngineRender*> WeaponRender;
	std::vector<GameEngineCollision*> WeaponCollision;
	std::vector<float4> WeaponDir; //이동방향
	std::vector<int> Passes; // 관통
	std::vector<float> DelayTime;

	float ProjectileInterval = 0.05f; // 0.1f

	std::vector<float4> GetWeaponDir(const float4& _Pos);
	//void SetWeaponDir();
	bool IsInScreen(float4 _Pos);
};