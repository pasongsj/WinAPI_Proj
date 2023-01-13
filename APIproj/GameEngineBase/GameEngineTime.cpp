#include "GameEngineTime.h"

GameEngineTime::GameEngineTime() 
{
	// 1초를 기준으로한 정수 단위입니다. 
	QueryPerformanceFrequency(&Second);
}

GameEngineTime::~GameEngineTime() 
{
}

void GameEngineTime::Reset()
{
	QueryPerformanceCounter(&Prev); // 현재시간을 Prev에 저장
}


float GameEngineTime::TimeCheck()
{
	QueryPerformanceCounter(&Current); // TimeCheck하는 현재시간을 current에 저장

	DoubleDeltaTime = (static_cast<double>(Current.QuadPart) - static_cast<double>(Prev.QuadPart)) / static_cast<double>(Second.QuadPart); // 한번에 loop 연산이 돌고있는 절대시간
	
	Prev.QuadPart = Current.QuadPart; // Prev reset
	floatDeltaTime = static_cast<float>(DoubleDeltaTime);

	return floatDeltaTime;
}