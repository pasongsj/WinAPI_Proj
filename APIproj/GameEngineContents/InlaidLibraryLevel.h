#pragma once
#include <set>
#include <GameEngineCore/GameEngineLevel.h>
#include <GameEngineCore/GameEngineResources.h>

// 화려한 도서관 스테이지
class PlayGameUI;
class InlaidLibraryBack;
class Button;
class ObtainBox;
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
	int NextSettingTime = 0;

	float LastReGenTime = 0.0f;

	float RegenInterval = 0.0f;
	int MaxMonster = 0;

	std::vector<std::string> SponableMonster;

	float4 BGSize = float4::Zero;
	void ImageLoad();
	void SoundLoad();
	PlayGameUI* NewUI = nullptr;
	InlaidLibraryBack* BackGround = nullptr;

	//ObtainBox* ObtainBoxUI = nullptr;

	void ReGenMonster();
	void SetState();

	void CheckEnd();

	Button* BackButton = nullptr;

	void CheckLevelUpUI();

	//void CheckBoxOpenUI();

	void CheckDebugInput();

	void ControlTimeScale();
};

