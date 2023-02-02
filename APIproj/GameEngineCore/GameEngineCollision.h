#pragma once
#include "GameEngineObject.h"
#include <GameEngineBase/GameEngineMath.h>

class GameEngineCollision : public GameEngineObject
{
public:
	// constrcuter destructer
	GameEngineCollision() ;
	~GameEngineCollision();

	// delete Function
	GameEngineCollision(const GameEngineCollision& _Other) = delete;
	GameEngineCollision(GameEngineCollision&& _Other) noexcept = delete;
	GameEngineCollision& operator=(const GameEngineCollision& _Other) = delete;
	GameEngineCollision& operator=(GameEngineCollision&& _Other) noexcept = delete;

	inline void SetPosition(float4 _Position)
	{
		Position = _Position;
	}

	inline void SetScale(float4 _Scale)
	{
		Scale = _Scale;
	}

	inline float4 GetPosition()
	{
		return Position;
	}

	inline float4 GetScale()
	{
		return Scale;
	}

protected:

private:
	float4 Position = float4::Zero;
	float4 Scale = float4::Zero;

};

