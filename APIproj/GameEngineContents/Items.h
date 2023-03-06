#pragma once
#include <map>
#include <GameEngineCore/GameEngineActor.h>
#include <queue>
class Items : public GameEngineActor
{
public:

	static std::queue<Items*> ObtainedItems; // ¿ÃπÃ »πµÊ«— æ∆¿Ã≈€
	// constrcuter destructer
	Items() ;
	~Items();

	// delete Function
	Items(const Items& _Other) = delete;
	Items(Items&& _Other) noexcept = delete;
	Items& operator=(const Items& _Other) = delete;
	Items& operator=(Items&& _Other) noexcept = delete;
	void SetExp(float _Exp); 
	inline float GetExp() {
		return Exp;
	}

	void Reset();
	//Items GetItems(const std::string_view& _Name) {
	//	//Items*;
	//	return AllItems[_Name.data()];
	//}


protected:
	void Start() override;
	void Update(float _DeltaTime) override;

private:
	GameEngineRender* ItemRender = nullptr;
	GameEngineCollision* ItemCollision = nullptr; // æ∆¿Ã≈€ »πµÊ ªÁ∞≈∏Æ
	float Exp = 1;
	/*static std::map<std::string, Items> AllItems;*/
};

