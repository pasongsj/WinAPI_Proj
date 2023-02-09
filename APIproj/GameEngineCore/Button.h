#pragma once
#include "GameEngineActor.h"
#include "GameEngineCollision.h"
#include "GameEngineRender.h"

enum class ButtonState
{
	Release, // 안눌렸다.
	Press, // 눌렸다.
	Hover, // 마우스가 버튼 위에 있어 표기됨
};

class GameEngineRender;
class Button : public GameEngineActor
{
public:
	// constrcuter destructer
	Button() ;
	~Button();

	// delete Function
	Button(const Button& _Other) = delete;
	Button(Button&& _Other) noexcept = delete;
	Button& operator=(const Button& _Other) = delete;
	Button& operator=(Button&& _Other) noexcept = delete;

	void SetRenderOrder(int _Value);

	void SetScale(float4 _Scale);

	void SetClickCallBack(void(*_ClickPtr)())
	{
		ClickPtr = _ClickPtr;
	}

	void SetTargetCollisionGroup(int _PointTargetGroup);

	void SetButtonCollisionType(CollisionType _ButtonCollisionType)
	{
		ButtonCollisionType = _ButtonCollisionType;
	}

	void SetHoverImage(const std::string_view& _Name)
	{
		HoverImageName = _Name;
	}
	void SetReleaseImage(const std::string_view& _Name)
	{
		ReleaseImageName = _Name;
	}
	void SetPressImage(const std::string_view& _Name)
	{
		PressImageName = _Name;
	}

	GameEngineRender* GetButtonRender()
	{
		return ButtonRender;
	}

	GameEngineCollision* GetButtonCollision()
	{
		return ButtonCollision;
	}

	void setting(const std::string_view& _ReleaseName, const std::string_view& _HoverName, const std::string_view& _PressName, 
		float4 _Pos, float4 _Scale, int _Order ,bool _EffectCam);

protected:

	void Start() override;
	void Update(float _DeltaTime) override;

private:
	GameEngineRender* ButtonRender = nullptr;
	GameEngineCollision* ButtonCollision = nullptr;
	int PointTargetGroup = 0;
	CollisionType ButtonCollisionType = CollisionType::CT_Rect;
	void(*ClickPtr)() = nullptr;

	float4 Scale;
	ButtonState State;
	std::string CurImageName;
	std::string HoverImageName;
	std::string ReleaseImageName;
	std::string PressImageName;
};

