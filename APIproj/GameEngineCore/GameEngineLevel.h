#pragma once
#include <list>
#include <map>

#include <GameEngineBase/GameEngineMath.h>
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

protected:
	virtual void Loading() = 0;
	virtual void Update(float _DeltaTime) = 0;

	// ���� ���� �ٸ� ������ ��ü�ȴ�.
	virtual void LevelChangeEnd(GameEngineLevel* _NextLevel) = 0;
	// ���� ���� ���ο� ���� ���̴� ������ �ɰŴ�.
	virtual void LevelChangeStart(GameEngineLevel* _PrevLevel) = 0;

	

private:

	float4 CameraPos = float4::Zero;
	// �ൿ������ ���� map
	std::map<int, std::list<GameEngineActor*>> Actors;

	void ActorsUpdate(float _DeltaTime);
	void ActorsRender(float _DeltaTime);


	void ActorStart(GameEngineActor* _Actor, int _Order);

	// ���� ������ ���� map
	std::map<int, std::list<GameEngineRender*>> Renders;

	void PushRender(GameEngineRender* _Render);


};

