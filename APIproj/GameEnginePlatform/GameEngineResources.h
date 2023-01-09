#pragma once
class GameEngineResources
{
public:
	// constrcuter destructer
	GameEngineResources() ;
	~GameEngineResources();

	// delete Function
	GameEngineResources(const GameEngineResources& _Other) = delete;
	GameEngineResources(GameEngineResources&& _Other) noexcept = delete;
	GameEngineResources& operator=(const GameEngineResources& _Other) = delete;
	GameEngineResources& operator=(GameEngineResources&& _Other) noexcept = delete;

protected:

private:

};

