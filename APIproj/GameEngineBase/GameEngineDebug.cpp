#include "GameEngineDebug.h"
// #include <iostream>
#include <crtdbg.h> // _CrtSetDbgFlag ��ũ�θ� ����ϱ� ���� ���

GameEngineDebug::GameEngineDebug() 
{
}

GameEngineDebug::~GameEngineDebug() 
{
}


void GameEngineDebug::LeakCheck()
{
	// leak ����� �ܼ�â�� ���� ���
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
}
