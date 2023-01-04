#pragma once

// 설명 :
class GameEngineLevel // 띄우는 화면을 의미한다.
{
public:
	// constrcuter destructer
	GameEngineLevel();
	virtual ~GameEngineLevel() = 0; //순수가상함수

	// delete Function
	GameEngineLevel(const GameEngineLevel& _Other) = delete;
	GameEngineLevel(GameEngineLevel&& _Other) noexcept = delete;
	GameEngineLevel& operator=(const GameEngineLevel& _Other) = delete;
	GameEngineLevel& operator=(GameEngineLevel&& _Other) noexcept = delete;

protected:

private:

};

