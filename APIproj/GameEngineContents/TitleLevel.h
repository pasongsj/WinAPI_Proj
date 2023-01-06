#pragma once
#include <GameEngineCore/GameEngineLevel.h>

// ���� �� ���̴� Ÿ��Ʋ ������
class TitleLevel : public GameEngineLevel
{
public:
	// constrcuter destructer
	TitleLevel() ;
	~TitleLevel();

	// delete Function
	TitleLevel(const TitleLevel& _Other) = delete;
	TitleLevel(TitleLevel&& _Other) noexcept = delete;
	TitleLevel& operator=(const TitleLevel& _Other) = delete;
	TitleLevel& operator=(TitleLevel&& _Other) noexcept = delete;

protected:
	void Loading() override;
	void Update() override;

private:

};

