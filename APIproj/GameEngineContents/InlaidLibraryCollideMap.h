#pragma once
#include <GameEngineCore/GameEngineActor.h>
// Ό³Έν :
class InlaidLibraryCollideMap : public GameEngineActor
{
public:
	// constrcuter destructer
	InlaidLibraryCollideMap();
	~InlaidLibraryCollideMap();

	// delete Function
	InlaidLibraryCollideMap(const InlaidLibraryCollideMap& _Other) = delete;
	InlaidLibraryCollideMap(InlaidLibraryCollideMap&& _Other) noexcept = delete;
	InlaidLibraryCollideMap& operator=(const InlaidLibraryCollideMap& _Other) = delete;
	InlaidLibraryCollideMap& operator=(InlaidLibraryCollideMap&& _Other) noexcept = delete;

protected:
	void Start() override;

private:

};

