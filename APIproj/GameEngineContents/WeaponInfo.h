#pragma once
#include <string>
#include <string_view>
#include <map>
#include <GameEngineCore/GameEngineActor.h>

class WeaponInfo : public GameEngineActor
{
public:
	static std::map<std::string, WeaponInfo*> Infos;

	// constrcuter destructer
	~WeaponInfo();

	// delete Function
	WeaponInfo(const WeaponInfo& _Other) = delete;
	WeaponInfo(WeaponInfo&& _Other) noexcept = delete;
	WeaponInfo& operator=(const WeaponInfo& _Other) = delete;
	WeaponInfo& operator=(WeaponInfo&& _Other) noexcept = delete;

	void CreateWeapon(const std::string_view& _WeaponName);
	/*void SetWeaponName(const std::string_view& _WeaponName) {
		WeaponName = _WeaponName;
	}*/

protected:
	WeaponInfo() ;

private:
	int Att;
	//std::string WeaponName;
	GameEngineRender* WeaponRender;
	GameEngineCollision* WeaponCollision;
};

