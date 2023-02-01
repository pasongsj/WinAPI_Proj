#pragma once
#include <GameEngineCore/GameEngineActor.h>
#include <set>
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

protected:
	void Start() override;
	void Update(float _DeltaTime) override;
	     
private:
	float4 BGSize = float4::Zero;
	std::set<int> IsRanderPos;
	int RenPos;
};

