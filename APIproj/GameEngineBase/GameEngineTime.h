#pragma once
#include <chrono>
#include <Windows.h>

// �ð��� ��ų� �ϴ� ��ɵ��� ����մϴ�.
// �⺻������ �ð��� ��� ����� ���������� ������
// �������� C++ std�� �ֽű���� ũ�γ븦 �̿��Ұ̴ϴ�.
// �ð��� ��� ����� �⺻������ CPU�� ������ �� �ֽ��ϴ�.
// �� �ϵ��� os�� ���� �޾ƿͼ� �츮���� �˷��ִ� �����̴�.

// �׷��� �⺻������ �ð��� ��� ������ ǥ���ϰ� �˴ϴ�.
// ������ ����ϴ�. 

// ���� :
class GameEngineTime
{
public:
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

protected:
	

private:
	LARGE_INTEGER Prev = LARGE_INTEGER();
	LARGE_INTEGER Current = LARGE_INTEGER();
	LARGE_INTEGER Second = LARGE_INTEGER();
	double DoubleDeltaTime = 0.0;
	float floatDeltaTime = 0.0;

};

