#pragma once
#include "Weapon.h"

class WeaponRuneTracer : public Weapon
{
	//friend class Player;
public:
	// constrcuter destructer
	WeaponRuneTracer() ;
	~WeaponRuneTracer();

	// delete Function
	WeaponRuneTracer(const WeaponRuneTracer& _Other) = delete;
	WeaponRuneTracer(WeaponRuneTracer&& _Other) noexcept = delete;
	WeaponRuneTracer& operator=(const WeaponRuneTracer& _Other) = delete;
	WeaponRuneTracer& operator=(WeaponRuneTracer&& _Other) noexcept = delete;


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
	std::vector<float> LuneLiveTime; // 룬트레이서 지속시간

	//void SetWeaponDir();

	float4 CheckNextPos(const float4& _Pos, const float4& _Dir);

};

