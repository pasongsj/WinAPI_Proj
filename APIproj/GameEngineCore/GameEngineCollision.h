#pragma once
#include "GameEngineComponent.h"
//#include <GameEngineBase/GameEngineMath.h>
#include <vector>

enum CollisionType
{
	CT_Point,
	CT_CirCle,
	CT_Rect,
	CT_Max,
};

class CollisionCheckParameter
{
public:
	int TargetGroup = -342367842; // 초기화를 하지 않으면 터트릴 수 있도록
	CollisionType TargetColType = CollisionType::CT_CirCle;
	CollisionType ThisColType = CollisionType::CT_CirCle;
};

class CollisionData
{
public:
	float4 Position;
	float4 Scale; // circle은 x값이 원의 반지름값
};

class CollisionFunctionInit;
class GameEngineCollision : public GameEngineComponent
{
	friend CollisionFunctionInit;
public:
	static bool CollisionCirCleToCirCle(const CollisionData& _Left, const CollisionData& _Right);

	// constrcuter destructer
	GameEngineCollision() ;
	~GameEngineCollision();

	// delete Function
	GameEngineCollision(const GameEngineCollision& _Other) = delete;
	GameEngineCollision(GameEngineCollision&& _Other) noexcept = delete;
	GameEngineCollision& operator=(const GameEngineCollision& _Other) = delete;
	GameEngineCollision& operator=(GameEngineCollision&& _Other) noexcept = delete;

	bool Collision(const CollisionCheckParameter& _CollisionCheck);

	bool Collision(const CollisionCheckParameter& _CollisionCheck, std::vector<GameEngineCollision*>& _Collision);

	void SetOrder(int _Order) override;

	CollisionData GetCollisionData();

protected:

private:


};

