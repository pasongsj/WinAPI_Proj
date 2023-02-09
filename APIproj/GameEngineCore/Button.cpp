#include "Button.h"
#include <GameEnginePlatform/GameEngineInput.h>


Button::Button()
{
	State = ButtonState::Release;
}

Button::~Button()
{
}


void Button::SetTargetCollisionGroup(int _PointTargetGroup)
{
	PointTargetGroup = _PointTargetGroup;
	if (nullptr == ButtonCollision)
	{
		ButtonCollision = CreateCollision(PointTargetGroup);
	}
}


void Button::Start()
{
	ButtonRender = CreateRender();
	ButtonCollision = CreateCollision();
	ButtonCollision->SetDebugRenderType(ButtonCollisionType);
}

void Button::SetRenderOrder(int _Value)
{
	ButtonRender->SetOrder(_Value);
}

void Button::SetScale(float4 _Scale)
{
	Scale = _Scale;
	ButtonCollision->SetScale(Scale);
	ButtonRender->SetScale(_Scale);
}

void Button::Update(float _DeltaTime)
{
	State = ButtonState::Release;

	if (true == ButtonCollision->Collision({ .TargetGroup = PointTargetGroup, .TargetColType = CollisionType::CT_Point, .ThisColType = ButtonCollisionType }))
	{
		int a = 0;
		if (true == GameEngineInput::IsUp("EngineMouseLeft") && nullptr != ClickPtr)
		{
			ClickPtr();
		}
		else if (true == GameEngineInput::IsFree("EngineMouseLeft"))
		{
			State = ButtonState::Hover;
		}
		else if (true == GameEngineInput::IsPress("EngineMouseLeft"))
		{
			State = ButtonState::Press;
		}
	}

	switch (State)
	{
	case ButtonState::Release:
		CurImageName = ReleaseImageName;
		ButtonRender->SetImage(ReleaseImageName);
		break;

	case ButtonState::Press:
		CurImageName = PressImageName;
		ButtonRender->SetImage(PressImageName);
		break;

	case ButtonState::Hover:
		CurImageName = HoverImageName;
		ButtonRender->SetImage(HoverImageName);
		break;

	default:
		break;
	}
}

void Button::setting(const std::string_view& _ReleaseName, const std::string_view& _HoverName, const std::string_view& _PressName, float4 _Pos, float4 _Scale, int _Order, bool _EffectCam)
{
	SetReleaseImage(_ReleaseName);
	SetHoverImage(_HoverName);
	SetPressImage(_PressName);
	SetPos(_Pos);
	Button::SetScale(_Scale);
	SetRenderOrder(_Order);
	ButtonRender->SetEffectCamera(_EffectCam);
}