#include "Weapon.h"
#include "ContentsEnums.h"
#include <GameEngineCore/GameEngineLevel.h>
#include <utility>

#include "Player.h"


std::map<std::string, Weapon*> Weapon::Weapons;

Weapon::Weapon()
{
}

Weapon::~Weapon()
{
}
void Weapon::InitWeapon(GameEngineLevel* _Level)
{

}



void Weapon::Start()
{
}

void Weapon::Update(float _DeltaTime)
{
}



float Weapon::GetDmg()
{
	float MightPerc = (Player::MainPlayer->GetPlayerActive().Might / 100.0f);
	return (Dmg[WeaponLevel] * MightPerc);
}

float Weapon::GetWeaponSpeed()
{
	float SpeedPerc = (Player::MainPlayer->GetPlayerActive().Speed / 100.0f);
	return (WeaponSpeed * SpeedPerc);
}

float4 Weapon::GetWeaponRenderScale()
{
	float ScalePerc = (Player::MainPlayer->GetPlayerActive().Area / 100.0f);
	return (WeaponRenderScale * ScalePerc);
}

float4 Weapon::GetWeaponCollisionScale()
{
	float ScalePerc = (Player::MainPlayer->GetPlayerActive().Area / 100.0f);
	return (WeaponCollisionScale * ScalePerc);
}


int Weapon::GetWeaponPass()
{
	int AddPass = (Player::MainPlayer->GetPlayerActive().Amount);
	return WeaponPass + AddPass;
}


float Weapon::GetCoolTime()
{
	float CoolDownPer = (Player::MainPlayer->GetPlayerActive().Cooldown / 100.0f);
	return CoolTime * CoolDownPer;
}


float Weapon::GetRunTime()
{
	float DurationPer = (Player::MainPlayer->GetPlayerActive().Duration / 100.0f);
	return RunTime * DurationPer;
}