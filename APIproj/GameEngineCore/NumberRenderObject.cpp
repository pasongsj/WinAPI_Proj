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


void NumberRenderObject::SetImage(const std::string_view& _ImageName, float4 _Scale, int _Order, int _TransColor)
{
	GameEngineImage* FindNumberImage = GameEngineResources::GetInst().ImageFind(_ImageName);

	// ������ ���� 0.bmp 1.bmp
	if (FindNumberImage->GetImageCuttingCount() != 10)
	{
		MsgAssert("���� �̹����� ������ 10���� ©���־�� �մϴ�.");
	}

	if (0 >= _Scale.x || 0 >= _Scale.y)
	{
		MsgAssert("ũ�Ⱑ 0���� ���ڸ� ����� �� �����ϴ�.");
	}

	ImageName = _ImageName;
	NumberScale = _Scale;
	Order = _Order;
	TransColor = _TransColor;
}
//
//void NumberRenderObject::SetValue(int _Value)
//{
//	Value = _Value;
//	std::vector<unsigned int> Numbers = GameEngineMath::GetDigits(Value);
//	/*if (NumOfDigits != 0) {
//		Numbers = GameEngineMath::GetDigits(Value, NumOfDigits);
//	}
//	else {
//		Numbers = GameEngineMath::GetDigits(Value);
//	}*/
//
//	GameEngineActor* Actor = GetOwner<GameEngineActor>();
//
//	if (nullptr == Actor)
//	{
//		MsgAssert("���͸��� NumberRenderObject�� �θ� �ɼ� �ֽ��ϴ�.");
//	}
//
//	if(-1 != NumOfDigits)
//	{
//		//            �ڸ����� �ٲ����                  3�ڸ� �����ϰ� �־��µ� 5�ڸ��� �ƴٸ�
//		if (NumberRenders.size() != Numbers.size() && NumberRenders.size() < Numbers.size())
//		{
//			size_t CurRenderSize = NumberRenders.size();
//			//                       5                   3
//			for (size_t i = 0; i < (Numbers.size() - CurRenderSize); i++)
//			{
//				NumberRenders.push_back(Actor->CreateRender(Order));
//			}
//		}
//	}
//	else 
//	{
//		for (size_t i = 0; i < (NumOfDigits); i++)
//		{
//			NumberRenders.push_back(Actor->CreateRender(Order));
//		}
//	}
//	// Pos
//
//	float4 RenderPos = float4::Zero;
//	int index = 0;
//	if (NumOfDigits > Numbers.size()) {
//		for (size_t i = 0; index < NumOfDigits - NumberRenders.size(); index++)
//		{
//			GameEngineRender* Render = NumberRenders[index];
//
//			if (nullptr == Render)
//			{
//				MsgAssert("���ڷ������� nullptr �Դϴ�");
//			}
//
//			Render->SetTransColor(TransColor);
//			Render->SetPosition(Pos + RenderPos);
//			Render->SetImage(ImageName);
//			Render->SetScale(NumberScale);
//			Render->SetFrame(0);
//			Render->EffectCameraOff();
//			RenderPos.x += NumberScale.x;
//		}
//	}
//
//	for (; index < NumberRenders.size(); index++)
//	{
//		GameEngineRender* Render = NumberRenders[index];
//
//		if (nullptr == Render)
//		{
//			MsgAssert("���ڷ������� nullptr �Դϴ�");
//		}
//
//		Render->SetTransColor(TransColor);
//		Render->SetPosition(Pos + RenderPos);
//		Render->SetImage(ImageName);
//		Render->SetScale(NumberScale);
//		Render->SetFrame(Numbers[index]);
//		Render->EffectCameraOff();
//		RenderPos.x += NumberScale.x;
//	}
//
//	switch (AlignState)
//	{
//	case Align::Left:
//		break;
//	case Align::Right:
//		SetMove(float4::Left * static_cast<const float>(GameEngineMath::GetLenth(Value) - 1) * NumberScale.x);
//		break;
//	case Align::Center:
//		SetMove((float4::Left * static_cast<const float>(GameEngineMath::GetLenth(Value) - 1) * NumberScale.x).half());
//		break;
//	default:
//		break;
//	}
//}

void NumberRenderObject::SetValue(int _Value)
{
	Value = _Value;

	std::vector<unsigned int> Numbers = GameEngineMath::GetDigits(Value);
	GameEngineActor* Actor = GetOwner<GameEngineActor>();

	if (nullptr == Actor)
	{
		MsgAssert("���͸��� NumberRenderObject�� �θ� �ɼ� �ֽ��ϴ�.");
	}

	if (-1 != NumOfDigits && Numbers.size() > NumOfDigits)
	{
		int a = 0;
		MsgAssert("NumOfDigits�� value�� ���� �۽��ϴ�.");
	}

	int Digits = (NumOfDigits == -1 ? Numbers.size() : NumOfDigits);
	
	//            �ڸ����� �ٲ����                  3�ڸ� �����ϰ� �־��µ� 5�ڸ��� �ƴٸ�
	if (NumberRenders.size() != Digits && NumberRenders.size() < Digits)
	{
		size_t CurRenderSize = NumberRenders.size();
		//                       5                   3
		for (size_t i = 0; i < (Digits - CurRenderSize); i++)
		{
			NumberRenders.push_back(Actor->CreateRender(Order));
		}
	}
	// Pos

	float4 RenderPos;

	size_t index = 0;
	for (; index < Digits - Numbers.size(); ++index) {
		GameEngineRender* Render = NumberRenders[index];

		if (nullptr == Render)
		{
			MsgAssert("���ڷ������� nullptr �Դϴ�");
		}

		Render->SetTransColor(TransColor);
		Render->SetPosition(Pos + RenderPos);
		Render->SetImage(ImageName);
		Render->SetScale(NumberScale);
		Render->SetFrame(0);
		Render->SetEffectCamera(CameraEffect);
		RenderPos.x += NumberScale.x;
	}
	
	for (int i = 0; index < NumberRenders.size(); ++index)
	{
		GameEngineRender* Render = NumberRenders[index];

		if (nullptr == Render)
		{
			MsgAssert("���ڷ������� nullptr �Դϴ�");
		}

		Render->SetTransColor(TransColor);
		Render->SetPosition(Pos + RenderPos);
		Render->SetImage(ImageName);
		Render->SetScale(NumberScale);
		Render->SetFrame(Numbers[i++]);
		Render->SetEffectCamera(CameraEffect);
		RenderPos.x += NumberScale.x;
	}

	switch (AlignState)
	{
	case Align::Left:
		break;
	case Align::Right:
		SetMove(float4::Left * static_cast<const float>(GameEngineMath::GetLenth(Value) - 1) * NumberScale.x);
		break;
	case Align::Center:
		SetMove((float4::Left * static_cast<const float>(GameEngineMath::GetLenth(Value) - 1) * NumberScale.x).half());
		break;
	default:
		break;
	}
}

void NumberRenderObject::SetMove(float4 _RenderPos)
{
	for (size_t i = 0; i < NumberRenders.size(); i++)
	{
		NumberRenders[i]->SetMove(_RenderPos);
	}
}


void NumberRenderObject::SetAlign(Align _Align)
{
	AlignState = _Align;
}
