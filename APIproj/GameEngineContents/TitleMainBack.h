#pragma once
#include <GameEngineCore/GameEngineActor.h>
// Ό³Έν :
class TitleMainBack : public GameEngineActor
{
public:
	// constrcuter destructer
	TitleMainBack();
	~TitleMainBack();

	// delete Function
	TitleMainBack(const TitleMainBack& _Other) = delete;
	TitleMainBack(TitleMainBack&& _Other) noexcept = delete;
	TitleMainBack& operator=(const TitleMainBack& _Other) = delete;
	TitleMainBack& operator=(TitleMainBack&& _Other) noexcept = delete;

protected:
	void Start() override;

private:

};

