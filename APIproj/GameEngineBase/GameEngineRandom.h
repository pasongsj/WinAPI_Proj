#pragma once
#include <random>

// 설명 :	메르센 트위스터 알고리즘을 사용하여 최댓값과 최솟값을 통해 난수를 만들 수 있도록 하였다. 여기서 사용한 seed값은 현재 시각적용하였다.
class GameEngineRandom
{

public:
	static GameEngineRandom MainRandom;

	// constrcuter destructer
	GameEngineRandom();
	~GameEngineRandom();

	// delete Function
	GameEngineRandom(const GameEngineRandom& _Other) = delete;
	GameEngineRandom(GameEngineRandom&& _Other) noexcept = delete;
	GameEngineRandom& operator=(const GameEngineRandom& _Other) = delete;
	GameEngineRandom& operator=(GameEngineRandom&& _Other) noexcept = delete;

	int RandomInt(int _Min, int _Max)
	{
		// 이게 Creater
		std::uniform_int_distribution<int> Uniform(_Min, _Max);
		return Uniform(MtGen);
	}

	float RandomFloat(float _Min, float _Max)
	{
		std::uniform_real_distribution <float> Uniform(_Min, _Max);
		return Uniform(MtGen);
	}

	void SetSeed(__int64 _Seed)
	{
		MtGen = std::mt19937_64(_Seed);
	}

protected:


private:
	// 메르센 트위스터 알고리즘을 사용한 제네러이터
	std::mt19937_64 MtGen = std::mt19937_64();
	// 랜덤 크리에이터 클래스 => 1개
};

