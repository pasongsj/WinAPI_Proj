#pragma once
#include <GameEngineCore/GameEngineActor.h>

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

private:

};

