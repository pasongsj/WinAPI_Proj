#pragma once
#include <map>

#include <GameEnginePlatform/GameEngineImage.h>

//#include "GameEngineObject.h"
#include "GameEngineComponent.h"
 // �������� ���õ� ����� ��� �����Ѵ�.
 // ���͸� �ϳ��� ������ �� �� ���� ������� �̹����� �ִ� ex) player�� ������� HP bar
 // actor���� render�� list�� �����Ͽ� ���������� ������ �� �� �ֵ���
// list�� �� ������ �ڵ带 ���������� �����ϰ� ����� �� �ֱ� ������

class FrameAnimationParameter
{
public:
	std::string_view AnimationName = "";
	std::string_view ImageName = "";
	int Start = 0;
	int End = 0;
	int CurrentIndex = 0;
	float InterTime = 0.1f;
	bool Loop = true;
	std::vector<int> FrameIndex = std::vector<int>();
	std::vector<float> FrameTime = std::vector<float>();
};

class GameEngineActor;
class GameEngineLevel;
class GameEngineRender : public GameEngineComponent
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

	//inline void SetPosition(float4 _Position)
	//{
	//	Position = _Position;
	//}

	//inline void SetScale(float4 _Scale)
	//{
	//	Scale = _Scale;
	//}

	void SetScaleToImage();
	
	void SetFrame(int _Frame);

	inline GameEngineImage* GetImage()
	{
		return Image;
	}

	inline int GetFrame()
	{
		return Frame;
	}


	//inline float4 GetPosition()
	//{
	//	return Position;
	//}

	//inline float4 GetScale()
	//{
	//	return Scale;
	//}

	inline void SetTransColor(int _Color)
	{
		TransColor = _Color;
	}

	//GameEngineActor* GetActor();

	inline void EffectCameraOff()
	{
		IsCameraEffect = false;
	}

	bool IsAnimationEnd();
	void CreateAnimation(const FrameAnimationParameter& _Paramter);
	void ChangeAnimation(const std::string_view& _AnimationName);

	void SetOrder(int _Order) override;

protected:

private:
	
	float4 Position = float4::Zero;
	float4 Scale = float4::Zero;
	GameEngineImage* Image = nullptr;
	bool IsCameraEffect = true;

	int Frame = 0;

	int TransColor = RGB(255, 0, 255); // ������ ��� RGB�� 

	void Render(float _DeltaTime);

	class FrameAnimation
	{
	public:
		GameEngineRender* Parent = nullptr;
		// ©���ִ� �̹������� �Ѵ�.
		GameEngineImage* Image = nullptr;
		std::vector<int> FrameIndex;
		std::vector<float> FrameTime;
		int CurrentIndex = 0;
		float CurrentTime = 0.0f;
		bool Loop = true;

		bool IsEnd();

		void Render(float _DeltaTime);

		void Reset()
		{
			CurrentIndex = 0;
			CurrentTime = 0.0f;
		}
	};

	std::map<std::string, FrameAnimation> Animation;
	FrameAnimation* CurrentAnimation = nullptr;

};

