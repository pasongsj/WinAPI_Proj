#pragma once
#include <Windows.h>
#include <assert.h>
#include <string>

// 설명 :
class GameEngineDebug
{
public:

	// delete Function
	GameEngineDebug(const GameEngineDebug& _Other) = delete;
	GameEngineDebug(GameEngineDebug&& _Other) noexcept = delete;
	GameEngineDebug& operator=(const GameEngineDebug& _Other) = delete;
	GameEngineDebug& operator=(GameEngineDebug&& _Other) noexcept = delete;

	static void LeakCheck();

protected:

private:
	// constrcuter destructer
	GameEngineDebug();
	~GameEngineDebug();

};

// MessageBoxA 메시지박스를 띄워주는 기능,  assert 오류를 검출하기 위해 추가
#define MsgAssert(MsgText) std::string ErrorText = MsgText; MessageBoxA(nullptr, ErrorText.c_str(), "Error", MB_OK); assert(false);
