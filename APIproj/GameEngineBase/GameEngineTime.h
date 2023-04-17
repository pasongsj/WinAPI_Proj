#pragma once
#include <chrono>
#include <Windows.h>

// �ð��� ��ų� �ϴ� ��ɵ��� ���.
// �⺻������ �ð��� ��� ����� ���������� ������
// �ð��� ��� ����� �⺻������ CPU�� ������ �� �ִ�..
// �� �ϵ��� os�� ���� �޾ƿͼ� �츮���� �˷��ִ� �����̴�.

// ���� :
class GameEngineTime
{
public:

	static GameEngineTime GlobalTime; // ���α׷��� �۷ι�Ÿ��

	// constrcuter destructer
	GameEngineTime();
	~GameEngineTime();

	// delete Function
	GameEngineTime(const GameEngineTime& _Other) = delete;
	GameEngineTime(GameEngineTime&& _Other) noexcept = delete;
	GameEngineTime& operator=(const GameEngineTime& _Other) = delete;
	GameEngineTime& operator=(GameEngineTime&& _Other) noexcept = delete;

	void Reset(); // Prev�� ���� �ð����� �ٽ� ����

	// �� ���̿� ������ ���� �ð��� ��� ����Դϴ�.

	float TimeCheck(); // Current�� Prev���� �ð��� return�ϰ� Prev�� ����ð����� reset

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

