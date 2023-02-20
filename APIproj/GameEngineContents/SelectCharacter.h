#pragma once
//#include <string>
#include <GameEngineCore/Button.h>
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

	static std::vector<Button*> CharacterButton;
	static SelectCharacter* MainScreen;
	
	Button* GetBackBtn() {
		return BackBtn;
	}

protected:
	void Start() override;
	void Update(float _DeltaTime) override;

private:
	float4 ButtonPos = { 516, 300 }; // 168씩 차이남
	std::vector<std::string> CharName;
	void SetNextBtnPos();
	Button* BackBtn = nullptr;
	//GameEngineRender* Screen = nullptr;
};