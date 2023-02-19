#pragma once
#include <GameEngineCore/GameEngineLevel.h>
#include <GameEngineCore/GameEngineResources.h>

// ���� �� ���̴� Ÿ��Ʋ ������
class SelectCharacter;
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

	static SelectCharacter* SelectScreen;


protected:
	void Loading() override;
	void Update(float _DeltaTime) override;

	void LevelChangeEnd(GameEngineLevel* _NextLevel) override {}
	void LevelChangeStart(GameEngineLevel* _PrevLevel);

	GameEngineSoundPlayer BGMPlayer;


private:
	void SoundLoad();
	void ImageLoad();


};

