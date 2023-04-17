#pragma once
#include <string>
#include <string_view>

// ���� : 	std::String�� ���õ� �����̴�.
class GameEngineString
{
public:
	static std::string ToUpper(const std::string_view& _Str);			// �����̸��� ������ �� ��ҹ��ڸ� �����ϱ� ������ �ϰ������� �빮�ڷ� ��ȯ�Ͽ� ����Ͽ���.
	static std::string ToString(int Value);								// ��ġ�� ȭ�鿡 ���� ���� ���������� �߰��Ͽ���

	// ��Ƽ����Ʈ(anti), �����ڵ�, UTF��ȯ
	// fmod�� ����� �� ���
	static std::wstring AnsiToUniCode(const std::string_view& _Text); // string_view�� �޴� ������ string�� ���� ���� ���� �޸𸮸� ����ϱ� ������
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

