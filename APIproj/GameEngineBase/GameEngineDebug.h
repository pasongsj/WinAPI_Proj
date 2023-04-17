#pragma once
#include <Windows.h>
#include <assert.h>
#include <string>

// 설명 :1.	잘못된 접근에 대한 표시가 필요하다고 생각한다.
//		2.	일반적인 콘솔코딩이라면 std::cout 또는 printf를 통해 문제를 확인할 수 있지만 winapi를 사용하기 때문에 메시지박스를 띄워 이를 알려주는 것이 좋다고 판단하였다.
//		3.	메시지 박스로 오류를 띄워도 코드가 중단되는 것이 아니기 때문에 에러검출용 코드인 assert함수를 추가하였다.

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
