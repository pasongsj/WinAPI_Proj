#pragma once
#include <GameEnginePlatform/GameEngineImage.h>
#include "GameEngineObject.h"

 // 랜더링에 관련된 기능을 모두 집약한다.
 // 액터를 하나를 랜더링 할 때 같이 따라오는 이미지가 있다 ex) player에 따라오는 HP bar
 // actor에서 render를 list로 보관하여 연쇄적으로 랜더링 할 수 있도록

class GameEngineActor;
class GameEngineLevel;
class GameEngineRender : public GameEngineObject
{
	friend GameEngineLevel;
	friend GameEngineActor;
public:
	// constrcuter destructer
	GameEngineRender() ;
	~GameEngineRender();

	// delete Function
	GameEngineRender(const GameEngineRender& _Other) = delete;
	GameEngineRender(GameEngineRender&& _Other) noexcept = delete;
	GameEngineRender& operator=(const GameEngineRender& _Other) = delete;
	GameEngineRender& operator=(GameEngineRender&& _Other) noexcept = delete;
	
	void SetImage(const std::string_view& _ImageName);

	inline void SetPosition(float4 _Position)
	{
		Position = _Position;
	}

	inline void SetScale(float4 _Scale)
	{
		Scale = _Scale;
	}

	void SetFrame(int _Frame);

	inline GameEngineImage* GetImage()
	{
		return Image;
	}

	inline int GetOrder()
	{
		return Order;
	}

	inline int GetFrame()
	{
		return Frame;
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
	GameEngineActor* Owner = nullptr; // 센터가 되는 엑터 ex) player자체

	int Order = 0; // 랜더링 순서
	float4 Position = float4::Zero;
	float4 Scale = float4::Zero;
	GameEngineImage* Image = nullptr;

	int Frame = 0;

	void SetOrder(int _Order);

	void Render(float _DeltaTime);
};

