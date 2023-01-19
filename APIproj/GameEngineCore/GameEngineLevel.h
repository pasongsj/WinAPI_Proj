#pragma once
#include <list>
#include <map>

#include <GameEngineCore/GameEngineObject.h>
// ���� :
class GameEngineCore;
class GameEngineRender;
class GameEngineActor;
class GameEngineLevel : public GameEngineObject
{
	friend GameEngineCore;
	friend GameEngineRender;

public:
	// constrcuter destructer
	GameEngineLevel();
	virtual ~GameEngineLevel() = 0;

	// delete Function
	GameEngineLevel(const GameEngineLevel& _Other) = delete;
	GameEngineLevel(GameEngineLevel&& _Other) noexcept = delete;
	GameEngineLevel& operator=(const GameEngineLevel& _Other) = delete;
	GameEngineLevel& operator=(GameEngineLevel&& _Other) noexcept = delete;

	
	template<typename ActorType>
	void CreateActor(int _Order = 0)
	{
		GameEngineActor* Actor = new ActorType();

		ActorStart(Actor, _Order);

		Actors[_Order].push_back(Actor);
	}

protected:
	virtual void Loading() = 0;
	virtual void Update(float _DeltaTime) = 0;

	// ���� ���� �ٸ� ������ ��ü�ȴ�.
	virtual void LevelChangeEnd(GameEngineLevel* _NextLevel) = 0;
	// ���� ���� ���ο� ���� ���̴� ������ �ɰŴ�.
	virtual void LevelChangeStart(GameEngineLevel* _PrevLevel) = 0;

private:
	// �ൿ������ ���� map
	std::map<int, std::list<GameEngineActor*>> Actors;

	void ActorsUpdate(float _DeltaTime);
	void ActorsRender(float _DeltaTime);


	void ActorStart(GameEngineActor* _Actor, int _Order);

	// ���� ������ ���� map
	std::map<int, std::list<GameEngineRender*>> Renders;

	void PushRender(GameEngineRender* _Render);


};

