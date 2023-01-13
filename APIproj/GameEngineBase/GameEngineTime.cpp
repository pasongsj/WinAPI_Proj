#include "GameEngineTime.h"

GameEngineTime::GameEngineTime() 
{
	// 1�ʸ� ���������� ���� �����Դϴ�. 
	QueryPerformanceFrequency(&Second);
}

GameEngineTime::~GameEngineTime() 
{
}

void GameEngineTime::Reset()
{
	QueryPerformanceCounter(&Prev); // ����ð��� Prev�� ����
}


float GameEngineTime::TimeCheck()
{
	QueryPerformanceCounter(&Current); // TimeCheck�ϴ� ����ð��� current�� ����

	DoubleDeltaTime = (static_cast<double>(Current.QuadPart) - static_cast<double>(Prev.QuadPart)) / static_cast<double>(Second.QuadPart); // �ѹ��� loop ������ �����ִ� ����ð�
	
	Prev.QuadPart = Current.QuadPart; // Prev reset
	floatDeltaTime = static_cast<float>(DoubleDeltaTime);

	return floatDeltaTime;
}