#include "NumberRenderObject.h"
#include "GameEngineResources.h"
#include "GameEngineActor.h"
#include <GameEngineBase/GameEngineString.h>


NumberRenderObject::NumberRenderObject()
{
}

NumberRenderObject::~NumberRenderObject()
{
}


void NumberRenderObject::SetImage(const std::string_view& _ImageName, float4 _Scale, int _Order, int _TransColor, const std::string_view& _NegativeName)
{
	GameEngineImage* FindNumberImage = GameEngineResources::GetInst().ImageFind(_ImageName);

	// 선생님 저는 0.bmp 1.bmp
	if (FindNumberImage->GetImageCuttingCount() != 10)
	{
		MsgAssert("숫자 이미지는 무조건 10개로 짤려있어야 합니다.");
	}

	if (0 >= _Scale.x || 0 >= _Scale.y)
	{
		MsgAssert("크기가 0으로 숫자를 출력할 수 없습니다.");
	}

	ImageName = _ImageName;
	NumberScale = _Scale;
	Order = _Order;
	TransColor = _TransColor;
	NegativeName = _NegativeName;
}

void NumberRenderObject::SetNumberRenders(size_t _Index, int _TransColor, float4 _Pos, const std::string_view& _ImageName, float4 _Scale, bool _CameraEffect, int _Frame)
{
	GameEngineRender* Render = NumberRenders[_Index];
	if (nullptr == Render)
	{
		MsgAssert("숫자랜더러가 nullptr 입니다");
	}
	Render->SetTransColor(_TransColor);
	Render->SetPosition(_Pos);
	Render->SetImage(_ImageName);
	Render->SetScale(_Scale);
	Render->SetEffectCamera(_CameraEffect);
	if (-1 != _Frame)
	{
		Render->SetFrame(_Frame);
	}
}

void NumberRenderObject::SetValue(int _Value)
{
	Value = _Value;

	std::vector<unsigned int> Numbers = GameEngineMath::GetDigits(Value);
	GameEngineActor* Actor = GetOwner<GameEngineActor>();

	if (nullptr == Actor)
	{
		MsgAssert("액터만이 NumberRenderObject의 부모가 될수 있습니다.");
	}

	if (-1 != NumOfDigits && Numbers.size() > NumOfDigits)
	{
		MsgAssert("NumOfDigits이 value값 보다 작습니다.");
	}

	if (-1 != NumOfDigits && Value < 0) //
	{
		ResetDigits(); // 음수면서 digits길이를 설정한 경우 
		MsgAssert("Value가 음수인 동시에 Digits길이가 설정되었습니다.");
	}

	Negative = _Value >= 0 ? false : true;

	size_t Digits = (NumOfDigits == -1 ? Numbers.size() : NumOfDigits);
	
	//            자리수가 바뀌었고                  3자리 랜더하고 있었는데 5자리가 됐다면
	if (NumberRenders.size() < Digits)
	{
		size_t CurRenderSize = NumberRenders.size();
		//                       5                   3
		for (size_t i = 0; i < (Digits - CurRenderSize); i++)
		{
			NumberRenders.push_back(Actor->CreateRender(Order));
		}
	}
	else // NumberRenders를 삭제 해야하는 경우  +)유지되는 경우
	{
		size_t CurRenderSize = NumberRenders.size();
		//                       5                   3
		for (size_t i = 0; i < (CurRenderSize - Digits); ++i)
		{
			GameEngineRender* LastRender = NumberRenders.back();
			NumberRenders.pop_back(); // 삭제되는지 체크 필요
			LastRender->Death();
		}
	}

	// Pos

	float4 RenderPos = Pos;
	size_t NumRenderIndex = 0;

	switch (AlignState)
	{
	case Align::Left:
		break;
	case Align::Right:
		RenderPos.x -= (Digits - 1) * NumberScale.x;
		break;
	case Align::Center:
		RenderPos.x -= ((Digits - 1) * NumberScale.x) / 2;
		break;
	default:
		break;
	}

	if (true == Negative && nullptr == NegativeRender)
	{
		SetNumberRenders(NumRenderIndex++, TransColor, RenderPos, NegativeName, NumberScale, CameraEffect);
		RenderPos.x += NumberScale.x;
	}
	for (; NumRenderIndex < Digits - Numbers.size(); ++NumRenderIndex)
	{
		SetNumberRenders(NumRenderIndex, TransColor, RenderPos, ImageName, NumberScale, CameraEffect, 0);
		RenderPos.x += NumberScale.x;
	}
	for (int i = 0; NumRenderIndex < NumberRenders.size(); ++NumRenderIndex)
	{
		SetNumberRenders(NumRenderIndex, TransColor, RenderPos, ImageName, NumberScale, CameraEffect, Numbers[i++]);
		RenderPos.x += NumberScale.x;
	}
}

//void NumberRenderObject::SetMove(float4 _RenderPos)
//{
//	for (size_t i = 0; i < NumberRenders.size(); i++)
//	{
//		NumberRenders[i]->SetMove(_RenderPos);
//	}
//}


void NumberRenderObject::SetAlign(Align _Align)
{
	AlignState = _Align;
	SetValue(Value);
}
