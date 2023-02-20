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
	void Disable();

protected:
	void Start() override;
	void Update(float _DeltaTime) override;

private:
	std::vector<Button*> CharacterButton;
	float4 ButtonPos = { 516, 300 }; // 168씩 차이남
	std::vector<std::string> CharName;
	int ClickIndex = -1;

	void SetNextBtnPos();
	Button* BackBtn = nullptr;
	//GameEngineRender* Screen = nullptr;
};

