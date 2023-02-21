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

	inline float4 GetWeaponPos() {
		return WeaponPos;
	}
	inline void SetWeaponPos(const float4& _WeaponPos) {
		WeaponPos = _WeaponPos;
	}

	//Render
	void SetImage(const std::string_view& _AnimationName = "", const std::string_view& _Image = "", int _Start = 0, int _End = 0, float _InterTim = 0.0f);

	inline void SetRenderOrder(int _Value)
	{
		WeaponRender->SetOrder(_Value);
	}

	inline void SetRenderScale(float4 _Scale)
	{
		WeaponRender->SetScale(_Scale);
	}

	inline void SetAnimationOff() {
		IsAnimation = false;
	}

	// Collision
	inline void SetCollisionScale(float4 _Scale)
	{
		WeaponCollision->SetScale(_Scale);
	}

	void SetDmg(const int* _Dmg) {
		for (int i = 1;i < 9;i++)
		{
			Dmg[i] = *(_Dmg + i);
		}
		//Dmg = _Dmg;
	}

	inline int GetDmg() 
	{
		return Dmg[WeaponLevel];
	}
	
	inline void SetCoolTime(const float& _CoolTime) 
	{
		CoolTime = _CoolTime;
	}

	inline float GetCoolTime()
	{
		return CoolTime;
	}
	
	inline void SetRunTime(const float& _RunTime) 
	{
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


	inline void SetCollisionPosition(const float4& _Pos) {
		WeaponCollision->SetPosition(_Pos);
	}

	inline void SetRenderPosition(const float4& _Pos) {
		WeaponRender->SetPosition(_Pos);
	}

	inline CollisionType GetWeaponCollisionType()
	{
		return WeaponCollisionType;
	}

	GameEngineRender* GetWeaponRender() {
		return WeaponRender;
	}

	GameEngineCollision* GetWeaponCollision() {
		return WeaponCollision;
	}

	void SetWeaponName(const std::string_view& _Name)
	{
		WeaponName = _Name.data();
	}

	std::string GetWeaponName() {
		return WeaponName;
	}
protected:

	void Start() override;
	void Update(float _DeltaTime) override;

private:
	std::string WeaponName;
	int WeaponLevel = 1; // 무기 레벨 최디8
	int Dmg[9] = {0,}; // index0무시 0~8
	float CoolTime = 0.0f;
	float RunTime =  0.0f;
	bool IsAnimation = true;

	float4 WeaponPos;

	GameEngineRender* WeaponRender = nullptr;
	GameEngineCollision* WeaponCollision = nullptr;
	CollisionType WeaponCollisionType = CollisionType::CT_Rect;
};
