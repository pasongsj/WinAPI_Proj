#pragma once
#include <GameEngineCore/GameEngineActor.h>

class PlayGameUI : public GameEngineActor
{
public:
	// constrcuter destructer
	PlayGameUI() ;
	~PlayGameUI();

	// delete Function
	PlayGameUI(const PlayGameUI& _Other) = delete;
	PlayGameUI(PlayGameUI&& _Other) noexcept = delete;
	PlayGameUI& operator=(const PlayGameUI& _Other) = delete;
	PlayGameUI& operator=(PlayGameUI&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;

private:
	GameEngineRender* UIRender = nullptr;
};

