#pragma once
#include <GameEngineCore/GameEngineActor.h>


class Button;
class SelectCharacter : public GameEngineActor
{
public:
	// constrcuter destructer
	SelectCharacter() ;
	~SelectCharacter();

	// delete Function
	SelectCharacter(const SelectCharacter& _Other) = delete;
	SelectCharacter(SelectCharacter&& _Other) noexcept = delete;
	SelectCharacter& operator=(const SelectCharacter& _Other) = delete;
	SelectCharacter& operator=(SelectCharacter&& _Other) noexcept = delete;

	void Activate();

protected:
	void Start() override;
	void Update(float _DeltaTime) override;

private:
	std::vector<Button*> CharacterButton;
	GameEngineRender* Screen = nullptr;
};

