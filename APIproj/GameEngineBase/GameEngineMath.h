#pragma once
#include <cmath>

// final 더이상 상속내릴지 못한다.
// 상속도 못하고 만들지도 못하게 만든 상태로

class GameEngineMath final // final은 상속, override를 막는다.
{
public:
	static const float PIE;
	static const float PIE2; // pie * 2

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
};