#pragma once
#include <GameEnginePlatform/GameEngineImage.h>

 // �������� ���õ� ����� ��� �����Ѵ�.
 // ���͸� �ϳ��� ������ �� �� ���� ������� �̹����� �ִ� ex) player�� ������� HP bar
 // actor���� render�� list�� �����Ͽ� ���������� ������ �� �� �ֵ���

class GameEngineActor;
class GameEngineLevel;
class GameEngineRender
{
	friend GameEngineLevel;
public:
	// constrcuter destructer
	GameEngineRender() ;
	~GameEngineRender();

	// delete Function
	GameEngineRender(const GameEngineRender& _Other) = delete;
	GameEngineRender(GameEngineRender&& _Other) noexcept = delete;
	GameEngineRender& operator=(const GameEngineRender& _Other) = delete;
	GameEngineRender& operator=(GameEngineRender&& _Other) noexcept = delete;

	inline void SetPosition(float4 _Position)
	{
		Position = _Position;
	}

	inline void SetScale(float4 _Scale)
	{
		Scale = _Scale;
	}

	inline int GetOrder()
	{
		return Order;
	}

protected:

private:
	GameEngineActor* Owner = nullptr; // ���Ͱ� �Ǵ� ���� ex) player��ü

	int Order = 0; // ������ ����
	float4 Position = float4::Zero;
	float4 Scale = float4::Zero;
	GameEngineImage* Image = nullptr;
	int Frame = 0;

	void SetOrder(int _Order);

	void Render(float _DeltaTime);
};

