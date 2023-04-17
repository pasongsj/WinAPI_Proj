#pragma once
#include <Windows.h>
#include <assert.h>
#include <string>

// ���� :1.	�߸��� ���ٿ� ���� ǥ�ð� �ʿ��ϴٰ� �����Ѵ�.
//		2.	�Ϲ����� �ܼ��ڵ��̶�� std::cout �Ǵ� printf�� ���� ������ Ȯ���� �� ������ winapi�� ����ϱ� ������ �޽����ڽ��� ��� �̸� �˷��ִ� ���� ���ٰ� �Ǵ��Ͽ���.
//		3.	�޽��� �ڽ��� ������ ����� �ڵ尡 �ߴܵǴ� ���� �ƴϱ� ������ ��������� �ڵ��� assert�Լ��� �߰��Ͽ���.

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

// MessageBoxA �޽����ڽ��� ����ִ� ���,  assert ������ �����ϱ� ���� �߰�
#define MsgAssert(MsgText) std::string ErrorText = MsgText; MessageBoxA(nullptr, ErrorText.c_str(), "Error", MB_OK); assert(false);
