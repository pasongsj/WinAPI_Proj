#pragma once
#include <list>
#include <map>
#include <vector>

#include <GameEngineBase/GameEngineMath.h>
#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEngineCore/GameEngineObject.h>
// ���� :
class GameEngineCore;
class GameEngineRender;
class GameEngineActor;
class GameEngineCollision;
class GameEngineLevel : public GameEngineObject
{
	friend GameEngineCore;
	friend GameEngineRender;
	friend GameEngineCollision;

public:
	// constrcuter destructer
	GameEngineLevel();
	virtual ~GameEngineLevel() = 0;

	// delete Function
	GameEngineLevel(const GameEngineLevel& _Other) = delete;
	GameEngineLevel(GameEngineLevel&& _Other) noexcept = delete;
	GameEngineLevel& operator=(const GameEngineLevel& _Other) = delete;
	GameEngineLevel& operator=(GameEngineLevel&& _Other) noexcept = delete;

	template<typename ActorType, typename EnumType> // Enum�� �𸣱� ������ int�� ĳ�����ϴ� �۾�
	ActorType* CreateActor(EnumType _Order)
	{
		return CreateActor<ActorType>(static_cast<int>(_Order));
	}

	template<typename ActorType>
	ActorType* CreateActor(int _Order = 0)
	{
		GameEngineActor* Actor = new ActorType();

		ActorStart(Actor, _Order);

		Actors[_Order].push_back(Actor);

		return dynamic_cast<ActorType*>(Actor);
	}

	inline void SetCameraMove(const float4& _MoveValue) {
		CameraPos += _MoveValue;
	}

	inline void SetCameraPos(const float4& _Pos) {
		CameraPos = _Pos;
	}
	inline float4 GetCameraPos()
	{
		return CameraPos;
	}

	template<typename EnumType>
	std::vector<GameEngineActor*> GetActors(EnumType _GroupIndex) // _GroupIndex�� �ش��ϴ� �ٿ�ĳ���õ� actor list�� return
	{
		return GetActors(static_cast<int>(_GroupIndex));
	}

	std::vector<GameEngineActor*> GetActors(int _GroupIndex)
	{
		std::vector<GameEngineActor*> Result;

		// � 
		std::list<GameEngineActor*>& Group = Actors[_GroupIndex];
		Result.reserve(Group.size());

		for (GameEngineActor* ActorPtr : Group)
		{
			Result.push_back(ActorPtr);
		}

		return Result;
	}

protected:
	virtual void Loading() = 0;
	virtual void Update(float _DeltaTime) = 0;

	// ���� ���� �ٸ� ������ ��ü�ȴ�.
	virtual void LevelChangeEnd(GameEngineLevel* _NextLevel) = 0;
	// ���� ���� ���ο� ���� ���̴� ������ �ɰŴ�.
	virtual void LevelChangeStart(GameEngineLevel* _PrevLevel) = 0;

	

private:

	float4 CameraPos = float4::Zero;/*GameEngineWindow::GetScreenSize().half();*/
	// �ൿ������ ���� map
	std::map<int, std::list<GameEngineActor*>> Actors;

	void ActorsUpdate(float _DeltaTime);
	void ActorsRender(float _DeltaTime);


	void ActorStart(GameEngineActor* _Actor, int _Order);

	// ���� ������ ���� map
	std::map<int, std::list<GameEngineRender*>> Renders;

	void PushRender(GameEngineRender* _Render);

	std::map<int, std::list<GameEngineCollision*>> Collisions;

	void PushCollision(GameEngineCollision* _Collision);

	void Release();
};

