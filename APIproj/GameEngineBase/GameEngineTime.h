#pragma once
#include <chrono>
#include <Windows.h>

// 시간을 재거나 하는 기능들을 담당.
// 기본적으로 시간을 재는 방법은 여러가지가 있지만
// 시간을 재는 기능은 기본적으로 CPU에 별개로 들어가 있다..
// 그 하드웨어에 os가 값을 받아와서 우리에게 알려주는 개념이다.

// 설명 :
class GameEngineTime
{
public:

	static GameEngineTime GlobalTime; // 프로그램의 글로벌타임

	// constrcuter destructer
	GameEngineTime();
	~GameEngineTime();

	// delete Function
	GameEngineTime(const GameEngineTime& _Other) = delete;
	GameEngineTime(GameEngineTime&& _Other) noexcept = delete;
	GameEngineTime& operator=(const GameEngineTime& _Other) = delete;
	GameEngineTime& operator=(GameEngineTime&& _Other) noexcept = delete;

	void Reset(); // Prev를 현재 시간으로 다시 설정

	// 이 사이에 벌어진 일의 시간을 재는 기능입니다.

	float TimeCheck(); // Current와 Prev사이 시간을 return하고 Prev를 현재시간으로 reset

	inline float GetFloatDeltaTime()
	{
		return floatDeltaTime;
	}

protected:
	

private:
	LARGE_INTEGER Prev = LARGE_INTEGER();
	LARGE_INTEGER Current = LARGE_INTEGER();
	LARGE_INTEGER Second = LARGE_INTEGER();
	double DoubleDeltaTime = 0.0;
	float floatDeltaTime = 0.0;

};

