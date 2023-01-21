#pragma once
#include <GameEngineCore/GameEngineActor.h>
// Ό³Έν :
class TitleSubBack : public GameEngineActor
{
public:
	// constrcuter destructer
	TitleSubBack();
	~TitleSubBack();

	// delete Function
	TitleSubBack(const TitleSubBack& _Other) = delete;
	TitleSubBack(TitleSubBack&& _Other) noexcept = delete;
	TitleSubBack& operator=(const TitleSubBack& _Other) = delete;
	TitleSubBack& operator=(TitleSubBack&& _Other) noexcept = delete;

protected:
	void Start() override;

private:

};

