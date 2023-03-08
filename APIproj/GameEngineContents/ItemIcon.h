#pragma once
#include <set>
#include <map>
#include <GameEngineCore/GameEngineActor.h>
class ItemIcon : public GameEngineActor
{
public:
	// constrcuter destructer
	ItemIcon() ;
	~ItemIcon();

	// delete Function
	ItemIcon(const ItemIcon& _Other) = delete;
	ItemIcon(ItemIcon&& _Other) noexcept = delete;
	ItemIcon& operator=(const ItemIcon& _Other) = delete;
	ItemIcon& operator=(ItemIcon&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;

private:
	std::set<std::string> WeaponIconList;
	std::vector<GameEngineRender*> WeaponIcon;

	std::set<std::string> ActiveIconList;
	std::vector<GameEngineRender*> ActiveIcon;

	std::map<std::string, int> _Active;
	
	float4 WeaponPos = float4::Zero;
	float4 ActivePos = float4::Zero;

	void NextWeaponIconPos();
	void NextActiveIconPos();


};

