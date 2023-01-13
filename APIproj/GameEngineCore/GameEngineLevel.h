#pragma once
#include <list>
#include <map>

// 설명 :
class GameEngineRender;
class GameEngineCore;
class GameEngineActor;
class GameEngineLevel
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

	/// <summary>
	/// 액터를 만드는 함수
	/// </summary>
	/// <typeparam name="ActorType"> GameEngineActor를 상속받은 클래스 타입 </typeparam>
	/// <param name="_Order"> Actor의 업데이트 순서 숫자가 작을수록 먼저 업데이트 됩니다. </param>
	template<typename ActorType>
	void CreateActor(int _Order = 0)
	{
		//if (Actors.end() == Actors.find(_Order))
		//{
		//	Actors.insert(std::make_pair(_Order, std::list<GameEngineActor*>()));
		//}

		GameEngineActor* Actor = new ActorType();

		ActorStart(Actor, _Order);

		// 맵의 새로운 문법
		Actors[_Order].push_back(Actor);
	}

protected:
	virtual void Loading() = 0;
	virtual void Update() = 0;

private:
	// 행동순서를 담은 map
	std::map<int, std::list<GameEngineActor*>> Actors;

	void ActorsUpdate(float _DeltaTime);
	void ActorsRender(float _DeltaTime);


	void ActorStart(GameEngineActor* _Actor, int _Order);

	// 랜더 순서를 담은 map
	std::map<int, std::list<GameEngineRender*>> Renders;

	void PushRender(GameEngineRender* _Render);


};

