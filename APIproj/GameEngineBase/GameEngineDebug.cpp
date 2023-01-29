#include "GameEngineDebug.h"
// #include <iostream>
#include <crtdbg.h> // _CrtSetDbgFlag 매크로를 사용하기 위한 헤더

GameEngineDebug::GameEngineDebug() 
{
}

GameEngineDebug::~GameEngineDebug() 
{
}


void GameEngineDebug::LeakCheck()
{
	// leak 결과를 콘솔창에 띄우는 기능
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
}
