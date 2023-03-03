#pragma once
#include <set>
#include <GameEngineCore/GameEngineLevel.h>
#include <GameEngineCore/GameEngineResources.h>

// 화려한 도서관 스테이지
class PlayGameUI;
class InlaidLibraryBack;
class Button;
class InlaidLibraryLevel : public GameEngineLevel
{
public:

	// constrcuter destructer
	InlaidLibraryLevel() ;
	~InlaidLibraryLevel();

	// delete Function
	InlaidLibraryLevel(const InlaidLibraryLevel& _Other) = delete;
	InlaidLibraryLevel(InlaidLibraryLevel&& _Other) noexcept = delete;
	InlaidLibraryLevel& operator=(const InlaidLibraryLevel& _Other) = delete;
	InlaidLibraryLevel& operator=(InlaidLibraryLevel&& _Other) noexcept = delete;

protected:
	void Loading() override;
	void Update(float _DeltaTime) override;

	void LevelChangeEnd(GameEngineLevel* _NextLevel) override;
	void LevelChangeStart(GameEngineLevel* _PrevLevel) override;

	GameEngineSoundPlayer BGMPlayer;

private:
	float LevelTime = 0.0f;
	float MonsterReGenTime = 0.0f;

	float RegenInterval = 0.0f;
	int MaxMonster = 0;

	std::set<std::string> SponableMonster;

	float4 BGSize = float4::Zero;
	void ImageLoad();
	void SoundLoad();
	PlayGameUI* NewUI = nullptr;
	InlaidLibraryBack* BackGround = nullptr;

	void ReGenMonster(float _DeltaTime);
	void SetState(float _DeltaTime);

	void CheckEnd();

	Button* BackButton = nullptr;
};

