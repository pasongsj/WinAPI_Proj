// APImain.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//
#include <Windows.h>
#include <iostream>

#include <GameEngineBase/GameEngineDebug.h>
#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEngineBase/GameEngineMath.h>

//int main()
//{
//    std::cout << "Hello World!\n";
//}

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPWSTR    lpCmdLine,
	_In_ int       nCmdShow)
{
	GameEngineDebug::LeakCheck();

	GameEngineWindow::WindowCreate(hInstance, "MainWindow", { 1280, 720 }, { 0, 0 });

	//GameEngineWindow::WindowLoop(TestGameStart, TestGameLoop, TestGameEnd);

	// main이 끝나면 무조건 끝나기 때문에
	// 무조건 붙잡아둬야 합니다.

	return 1;
}