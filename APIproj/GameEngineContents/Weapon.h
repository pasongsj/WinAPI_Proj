#pragma once
#include <GameEngineCore/GameEngineActor.h>
#include <map>
#include <string>
#include <GameEngineCore/GameEngineCollision.h>

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

	void SetRenderOrder(int _Value);

	void SetRenderScale(float4 _Scale);

	/*inline GameEngineRender* GetWeaponRender() {
		return WeaponRender;
	}

	inline void SetWeaponRender(GameEngineRender* _Render) {
		WeaponRender = _Render;
	}*/

	void SetAnimationOff() {
		IsAnimation = false;
	}

	// Collision
	void SetCollisionScale(float4 _Scale);

	/*inline GameEngineCollision* GetWeaponCollision() {
		return WeaponCollision;
	}

	inline void SetWeaponCollision(GameEngineCollision* _Collision) {
		WeaponCollision = _Collision;
	}*/

	//

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
	
	void SetWeaponDebugType(CollisionType _Type);


protected:

	void Start() override;
	void Update(float _DeltaTime) override;
private:
	GameEngineRender* WeaponRender = nullptr;
	GameEngineCollision* WeaponCollision = nullptr;
	int Dmg = 0;
	float CoolTime = 0.0f;
	bool IsAnimation = true;
	float4 WeaponPos;

};
