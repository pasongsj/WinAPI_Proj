#pragma once
#include <cmath>
#include <vector>
#include <string>
#include <windows.h>


// 설명 : 1. 수학과 물리에 관련된 내용을 처리할 수 있도록 하였다.
//		A.위치와 크기 같은 기하학적 요소
//		B.삼각함수 연산

// 
// final 더이상 상속내릴지 못한다.
// 상속도 못하고 만들지도 못하게 만든 상태로

class GameEngineMath final // final은 상속, override를 막는다.
{
public:
	static std::vector<unsigned int> GetDigits(int _Value);
	static unsigned int GetLenth(int _Value);
	static const float PIE;
	static const float PIE2; // pie * 2
	static const float DegToRad;
	static const float RadToDeg;

private:
	virtual ~GameEngineMath() = 0;
};

class float4
{
public:
	static const float4 Left;
	static const float4 Right;
	static const float4 Up;
	static const float4 Down;
	static const float4 Forward;
	static const float4 Back;
	static const float4 Zero;
	static const float4 Null;

	static float4 AngleToDirection2DToDeg(float _Deg)
	{
		return AngleToDirection2DToRad(_Deg * GameEngineMath::DegToRad);
	}

	static float4 AngleToDirection2DToRad(float _Rad)
	{
		return float4(cosf(_Rad), sinf(_Rad), 0.0f, 1.0f);
	}

public:
	float x = 0.0f;
	float y = 0.0f;
	float z = 0.0f;
	float w = 1.0f;
	// 마지막이 1인지는 3d 때 배우게 될겁니다.
	// half 실수값 
	float hx() const
	{
		return (x * 0.5f);
	}

	float hy() const
	{
		return (y * 0.5f);
	}

	float hz() const
	{
		return (z * 0.5f);
	}

	float hw() const
	{
		return (w * 0.5f);
	}
	// 정수 값
	int ix() const
	{
		return static_cast<int>(x);
	}

	int iy() const 
	{
		return static_cast<int>(y);
	}

	int iz() const 
	{
		return static_cast<int>(z);
	}

	int iw() const 
	{
		return static_cast<int>(w);
	}

	// half 정수 값
	int hix() const
	{
		return static_cast<int>(x * 0.5f);
	}

	int hiy() const
	{
		return static_cast<int>(y * 0.5f);
	}

	int hiz() const
	{
		return static_cast<int>(z * 0.5f);
	}

	int hiw() const
	{
		return static_cast<int>(w * 0.5f);
	}

	float4 half() const
	{
		return {x * 0.5f,y * 0.5f,z * 0.5f,w};
	}

	// Degree


	float GetAngleDeg()
	{
		return GetAngleRad() * GameEngineMath::RadToDeg;
	}

	void RotaitonZDeg(float _Deg)
	{
		RotaitonZRad(_Deg * GameEngineMath::DegToRad);
	}

	void RotaitonZRad(float _Rad)
	{
		float4 Copy = *this;
		x = Copy.x * cosf(_Rad) - Copy.y * sinf(_Rad);
		y = Copy.x * sinf(_Rad) + Copy.y * cosf(_Rad);
	}

	float4 RotaitonZDegReturn(float _Deg)
	{
		float4 Copy = *this;
		Copy.RotaitonZDeg(_Deg);
		return Copy;
	}

	float GetAngleRad()
	{
		float4 AngleCheck = (*this);
		AngleCheck.Normalize();

		float Result = acosf(AngleCheck.x);

		if (AngleCheck.y > 0)
		{
			Result = GameEngineMath::PIE2 - Result;
		}
		return Result;

	}

	float GetAngelBetweenVec(float4 _Vec)
	{
		float diff = x * _Vec.x + y * _Vec.y;
		float m_fAngle = acos(diff/Size()*_Vec.Size());

		if (_Vec.y > 0) // *this = float4{1, 0}
		{
			return m_fAngle;
		}
		else
		{
			return -m_fAngle;
		}

	}
	
	//windows 변수로 변경
	POINT ToWindowPOINT()
	{
		return POINT(ix(), iy());
	}

	// vector크기가 0인지 확인
	bool IsZero() const
	{
		return x == 0.0f && y == 0.0f && z == 0.0f;
	}

	float Size() const
	{
		return sqrtf(x * x + y * y);
	}

	void Normalize()
	{
		float SizeValue = Size();
		x /= SizeValue;
		y /= SizeValue;
		z /= SizeValue;
	}

	float4 GetNormalize()
	{
		float4 ReturnVal = *this;
		ReturnVal.Normalize();
		return ReturnVal;
	}
	

	static float4 Lerp(const float4& Start, const float4& End, float Ratio)
	{
		// 1.5 + 0.5 * 2.5;
		return Start * (1.0f - Ratio) + (End * Ratio);
	}

	static float4 LerpClamp(const float4& Start, const float4& End, float Ratio)
	{
		if (0 >= Ratio)
		{
			Ratio = 0.0f;
		}

		if (1.0f <= Ratio)
		{
			Ratio = 1.0f;
		}

		return Lerp(Start, End, Ratio);
	}

	// operator
	//산술 연산자
	float4 operator +(const float4 _Value) const
	{
		float4 Return;
		Return.x = x + _Value.x;
		Return.y = y + _Value.y;
		Return.z = z + _Value.z;
		return Return;
	}

	float4 operator -(const float4 _Value) const
	{
		float4 Return;
		Return.x = x - _Value.x;
		Return.y = y - _Value.y;
		Return.z = z - _Value.z;
		return Return;
	}

	float4 operator *(const float _Value) const
	{
		float4 Return;
		Return.x = x * _Value;
		Return.y = y * _Value;
		Return.z = z * _Value;
		return Return;
	}

	float4 operator /(const float4 _Value) const
	{
		float4 Return;
		Return.x = x / _Value.x;
		Return.y = y / _Value.y;
		Return.z = z / _Value.z;
		return Return;
	}

	//할당 연산자
	float4& operator +=(const float4& _Other) 
	{
		x += _Other.x;
		y += _Other.y;
		z += _Other.z;
		return *this;
	}

	float4& operator -=(const float4& _Other)
	{
		x -= _Other.x;
		y -= _Other.y;
		z -= _Other.z;
		return *this;
	}

	float4& operator *=(const float _Other)
	{
		x *= _Other;
		y *= _Other;
		z *= _Other;
		return *this;
	}

	float4& operator /=(const float4& _Other)
	{
		x /= _Other.x;
		y /= _Other.y;
		z /= _Other.z;
		return *this;
	}

	float4& operator /=(const float& _Other)
	{
		x /= _Other;
		y /= _Other;
		z /= _Other;
		return *this;
	}

	//단항 연산자
	float4 operator -() const
	{
		return { -x, -y, -z, 1.0f };
	}
	
	//비교 연산자
	bool operator ==(const float4& _Other) const
	{
		return x == _Other.x && y == _Other.y && z == _Other.z;
	}
	bool operator !=(const float4& _Other) const
	{
		return !(*this == _Other);
	}

	std::string ToString()
	{
		char ArrReturn[256];

		sprintf_s(ArrReturn, "x: %f, y: %f, z: %f, w: %f", x, y, z, w);

		return std::string(ArrReturn);
	}
};



class CollisionData
{
public:
	float4 Position;
	float4 Scale; // x만 원의 반지름으로 보겠습니다.

	float Left() const
	{
		return Position.x - Scale.hx();
	}
	float Right() const
	{
		return Position.x + Scale.hx();
	}
	float Top() const
	{
		return Position.y - Scale.hy();
	}
	float Bot() const
	{
		return Position.y + Scale.hy();
	}

	float4 LeftTop() const
	{
		return float4{ Left(), Top() };
	}
	float4 RightTop() const
	{
		return float4{ Right(), Top() };
	}
	float4 LeftBot() const
	{
		return float4{ Left(), Bot() };
	}
	float4 RightBot() const
	{
		return float4{ Right(), Bot() };
	}
};