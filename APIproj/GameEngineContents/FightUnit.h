#pragma once
#include <GameEngineCore/GameEngineActor.h>

class FightUnit : public GameEngineActor
{
public:
	// constrcuter destructer
	FightUnit() ;
	~FightUnit();

	// delete Function
	FightUnit(const FightUnit& _Other) = delete;
	FightUnit(FightUnit&& _Other) noexcept = delete;
	FightUnit& operator=(const FightUnit& _Other) = delete;
	FightUnit& operator=(FightUnit&& _Other) noexcept = delete;

	inline void Attack(int _Att) {
		Hp -= _Att;
	}
	inline void SetHp(int _Hp) {
		Hp = _Hp;
	}

	int GetHp() {
		return Hp;
	}

protected:


private:
	int Hp = 0;

};

