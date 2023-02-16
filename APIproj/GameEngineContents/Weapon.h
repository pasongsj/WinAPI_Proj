#pragma once
#include <GameEngineCore/GameEngineActor.h>
#include <map>
#include <string>
#include <GameEngineCore/GameEngineCollision.h>
#include <GameEngineCore/GameEngineRender.h>

class Weapon : public GameEngineActor
{
public:

	static std::map<std::string, Weapon*> Weapons;
	// constrcuter destructer
	Weapon() ;
	~Weapon();

	// delete Function
	Weapon(const Weapon& _Other) = delete;
	Weapon(Weapon&& _Other) noexcept = delete;
	Weapon& operator=(const Weapon& _Other) = delete;
	Weapon& operator=(Weapon&& _Other) noexcept = delete;

	inline float4 GetWeaponPos() {
		return WeaponPos;
	}
	inline void SetWeaponPos(const float4& _WeaponPos) {
		WeaponPos = _WeaponPos;
	}

	//Render
	void SetImage(const std::string_view& _AnimationName = "", const std::string_view& _Image = "", int _Start = 0, int _End = 0, float _InterTim = 0.0f);

	void SetRenderOrder(int _Value)
	{
		WeaponRender->SetOrder(_Value);
	}

	void SetRenderScale(float4 _Scale)
	{
		WeaponRender->SetScale(_Scale);
	}


	void SetAnimationOff() {
		IsAnimation = false;
	}

	// Collision
	void SetCollisionScale(float4 _Scale)
	{
		WeaponCollision->SetScale(_Scale);
	}


	inline void SetDmg(const int& _Dmg) {
		Dmg = _Dmg;
	}
	inline int GetDmg() {
		return Dmg;
	}

	inline void SetCoolTime(const float& _CoolTime) {
		CoolTime = _CoolTime;
	}
	inline float GetCoolTime()
	{
		return CoolTime;
	}
	
	inline void SetRunTime(const float& _RunTime) {
		RunTime = _RunTime;
	}
	inline float GetRunTime()
	{
		return RunTime;
	}

	/*void SetWeaponDebugType(CollisionType _Type)
	{
		WeaponCollision->SetDebugRenderType(_Type);
	}*/

	float WaitTime = 0.0f;

	void SetCollisionPosition(const float4& _Pos) {
		WeaponCollision->SetPosition(_Pos);
	}

	void SetRenderPosition(const float4& _Pos) {
		WeaponRender->SetPosition(_Pos);
	}
protected:

	void Start() override;
	void Update(float _DeltaTime) override;
private:
	GameEngineRender* WeaponRender = nullptr;
	GameEngineCollision* WeaponCollision = nullptr;
	int Dmg = 0;
	float CoolTime = 0.0f;
	float RunTime = 0.0f;
	bool IsAnimation = true;
	float4 WeaponPos;

};
