#pragma once
#include <GameEngineCore/GameEngineActor.h>
#include <map>
#include <string>


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
	
	/*void SetPos(const float4& _Pos) {
		Pos = _Pos;
		WeaponRender->SetPosition(Pos);
		WeaponCollision->SetPosition(Pos);
	}*/

	inline float4 GetPos() {
		return Pos;
	}

	//Render
	void SetImage(const std::string_view& _AnimationName = "", const std::string_view& _Image = "", int _Start = 0, int _End = 0, float _InterTim = 0.0f);

	void SetRenderOrder(int _Value);

	void SetRenderScale(float4 _Scale);

	inline GameEngineRender* GetWeaponRender() {
		return WeaponRender;
	}

	inline void SetWeaponRender(GameEngineRender* _Render) {
		WeaponRender = _Render;
	}

	void SetAnimationOff() {
		IsAnimation = false;
	}

	// Collision
	void SetCollisionScale(float4 _Scale);

	inline GameEngineCollision* GetWeaponCollision() {
		return WeaponCollision;
	}

	inline void SetWeaponCollision(GameEngineCollision* _Collision) {
		WeaponCollision = _Collision;
	}

	//

	inline void SetDmg(int _Dmg) {
		Dmg = _Dmg;
	}
	inline int GetDmg() {
		return Dmg;
	}
	


protected:

	void Start() override;
	void Update(float _DeltaTime) override;
private:
	GameEngineRender* WeaponRender = nullptr;
	GameEngineCollision* WeaponCollision = nullptr;
	int Dmg = 0;
	float CoolTime = 0.0f;
	bool IsAnimation = true;
	float4 Pos;

};
