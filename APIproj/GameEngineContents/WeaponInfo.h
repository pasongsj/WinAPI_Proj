#pragma once
#include <string>
#include <string_view>
#include <map>
#include <GameEngineCore/GameEngineActor.h>

class WeaponInfo : public GameEngineActor
{
public:
	static std::map<std::string, WeaponInfo*> Infos;
	static void CreateWeapon(const std::string_view& _WeaponName);

	// constrcuter destructer
	~WeaponInfo();

	// delete Function
	WeaponInfo(const WeaponInfo& _Other) = delete;
	WeaponInfo(WeaponInfo&& _Other) noexcept = delete;
	WeaponInfo& operator=(const WeaponInfo& _Other) = delete;
	WeaponInfo& operator=(WeaponInfo&& _Other) noexcept = delete;

	/*void SetWeaponName(const std::string_view& _WeaponName) {
		WeaponName = _WeaponName;
	}*/

	inline void SetDmg(int _Dmg)
	{
		Dmg = _Dmg;

	}

	inline int GetDmg() 
	{
		return Dmg;
	}

	inline void SetCoolTimeg(float _CoolTime)
	{
		CoolTime = _CoolTime;

	}

	inline float GetCoolTime()
	{
		return CoolTime;
	}


	void SetImage(std::string_view& _Image);

	GameEngineRender* GetWeaponRender()
	{
		return WeaponRender;
	}

	GameEngineCollision* GetWeaponCollision()
	{
		return WeaponCollision;
	}

	void SetScale(const float4& _Scale);

protected:
	void Start() override;
	void Update(float _DeltaTime) override;

private:
	WeaponInfo();

	int Dmg = 10;
	float CoolTime = 0.1f;
	float4 Scale;
	//std::string WeaponName;
	GameEngineRender* WeaponRender = nullptr;
	GameEngineCollision* WeaponCollision = nullptr;
};

