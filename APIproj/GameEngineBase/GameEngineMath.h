#pragma once

// 설명 :
class GameEngineMath
{
public:
	static const float PIE;
	static const float PIE2;

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

public:
	float x = 0.0f;
	float y = 0.0f;
	float z = 0.0f;
	float w = 1.0f;
	// 마지막이 1인지는 3d 때 배우게 될겁니다.

	int ix() {
		return static_cast<int>(x);
	}

	int iy() {
		return static_cast<int>(y);
	}

	int iz() {
		return static_cast<int>(z);
	}

	int iw() {
		return static_cast<int>(w);
	}

};