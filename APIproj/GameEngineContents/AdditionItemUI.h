#pragma once
#include <set>
#include <unordered_map>
#include <GameEngineCore/GameEngineActor.h>
#include <GameEngineCore/Button.h>

class AdditionItemUI : public GameEngineActor
{
public:
	static std::string DeleteItemName;
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


	std::map<std::string, std::string> ItemNames;

	std::map<std::string, Button*> Items;
	std::map<std::string, Button*> DeletedItem;


	float4 BtnScale = float4{ 456,127, };
	std::vector<float4> BtnPos;
	GameEngineRender* LevelUpUIRender = nullptr;
	GameEngineRender* StatUI = nullptr;

	std::set<std::pair< std::string, Button*>> ShowedBtn;

	void ReSet();

	void SetItemImage();
	
	void SetItemFunction();
};

