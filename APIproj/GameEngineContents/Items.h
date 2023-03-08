#pragma once
#include <map>
#include <GameEngineCore/GameEngineActor.h>
#include <queue>
class Items : public GameEngineActor
{
public:

	static std::vector<Items*> ObtainedItems; // ¿ÃπÃ »πµÊ«— æ∆¿Ã≈€
	// constrcuter destructer
	Items() ;
	~Items();

	// delete Function
	Items(const Items& _Other) = delete;
	Items(Items&& _Other) noexcept = delete;
	Items& operator=(const Items& _Other) = delete;
	Items& operator=(Items&& _Other) noexcept = delete;
	void SetExp(float _Exp, bool _IsBox = false); 
	inline float GetExp() {
		return Exp;
	}

	void Reset();

	bool GetIsBox()
	{
		return IsBox;
	}


protected:
	void Start() override;
	void Update(float _DeltaTime) override;

private:
	bool IsBox = false;
	GameEngineRender* ItemRender = nullptr;
	GameEngineCollision* ItemCollision = nullptr; // æ∆¿Ã≈€ »πµÊ ªÁ∞≈∏Æ
	float Exp = 1;
	/*static std::map<std::string, Items> AllItems;*/
};

