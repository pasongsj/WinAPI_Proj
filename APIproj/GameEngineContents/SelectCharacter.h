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

	static SelectCharacter* MainScreen;
	
	Button* GetBackBtn() {
		return BackBtn;
	}
	std::vector<Button*> GetCharacterButtons()
	{
		return CharacterButtons;
	}

protected:
	void Start() override;


private:
	float4 ButtonPos = { 516, 300 }; // 168씩 차이남
	Button* BackBtn = nullptr; // 나가기버튼

	std::vector<std::string> CharName; // 캐릭터 이름
	std::vector<Button*> CharacterButtons; // 캐릭터 선택 버튼

	void SetNextBtnPos();
};