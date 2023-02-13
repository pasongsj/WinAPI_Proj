#pragma once
#include <GameEngineCore/GameEngineLevel.h>

// 화려한 도서관 스테이지
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

	void LevelChangeEnd(GameEngineLevel* _NextLevel) override {}
	void LevelChangeStart(GameEngineLevel* _PrevLevel) override;
private:

	float4 BGSize = float4::Zero;
	void ImageLoad();
};

