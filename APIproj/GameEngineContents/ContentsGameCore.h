#pragma once
#include <GameEngineCore/GameEngineCore.h>

class ContentsGameCore : public GameEngineCore
{
public:
	// delete Function
	ContentsGameCore(const ContentsGameCore& _Other) = delete;
	ContentsGameCore(ContentsGameCore&& _Other) noexcept = delete;
	ContentsGameCore& operator=(const ContentsGameCore& _Other) = delete;
	ContentsGameCore& operator=(ContentsGameCore&& _Other) noexcept = delete;

	// �̱��� ���
	static ContentsGameCore& GetInst()
	{
		return Core;
	}

protected:
	void Start() override;
	void Update() override;
	void End() override;

private:
	// constrcuter destructer
	// ��? private? -> core�� �Ѱ� ���ű� ������ �߰� core������ ���� ������ �Ѵ�.
	ContentsGameCore();
	~ContentsGameCore();
	// ���� 1���� ��ü�� ���������
	static ContentsGameCore Core;
};

