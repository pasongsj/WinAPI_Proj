#pragma once
#include <GameEngineCore/GameEngineActor.h>
#include <map>
#include <string>
#include <GameEngineCore/GameEngineCollision.h>
#include <GameEngineCore/GameEngineRender.h>

class Weapon : public GameEngineActor
{
public:

	static void InitWeapon(GameEngineLevel* _Level);
	static std::map<std::string, Weapon*> Weapons; //모든 Weapon을 모음
	float WaitTime = 0.0f;
	
	// constrcuter destructer
	Weapon() ;
	~Weapon();

	// delete Function
	Weapon(const Weapon& _Other) = delete;
	Weapon(Weapon&& _Other) noexcept = delete;
	Weapon& operator=(const Weapon& _Other) = delete;
	Weapon& operator=(Weapon&& _Other) noexcept = delete;

	// ---- Name
	inline void SetWeaponName(const std::string_view& _Name)
	{
		WeaponName = _Name.data();
	}

	std::string GetWeaponName()
	{
		return WeaponName;
	}

	// ---- Level
	inline void LevelUp()
	{
		++WeaponLevel;
	}

	inline int GetWeaponLevel()
	{
		return WeaponLevel;
	}

	// ---- Dmg
	void SetDmg(const int* _Dmg) {
		for (int i = 1;i < 9;i++)
		{
			Dmg[i] = *(_Dmg + i);
		}
	}

	inline int GetDmg()
	{
		return Dmg[WeaponLevel];
	}

	// --- CoolTime
	inline void SetCoolTime(const float& _CoolTime)
	{
		CoolTime = _CoolTime;
	}

	inline float GetCoolTime()
	{
		return CoolTime;
	}

	// --- RunTime
	inline void SetRunTime(const float& _RunTime)
	{
		RunTime = _RunTime;
	}

	inline float GetRunTime()
	{
		return RunTime;
	}

	// --- Animation
	inline void SetAnimationOff() {
		IsAnimation = false;
	}

	inline bool GetIsAnimation()
	{
		return IsAnimation;
	}

	// --- WeaponCollisionType
	inline void SetWeaponCollisionType(CollisionType _Type)
	{
		WeaponCollisionType = _Type;
	}

	inline CollisionType GetWeaponCollisionType()
	{
		return WeaponCollisionType;
	}

	// Render
	GameEngineRender* GetWeaponRender()
	{
		return WeaponRender;
	}
	// Collision
	GameEngineCollision* GetWeaponCollision()
	{
		return WeaponCollision;
	}

protected:

	void Start() override;
	void Update(float _DeltaTime) override;

	GameEngineRender* WeaponRender = nullptr;
	GameEngineCollision* WeaponCollision = nullptr;

private:
	

	std::string WeaponName;

	int WeaponLevel = 1; // 무기 레벨 최디8

	int Dmg[9] = {0,}; // index0무시 0~8
	float CoolTime = 0.0f;
	float RunTime =  0.0f;
	bool IsAnimation = true;

	CollisionType WeaponCollisionType = CollisionType::CT_Rect;

};
