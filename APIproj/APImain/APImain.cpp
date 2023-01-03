﻿// APImain.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//
#include <Windows.h>
#include <iostream>

#include <GameEngineBase/GameEngineDebug.h>
#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEngineBase/GameEngineMath.h>


void TestGameStart()
{
	int a = 0;
}

int x = 0;

void TestGameLoop()
{


	++x;
	// 화면에 그림을 그려주는 함수입니다.
	Rectangle(GameEngineWindow::GetDrawHdc(), 0 + x, 0, 100 + x, 100);

	// 몬스터가 움직이게 만들고
	// 플레이어가 움직이게 만들어야 한다.
	int a = 0;
}

void TestGameEnd()
{
	int a = 0;
}

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPWSTR    lpCmdLine,
	_In_ int       nCmdShow)
{
	GameEngineDebug::LeakCheck();

	//GameEngineWindow::WindowCreate(hInstance, "MainWindow", { 1280, 720 }, { 0, 0 });// 1090 * 690
	GameEngineWindow::WindowCreate(hInstance, "MainWindow", { 1090, 690 }, { 0, 0 });// 내 proj 화면비율

	GameEngineWindow::WindowLoop(TestGameStart, TestGameLoop, TestGameEnd);

	// main이 끝나면 무조건 끝나기 때문에
	// 무조건 붙잡아둬야 합니다.

	return 1;
}