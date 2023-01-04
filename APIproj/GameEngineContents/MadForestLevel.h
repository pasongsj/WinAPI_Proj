#pragma once
#include <GameEngineCore/GameEngineLevel.h>

// ±¤±âÀÇ ½£ ½ºÅ×ÀÌÁö
class MadForestLevel : GameEngineLevel
{
public:
	// constrcuter destructer
	MadForestLevel() ;
	~MadForestLevel();

	// delete Function
	MadForestLevel(const MadForestLevel& _Other) = delete;
	MadForestLevel(MadForestLevel&& _Other) noexcept = delete;
	MadForestLevel& operator=(const MadForestLevel& _Other) = delete;
	MadForestLevel& operator=(MadForestLevel&& _Other) noexcept = delete;

protected:

private:

};

