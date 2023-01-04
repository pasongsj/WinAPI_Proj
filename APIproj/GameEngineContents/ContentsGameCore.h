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

	// 싱글톤 방식
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
	// 왜? private? -> core를 한개 쓸거기 때문에 추가 core생성을 막는 역할을 한다.
	ContentsGameCore();
	~ContentsGameCore();
	// 오직 1개의 객체만 만들어진다
	static ContentsGameCore Core;
};

