#pragma once
#include <GameEngineCore/GameEngineActor.h>
#include <vector>
class InlaidLibraryBack  : public GameEngineActor
{
public:
	// constrcuter destructer
	InlaidLibraryBack() ;
	~InlaidLibraryBack();

	// delete Function
	InlaidLibraryBack(const InlaidLibraryBack& _Other) = delete;
	InlaidLibraryBack(InlaidLibraryBack&& _Other) noexcept = delete;
	InlaidLibraryBack& operator=(const InlaidLibraryBack& _Other) = delete;
	InlaidLibraryBack& operator=(InlaidLibraryBack&& _Other) noexcept = delete;

	void SetEndingRenderOn(bool _IsComplete);

protected:
	void Start() override;
	void Update(float _DeltaTime) override;
	     
private:
	//무한맵 이동을 위한 랜더
	GameEngineRender* MainBackGroundRender = nullptr;
	GameEngineRender* RemainBackGroundRender = nullptr;

	GameEngineRender* EndingRender = nullptr;
	GameEngineRender* EndingUI = nullptr;

	float4 BGSize = float4::Zero;
	float lim = 0;
	/*std::set<int> IsRanderPos;
	int RenPos;*/
};

