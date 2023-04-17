#pragma once
#include <Windows.h>
#include <map>
#include <string_view>
#include <GameEngineBase/GameEngineDebug.h>

// 단 한개의 코어를 사용한다고 생각한다.

// 설명 : 엔진에서 응당 로드해야할 필수적인 리소스나 
// 순수가상함수가 있으니까 추상클래스이다.
class GameEngineLevel;
class GameEngineCore
{
private:
	static void GlobalStart();
	static void GlobalUpdate();
	static void GlobalEnd();

public:
	// constrcuter destructer
	GameEngineCore();
	~GameEngineCore();

	// delete Function
	GameEngineCore(const GameEngineCore& _Other) = delete;
	GameEngineCore(GameEngineCore&& _Other) noexcept = delete;
	GameEngineCore& operator=(const GameEngineCore& _Other) = delete;
	GameEngineCore& operator=(GameEngineCore&& _Other) noexcept = delete;

	void CoreStart(HINSTANCE _instance);

	void ChangeLevel(const std::string_view& _Name);

	static GameEngineCore* GetInst();

	static float GetSpeed()
	{
		return SpeedUp;
	}
	static void SetSpeedUp(float _speed)
	{
		SpeedUp = _speed;
	}


protected:
	template<typename LevelType>
	void CreateLevel(const std::string_view& _Name)
	{
		// Title을 만들었는데
		// 또 Title을 만들겠다고 한 상황
		if (Levels.end() != Levels.find(_Name.data()))
		{
			std::string Name = _Name.data();
			MsgAssert(Name + "이미 존재하는 이름의 레벨을 만들려고 했습니다");
			return;
		}

		GameEngineLevel* Level = new LevelType();
		LevelLoading(Level);
		// Level->Loading();
		// insert할때마다 새로운 string이 생기면서 자신만의 메모리를 가지게 된다.
		Levels.insert(std::make_pair(_Name.data(), Level));
	}

	virtual void Start() = 0;
	virtual void Update() = 0;
	virtual void End() = 0;

private:
	// 그래서 map을 사용한다. 
	// 레벨이라는것은 장면입니다.
	// GameEngineLevel을 "어떠한 이름"으로 찾고 이름으로 실행시키고.
	std::map<std::string, GameEngineLevel*> Levels;

	GameEngineLevel* NextLevel = nullptr;

	GameEngineLevel* MainLevel = nullptr;

	void LevelLoading(GameEngineLevel* _Level);

	static float SpeedUp;

};

