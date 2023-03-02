#pragma once
#include <GameEngineCore/GameEngineActor.h>
#include <GameEngineCore/Button.h>

class AdditionItemUI : public GameEngineActor
{
public:
	static AdditionItemUI* SelectUI;
	// constrcuter destructer
	AdditionItemUI() ;
	~AdditionItemUI();

	// delete Function
	AdditionItemUI(const AdditionItemUI& _Other) = delete;
	AdditionItemUI(AdditionItemUI&& _Other) noexcept = delete;
	AdditionItemUI& operator=(const AdditionItemUI& _Other) = delete;
	AdditionItemUI& operator=(AdditionItemUI&& _Other) noexcept = delete;


	void ReSetOff()
	{
		IsReset = false;
	}

	void UIOn();
	void UIOff();

protected:

	void Start() override;
	void Update(float _DeltaTime) override;

private:
	bool IsReset = false;

	std::vector<Button*> Items;
	std::vector<std::string> LevelupItems;
	float4 BtnScale = float4{ 456,127, };
	std::vector<float4> BtnPos;
	GameEngineRender* LevelUpUIRender = nullptr;
	GameEngineRender* StatUI = nullptr;

	void ReSet();

};

