#pragma once
#include <set>
#include <unordered_map>
#include <GameEngineCore/GameEngineActor.h>
#include <GameEngineCore/Button.h>
#include <GameEngineCore/NumberRenderObject.h>

class AdditionItemUI : public GameEngineActor
{
public:
	static std::vector<std::string> DeleteItemName;
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

	void SetActiveStatUIValue(int _Index, int _Value)
	{
		//1, static_cast<int>(PlayerActive.Recovery *10)
		if (1 == _Index && 1 == _Value && nullptr != ZeroPoint)
		{
			ZeroPoint->Off();
		}
		ActiveStatUI[_Index].SetValue(_Value);
	}
	
	bool GetIsUIOnOff()
	{
		return IsUIOnOff;
	}

protected:

	void Start() override;
	void Update(float _DeltaTime) override;

private:
	bool IsUIOnOff = false;
	bool IsReset = false;


	std::map<std::string, std::string> ItemNames;

	std::map<std::string, Button*> Items;
	std::map<std::string, Button*> DeletedItem;


	float4 BtnScale = float4{ 547,153, };
	std::vector<float4> BtnPos;
	GameEngineRender* LevelUpUIRender = nullptr;
	GameEngineRender* StatUI = nullptr;
	GameEngineRender* ZeroPoint = nullptr;

	std::set<std::pair< std::string, Button*>> ShowedBtn;

	//std::vector<std::pair<int, std::string>> Icon;

	void ReSet();

	void SetItemImage();
	
	void SetItemFunction();

	NumberRenderObject ActiveStatUI[17];

	void SetStatNumber();

	void SetStatNumberValue();
	

};

