#pragma once
#include <GameEngineCore/GameEngineLevel.h>

// stage로 들어갈 때 화면 전환 level
class OpenningLevel : public GameEngineLevel
{
public:
	// constrcuter destructer
	OpenningLevel() ;
	~OpenningLevel();

	// delete Function
	OpenningLevel(const OpenningLevel& _Other) = delete;
	OpenningLevel(OpenningLevel&& _Other) noexcept = delete;
	OpenningLevel& operator=(const OpenningLevel& _Other) = delete;
	OpenningLevel& operator=(OpenningLevel&& _Other) noexcept = delete;

protected:
	void Loading() override;
	void Update() override;

private:

};

