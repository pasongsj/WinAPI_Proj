#pragma once
#include <string>
#include <string_view>

// 설명 : 	std::String과 관련된 내용이다.
class GameEngineString
{
public:
	static std::string ToUpper(const std::string_view& _Str);			// 파일이름을 관리할 때 대소문자를 구분하기 때문에 일괄적으로 대문자로 변환하여 사용하였다.
	static std::string ToString(int Value);								// 수치를 화면에 띄우기 위해 디버깅용으로 추가하였다

	// 멀티바이트(anti), 유니코드, UTF변환
	// fmod를 사용할 때 사용
	static std::wstring AnsiToUniCode(const std::string_view& _Text); // string_view로 받는 이유는 string에 비해 비교적 작은 메모리를 사용하기 때문에
	static std::string UniCodeToAnsi(const std::wstring_view& _Text);

	static std::string UniCodeToUTF8(const std::wstring_view& _Text);
	static std::string AnsiToUTF8(const std::string_view& _Text);


protected:

private:
	// constrcuter destructer
	GameEngineString();
	~GameEngineString();
	// delete Function
	GameEngineString(const GameEngineString& _Other) = delete;
	GameEngineString(GameEngineString&& _Other) noexcept = delete;
	GameEngineString& operator=(const GameEngineString& _Other) = delete;
	GameEngineString& operator=(GameEngineString&& _Other) noexcept = delete;
};

