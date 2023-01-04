#pragma once
#include <map>
#include <string_view>
#include <Windows.h>
#include <GameEngineBase/GameEngineDebug.h>

class GameEngineLevel;
class GameEngineCore
{
private:
	static void GlobalStart();
	static void GlobalUpdate();
	static void GlobalEnd();

public:
	// constrcuter destructer
	GameEngineCore() ;
	~GameEngineCore();

	// delete Function
	GameEngineCore(const GameEngineCore& _Other) = delete;
	GameEngineCore(GameEngineCore&& _Other) noexcept = delete;
	GameEngineCore& operator=(const GameEngineCore& _Other) = delete;
	GameEngineCore& operator=(GameEngineCore&& _Other) noexcept = delete;

	void CoreStart(HINSTANCE _instance);

protected:

	template<typename LevelType>
	void CreateLevel(const std::string_view& _Name)
	{
		if (Levels.end() != Levels.find(_Name))
		{
			std::string Name = _Name.data();
			MsgAssert(Name + "이미 존재하는 이름의 레벨을 만들려고 했습니다");
			return;
		}

		GameEngineLevel* Level = new LevelType();
		Levels.insert(std::make_pair(_Name, Level));
	}

	

	void ChangeLevel(const std::string_view& _Name);

	virtual void Start() = 0; // 순수가상함수
	virtual void Update() = 0;
	virtual void End() = 0;

private:
	// 여러 Level(화면)을 저장하고 있는 levels
	// 왜 map?? 원하는 level을 찾기(find method) 편하게 하기 위해 
	std::map<std::string_view, GameEngineLevel*> Levels;

	// 현재 화면에 띄워지는 Level
	GameEngineLevel* MainLevel = nullptr;
};
