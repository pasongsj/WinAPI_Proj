#pragma once
#include <vector>

#include "GameEngineObject.h"
#include "GameEngineRender.h"

enum class Align
{
	Left,
	Right,
	Center
};

class GameEngineActor;
class NumberRenderObject : public GameEngineObject
{
public:
	// constrcuter destructer
	NumberRenderObject() ;
	~NumberRenderObject();

	// delete Function
	NumberRenderObject(const NumberRenderObject& _Other) = delete;
	NumberRenderObject(NumberRenderObject&& _Other) noexcept = delete;
	NumberRenderObject& operator=(const NumberRenderObject& _Other) = delete;
	NumberRenderObject& operator=(NumberRenderObject&& _Other) noexcept = delete;

	void SetImage(const std::string_view& _ImageName, float4 _Scale, int _Order, int _TransColor, const std::string_view& _NegativeName = "");
	void SetValue(int _Value);

	//void SetMove(float4 _RenderPos);
	void SetAlign(Align _Align);

	inline int GetValue()
	{
		return Value;
	}

	inline void SetRenderPos(const float4& _Pos) {
		Pos = _Pos;
	}

	void SetCameraEffect(bool _EffectSetting)
	{
		CameraEffect = _EffectSetting;
	}

	inline void SetNumOfDigits(int _Num) {
		NumOfDigits = _Num;
	}

	inline void ResetDigits() { // 숫자길이 리셋 (Value만큼 랜더)
		SetNumOfDigits(-1);
	}

protected:

private:
	int Order = 0;
	float4 NumberScale = {};
	float4 Pos = {};
	int Value = 0;
	int TransColor = RGB(255, 0, 255);
	Align AlignState = Align::Left;
	// GameEngineImage* NumberImage;
	bool Negative = false;

	int NumOfDigits = -1;

	bool CameraEffect = false;

	std::string_view ImageName = std::string_view();

	std::string_view NegativeName = std::string_view();

	std::vector<GameEngineRender*> NumberRenders = std::vector<GameEngineRender*>();
	GameEngineRender* NegativeRender = nullptr;

	void SetNumberRenders(size_t _Index, int _TransColor, float4 _Pos, const std::string_view& _ImageName, float4 _Scale, bool _CameraEffect, int _Frame = -1);

};