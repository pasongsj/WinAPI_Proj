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
			MsgAssert(Name + "�̹� �����ϴ� �̸��� ������ ������� �߽��ϴ�");
			return;
		}

		GameEngineLevel* Level = new LevelType();
		Levels.insert(std::make_pair(_Name, Level));
	}

	

	void ChangeLevel(const std::string_view& _Name);

	virtual void Start() = 0; // ���������Լ�
	virtual void Update() = 0;
	virtual void End() = 0;

private:
	// ���� Level(ȭ��)�� �����ϰ� �ִ� levels
	// �� map?? ���ϴ� level�� ã��(find method) ���ϰ� �ϱ� ���� 
	std::map<std::string_view, GameEngineLevel*> Levels;

	// ���� ȭ�鿡 ������� Level
	GameEngineLevel* MainLevel = nullptr;
};
