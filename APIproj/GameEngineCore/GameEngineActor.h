#pragma once

#include <list>
#include <string_view>

#include <Windows.h>

#include <GameEngineBase/GameEngineMath.h>
#include "GameEngineObject.h"

// ȭ�鿡 �����ϰ� ��ġ�� �־���ϴ� ���͵��� �⺻����� �������� �̴ϴ�.
// �׷����� �Ѵ�.

// ���� :
class GameEngineRender;
class GameEngineCollision;
class GameEngineLevel;
class GameEngineActor : public GameEngineObject
{
	friend GameEngineLevel;

public:
	// constrcuter destructer
	GameEngineActor();
	~GameEngineActor();

	// delete Function
	GameEngineActor(const GameEngineActor& _Other) = delete;
	GameEngineActor(GameEngineActor&& _Other) noexcept = delete;
	GameEngineActor& operator=(const GameEngineActor& _Other) = delete;
	GameEngineActor& operator=(GameEngineActor&& _Other) noexcept = delete;

	inline float4 GetPos()
	{
		return Pos;
	}

	inline void SetPos(const float4& _MovePos)
	{
		Pos = _MovePos;
	}

	inline void SetMove(const float4& _MovePos)
	{
		Pos += _MovePos;
	}

	GameEngineLevel* GetLevel();

#pragma region CreateRenderEnumOverLoadings

	template<typename EnumType>
	GameEngineRender* CreateRender(const std::string_view& _Image, EnumType _Order)
	{
		return CreateRender(_Image, static_cast<int>(_Order));
	}

	template<typename EnumType>
	GameEngineRender* CreateRender(EnumType _Order)
	{
		return CreateRender(static_cast<int>(_Order));
	}

#pragma endregion

	GameEngineRender* CreateRender(const std::string_view& _Image, int _Order = 0);
	GameEngineRender* CreateRender(int _Order = 0);

	template<typename EnumType>
	GameEngineCollision* CreateCollision(EnumType _GroupIndex)
	{
		return CreateCollision(static_cast<int>(_GroupIndex));
	}

	GameEngineCollision* CreateCollision(int _GroupIndex = 0);


protected:
	// �ȱ����Ҽ��� �ִ�.
	// ex) ������ Update�� �ȱ����Ҽ��� �ִ�.

	// �����ϱ����� ���� �غ��ؾ��Ұ��� ������ ���⼭ �ض�.
	virtual void Start() {}

	// Ű�Է��� �ްų� �ΰ������� ������ ����ϰų� �ϴ� �͵��� ���⼭ ó��
	virtual void Update(float _DeltaTime) {}

	// ������ ���� �Լ��� �ѹ� �������ϰ� 
	virtual void LateUpdate(float _DeltaTime) {}

	// ȭ�鿡 �׷����� ��ɵ��� ���⼭ ó��
	virtual void Render(float _DeltaTime) {}

	inline float GetLiveTime()
	{
		return LiveTime;
	}

	virtual void LevelChangeEnd(GameEngineLevel* _PrevLevel);
	virtual void LevelChangeStart(GameEngineLevel* _PrevLevel);


private:

	float4 Pos = {0.0f, 0.0f};
	float LiveTime = 0.0;

	std::list<GameEngineRender*> RenderList; // actor�� ���Ե� �߰� img�� ������ list ex) player�� hp��
	std::list<GameEngineCollision*> CollisionList;

	void Release();
};

