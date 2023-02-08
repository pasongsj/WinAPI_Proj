#include "GameEngineMath.h"
#include "GameEngineString.h"
#include "GameEngineDebug.h"

const float GameEngineMath::PIE = 3.141592653589793238462643383279502884197169399375105820974944f;
const float GameEngineMath::PIE2 = PIE * 2.0f;

const float4 float4::Left	   = {-1.0f, 0.0f, 0.0f, 1.0f};
const float4 float4::Right	   = {1.0f, 0.0f, 0.0f, 1.0f };
const float4 float4::Up		   = { 0.0f, -1.0f, 0.0f, 1.0f };
const float4 float4::Down	   = { 0.0f, 1.0f, 0.0f, 1.0f };


const float4 float4::Forward   = { 0.0f, 0.0f, 1.0f, 1.0f };
const float4 float4::Back	   = { 0.0f, 0.0f, -1.0f, 1.0f };

const float4 float4::Zero = { 0.0f, 0.0f, 0.0f, 1.0f };
const float4 float4::Null = { 0.0f, 0.0f, 0.0f, 0.0f };

std::vector<unsigned int> GameEngineMath::GetDigits(int _Value)
{
	std::vector<unsigned int> ResultValue = std::vector<unsigned int>();

	std::string StringValue = GameEngineString::ToString(_Value);

	int StartIndex = 0;

	if (0 != StringValue.size() && StringValue[0] == '-')
	{
		StartIndex = 1;
	}

	ResultValue.reserve(StringValue.size());

	for (size_t i = StartIndex; i < StringValue.size(); i++)
	{
		ResultValue.push_back(StringValue[i] - '0');
	}

	return ResultValue;
}
//
//std::vector<unsigned int> GameEngineMath::GetZeroDigits(int _Value, int _Digits)
//{
//	std::vector<unsigned int> ResultVal = std::vector<unsigned int>();
//
//	std::string StringVal = GameEngineString::ToString(_Value);
//
//	int StartIndex = 0;
//
//	if (0 != StringVal.size() && StringVal[0] == '-')
//	{
//		StartIndex = 1;
//	}
//	if (-1 == _Digits) {
//		_Digits = StringVal.length();
//	}
//	if (StringVal.length() > _Digits) {
//		MsgAssert("지정한 Digits보다 값이 큽니다.");
//	}
//
//	ResultVal.reserve(_Digits);
//
//	for (size_t i = StartIndex; i < _Digits- StringVal.size() + StartIndex; i++)
//	{
//		ResultVal.push_back('0');
//	}
//	int a = 0;
//	for (size_t i = _Digits - StringVal.size() + StartIndex; i < StringVal.size(); i++)
//	{
//		ResultVal.push_back(StringVal[i] - '0');
//	}
//
//	return ResultVal;
//}


unsigned int GameEngineMath::GetLenth(int _Value)
{
	std::vector<unsigned int> ResultValue = std::vector<unsigned int>();

	std::string StringValue = GameEngineString::ToString(abs(_Value));

	return static_cast<unsigned int>(StringValue.size());
}