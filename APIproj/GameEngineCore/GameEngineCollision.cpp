#include "GameEngineCollision.h"
#include "GameEngineActor.h"
#include "GameEngineLevel.h"
#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEnginePlatform/GameEngineImage.h>

static bool(*ColFunctionPtr[CT_Max][CT_Max])(const CollisionData& _Left, const CollisionData& _Right);


class CollisionFunctionInit
{
public:
	CollisionFunctionInit()
	{
		ColFunctionPtr[CT_CirCle][CT_CirCle] = GameEngineCollision::CollisionCirCleToCirCle;
		ColFunctionPtr[CT_CirCle][CT_Point] = GameEngineCollision::CollisionCirCleToPoint;
		ColFunctionPtr[CT_Rect][CT_Rect] = GameEngineCollision::CollisionRectToRect;
		ColFunctionPtr[CT_Rect][CT_Point] = GameEngineCollision::CollisionRectToPoint;
		ColFunctionPtr[CT_Point][CT_CirCle] = GameEngineCollision::CollisionPointToCirCle;
		ColFunctionPtr[CT_Point][CT_Rect] = GameEngineCollision::CollisionPointToRect;
		ColFunctionPtr[CT_CirCle][CT_Rect] = GameEngineCollision::CollisionCirCleToRect;
		ColFunctionPtr[CT_Rect][CT_CirCle] = GameEngineCollision::CollisionRectToCirCle;
	}
	~CollisionFunctionInit()
	{

	}
};

CollisionFunctionInit Init = CollisionFunctionInit();

GameEngineCollision::GameEngineCollision()
{
}

GameEngineCollision::~GameEngineCollision()
{
}

bool GameEngineCollision::CollisionCirCleToPoint(const CollisionData& _Left, const CollisionData& _Right)
{
	float4 Len = _Left.Position - _Right.Position;
	float Size = Len.Size();
	float RadiusSum = _Left.Scale.hx();
	return RadiusSum > Size;
}

bool GameEngineCollision::CollisionCirCleToCirCle(const CollisionData& _Left, const CollisionData& _Right)
{
	float4 Len = _Left.Position - _Right.Position;
	float Size = Len.Size();
	float RadiusSum = _Left.Scale.hx() + _Right.Scale.hx();
	return RadiusSum > Size;
}

bool GameEngineCollision::CollisionRectToRect(const CollisionData& _Left, const CollisionData& _Right)
{
	if (_Left.Bot() <= _Right.Top())
	{
		return false;
	}

	if (_Left.Top() >= _Right.Bot())
	{
		return false;
	}

	if (_Left.Left() >= _Right.Right())
	{
		return false;
	}

	if (_Left.Right() <= _Right.Left())
	{
		return false;
	}

	return true;
}

bool GameEngineCollision::CollisionRectToPoint(const CollisionData& _Left, const CollisionData& _Right)
{
	if (_Left.Bot() <= _Right.Position.y)
	{
		return false;
	}

	if (_Left.Top() >= _Right.Position.y)
	{
		return false;
	}

	if (_Left.Left() >= _Right.Position.x)
	{
		return false;
	}

	if (_Left.Right() <= _Right.Position.x)
	{
		return false;
	}

	return true;
}

bool GameEngineCollision::CollisionPointToCirCle(const CollisionData& _Left, const CollisionData& _Right)
{
	return CollisionCirCleToPoint(_Right, _Left);
}

bool GameEngineCollision::CollisionPointToRect(const CollisionData& _Left, const CollisionData& _Right)
{
	return CollisionRectToPoint(_Right, _Left);
}

double Distance(POINT p1, POINT p2)
{
	LONGLONG x = (LONGLONG)p1.x - (LONGLONG)p2.x;
	LONGLONG y = (LONGLONG)p1.y - (LONGLONG)p2.y;
	return sqrt(x * x + y * y);
}

bool GameEngineCollision:: CollisionRectToCirCle(const CollisionData& _Left, const CollisionData& _Right)
{
	int x = _Right.Position.ix();
	int y = _Right.Position.iy();
	int radius = _Right.Scale.hix();
	int left = static_cast<int>(_Left.Left());
	int right = static_cast<int>(_Left.Right());
	int top = static_cast<int>(_Left.Top());
	int bottom = static_cast<int>(_Left.Bot());
	if ((left <= x && x < right) || (top <= y && y < bottom))
	{
		if (!(
			(y + radius <= top)
			|| (y - radius >= bottom)
			|| (x + radius <= left)
			|| (x - radius >= right)
			))
			return true;
	}
	else
	{
		if (
			((Distance({ x, y }, { right, top }) <= radius) && (x >= right && y <= top))
			|| ((Distance({ x, y }, { right, bottom }) <= radius) && (x >= right && y >= bottom))
			|| ((Distance({ x, y }, { left, top }) <= radius) && (x <= left && y <= top))
			|| ((Distance({ x, y }, { left, bottom }) <= radius) && (x <= left && y >= bottom))
			)
			return true;
	}
	return false;
}
bool GameEngineCollision::CollisionCirCleToRect(const CollisionData& _Left, const CollisionData& _Right)
{
	return CollisionRectToCirCle(_Right, _Left);
}




void GameEngineCollision::SetOrder(int _Order)
{
	GameEngineComponent::SetOrder(_Order);
	GetActor()->GetLevel()->PushCollision(this);
}

bool GameEngineCollision::Collision(const CollisionCheckParameter& _Parameter)
{
	if (false == IsUpdate())
	{
		return false;
	}

	std::list<GameEngineCollision*>& _TargetGroup = GetActor()->GetLevel()->Collisions[_Parameter.TargetGroup];

	for (GameEngineCollision* OtherCollision : _TargetGroup)
	{
		if (OtherCollision == this)
		{
			continue;
		}

		if (false == OtherCollision->IsUpdate())
		{
			continue;
		}

		CollisionType Type = _Parameter.ThisColType;
		CollisionType OtherType = _Parameter.TargetColType;

		if (nullptr == ColFunctionPtr[Type][OtherType])
		{
			MsgAssert("아직 충돌함수를 만들지 않은 충돌 타입입니다");
		}

		if (true == ColFunctionPtr[Type][OtherType](GetCollisionData(), OtherCollision->GetCollisionData()))
		{
			return true;
		}
	}
	return false;
}

bool GameEngineCollision::Collision(const CollisionCheckParameter& _Parameter, std::vector<GameEngineCollision*>& _Collision)
{
	if (false == IsUpdate())
	{
		return false;
	}

	_Collision.clear();

	std::list<GameEngineCollision*>& _TargetGroup = GetActor()->GetLevel()->Collisions[_Parameter.TargetGroup];

	SetDebugRenderType(_Parameter.ThisColType);

	for (GameEngineCollision* OtherCollision : _TargetGroup)
	{
		if (false == OtherCollision->IsUpdate())
		{
			continue;
		}

		CollisionType Type = _Parameter.ThisColType;
		CollisionType OtherType = _Parameter.TargetColType;

		OtherCollision->SetDebugRenderType(OtherType);

		if (nullptr == ColFunctionPtr[Type][OtherType])
		{
			MsgAssert("아직 충돌함수를 만들지 않은 충돌 타입입니다");
		}

		if (true == ColFunctionPtr[Type][OtherType](GetCollisionData(), OtherCollision->GetCollisionData()))
		{
			_Collision.push_back(OtherCollision);
		}
	}

	return _Collision.size() != 0;
}

CollisionData GameEngineCollision::GetCollisionData()
{
	return { GetActorPlusPos(), GetScale() };
}

void GameEngineCollision::DebugRender()
{
	HDC BackBufferDc = GameEngineWindow::GetDoubleBufferImage()->GetImageDC();
	float4 DebugRenderPos = GetActorPlusPos() - GetActor()->GetLevel()->GetCameraPos();
	switch (DebugRenderType)
	{
	case CT_Point:
		break;
	case CT_CirCle:
	{
		int Radius = GetScale().hix();
		Ellipse(BackBufferDc,
			DebugRenderPos.ix() - Radius,
			DebugRenderPos.iy() - Radius,
			DebugRenderPos.ix() + Radius,
			DebugRenderPos.iy() + Radius);
		break;
	}
	case CT_Rect:
	{
		Rectangle(BackBufferDc,
			DebugRenderPos.ix() - GetScale().hix(),
			DebugRenderPos.iy() - GetScale().hiy(),
			DebugRenderPos.ix() + GetScale().hix(),
			DebugRenderPos.iy() + GetScale().hiy());
		break;
	}
	case CT_Max:
		break;
	default:
		break;
	}
}