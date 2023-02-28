#pragma once
#include <map>

#include <GameEnginePlatform/GameEngineImage.h>

//#include "GameEngineObject.h"
#include "GameEngineComponent.h"
 // 랜더링에 관련된 기능을 모두 집약한다.
 // 액터를 하나를 랜더링 할 때 같이 따라오는 이미지가 있다 ex) player에 따라오는 HP bar
 // actor에서 render를 list로 보관하여 연쇄적으로 랜더링 할 수 있도록
// list로 한 이유는 코드를 직관적으로 이해하고 사용할 수 있기 때문에

class FrameAnimationParameter
{
public:
	std::string_view AnimationName = "";
	std::string_view ImageName = "";
	std::string_view FilterName = "";

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

	void SetImageToScaleToImage(const std::string_view& _ImageName);

	void SetScaleToImage();
	
	void SetFrame(int _Frame);

	void SetRotFilter(const std::string_view& _ImageName);

	inline GameEngineImage* GetImage()
	{
		return Image;
	}

	inline int GetFrame()
	{
		return Frame;
	}

	inline void SetTransColor(int _Color)
	{
		TransColor = _Color;
	}

	//GameEngineActor* GetActor();
	inline void SetEffectCamera(bool _Effect)
	{
		IsEffectCamera = _Effect;
	}

	inline void EffectCameraOff()
	{
		SetEffectCamera(false);
	}

	inline void EffectCameraOn()
	{
		SetEffectCamera(true);
	}

	bool IsAnimationEnd();
	void CreateAnimation(const FrameAnimationParameter& _Paramter);
	void ChangeAnimation(const std::string_view& _AnimationName);

	void SetOrder(int _Order) override;

	void SetText(const std::string_view& _Text);

	inline void SetAlpha(int _Alpha)
	{
		Alpha = _Alpha;
	}

	inline void SetAngle(float _Angle)
	{
		Angle = _Angle;
	}

	inline float GetAngle()
	{
		return Angle;
	}

	inline void SetAngleAdd(float _Angle)
	{
		Angle += _Angle;
	}


protected:

private:
	GameEngineImage* Image = nullptr;
	GameEngineImage* RotationFilter = nullptr;

	float4 Position = float4::Zero;
	float4 Scale = float4::Zero;
	bool IsEffectCamera = true;

	int Frame = 0;

	int TransColor = RGB(255, 0, 255); // 제거할 배경 RGB값 
	int Alpha = 255; // 투명도 0~255
	float Angle = 0.0f; // (반시계방향) 각도

	void Render(float _DeltaTime);

	void TextRender(float _DeltaTime);
	void ImageRender(float _DeltaTime);

	class FrameAnimation
	{
	public:
		GameEngineRender* Parent = nullptr;
		// 짤려있는 이미지여야 한다.
		GameEngineImage* Image = nullptr;
		GameEngineImage* FilterImage = nullptr;
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

	std::string RenderText;

};

