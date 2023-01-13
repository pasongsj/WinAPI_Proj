#include "GameEngineCore.h"
#include <GameEngineBase/GameEngineDebug.h>
#include <GameEnginePlatform/GameEngineWindow.h>
#include "GameEngineLevel.h"
#include "GameEngineResources.h"
#include <GameEngineBase/GameEngineTime.h>

GameEngineCore* Core;

void GameEngineCore::GlobalStart() 
{
	Core->Start();
	GameEngineTime::GlobalTime.Reset(); // start
}

void GameEngineCore::GlobalUpdate() 
{
	float TimeDeltaTime = GameEngineTime::GlobalTime.TimeCheck(); // 1프레임의 델타타임
	Core->Update();
	if (nullptr == Core->MainLevel)
	{
		MsgAssert("레벨을 지정해주지 않은 상태로 코어를 실행했습니다");
		return;
	}

	Core->MainLevel->ActorsUpdate(TimeDeltaTime);
	GameEngineWindow::DoubleBufferClear();
	Core->MainLevel->ActorsRender(TimeDeltaTime);
	GameEngineWindow::DoubleBufferRender();
}

void GameEngineCore::GlobalEnd() 
{
	Core->End();

	GameEngineResources::GetInst().Release();
}


GameEngineCore::GameEngineCore() 
{
	GameEngineDebug::LeakCheck();
	// 나는 자식중에 하나일수밖에 없다.
	// 나는 절대만들어질수 없기 때문이다.
	Core = this;
}

GameEngineCore::~GameEngineCore() 
{
	std::map<std::string, GameEngineLevel*>::iterator StartIter = Levels.begin();
	std::map<std::string, GameEngineLevel*>::iterator EndIter = Levels.end();

	for (size_t i = 0; StartIter != EndIter; ++StartIter)
	{
		if (nullptr != StartIter->second)
		{
			delete StartIter->second;
		}
	}

	Levels.clear();
}

void GameEngineCore::CoreStart(HINSTANCE _instance)
{
	GameEngineWindow::WindowCreate(_instance, "MainWindow", { 1280, 720 }, { 0, 0 });
	GameEngineWindow::WindowLoop(GameEngineCore::GlobalStart, GameEngineCore::GlobalUpdate, GameEngineCore::GlobalEnd);
}

void GameEngineCore::ChangeLevel(const std::string_view& _Name) 
{
	std::map<std::string, GameEngineLevel*>::iterator FindIter = Levels.find(_Name.data());

	if (FindIter == Levels.end())
	{
		std::string Name = _Name.data();
		MsgAssert(Name + "존재하지 않는 레벨을 실행시키려고 했습니다");
		return;
	}

	MainLevel = FindIter->second;
}

void GameEngineCore::LevelLoading(GameEngineLevel* _Level)
{
	if (nullptr == _Level)
	{
		MsgAssert("nullptr 인 레벨을 로딩하려고 했습니다.");
		return;
	}

	_Level->Loading();
}