#pragma once
#include "Weapon.h"

class WeaponWhip : public Weapon
{
	//friend class Player;
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
	void Init() override;
	void ReSet() override;
	void LevelUp() override;

private:
	std::string LastDir = "Right_";
	std::map<std::string,GameEngineRender*> WeaponRender;
	std::map<std::string, GameEngineCollision*> WeaponCollision;
	/*GameEngineRender* WeaponRender = nullptr;
	GameEngineCollision* WeaponCollision = nullptr;*/
};

