#pragma once
#include <list>
#include <map>
#include <vector>

#include <GameEngineBase/GameEngineMath.h>
#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEngineCore/GameEngineObject.h>
// 설명 :
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

	template<typename ActorType, typename EnumType> // Enum을 모르기 때문에 int로 캐스팅하는 작업
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
	std::vector<GameEngineActor*> GetActors(EnumType _GroupIndex) // _GroupIndex에 해당하는 다운캐스팅된 actor list를 return
	{
		return GetActors(static_cast<int>(_GroupIndex));
	}

	std::vector<GameEngineActor*> GetActors(int _GroupIndex)
	{
		std::vector<GameEngineActor*> Result;

		// 어떤 
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

	// 내가 이제 다른 레벨로 교체된다.
	virtual void LevelChangeEnd(GameEngineLevel* _NextLevel) = 0;
	// 내가 이제 새로운 눈에 보이는 레벨이 될거다.
	virtual void LevelChangeStart(GameEngineLevel* _PrevLevel) = 0;

	

private:

	float4 CameraPos = float4::Zero;/*GameEngineWindow::GetScreenSize().half();*/
	// 행동순서를 담은 map
	std::map<int, std::list<GameEngineActor*>> Actors;

	void ActorsUpdate(float _DeltaTime);
	void ActorsRender(float _DeltaTime);


	void ActorStart(GameEngineActor* _Actor, int _Order);

	// 랜더 순서를 담은 map
	std::map<int, std::list<GameEngineRender*>> Renders;

	void PushRender(GameEngineRender* _Render);

	std::map<int, std::list<GameEngineCollision*>> Collisions;

	void PushCollision(GameEngineCollision* _Collision);

	void Release();
};

