#include "Items.h"
#include <GameEngineCore/GameEngineRender.h>
#include <GameEngineCore/GameEngineCollision.h>
#include "ContentsEnums.h"

#include "Player.h"

//std::map<std::string, Items> Items::AllItems;
std::queue<Items*> Items::ObtainedItems;

Items::Items()
{
}

Items::~Items()
{
}

void Items::SetExp(float _Exp)
{
	Exp = _Exp;
	if (Exp >= 10)
	{
		ItemRender->SetImage("ExperienceGemRed.bmp");
	}
	else if (Exp >= 5)
	{
		ItemRender->SetImage("ExperienceGemGreen.bmp");
	}
	else
	{
		ItemRender->SetImage("ExperienceGemBlue.bmp");
	}
}

void Items::Reset()
{
	ItemRender = CreateRender(VSRenderOrder::Item);
	ItemCollision = CreateCollision(VSRenderOrder::Item);

	ItemRender->SetImageToScaleToImage("ExperienceGemBlue.bmp");

	float4 ColScale = ItemRender->GetScale() * 1.5f;
	float Magnetic = 1.0f + 0.5f * static_cast<float>(Player::MainPlayer->GetPlayerActive().Magnet / 10);
	ItemCollision->SetScale(ColScale * Magnetic);

	ItemRender->SetPosition({ 0,-ItemRender->GetScale().hy() });
	ItemCollision->SetPosition({ 0,-ItemRender->GetScale().hy() });
	this->On();
}

void Items::Start()
{
	Reset();
}

void Items::Update(float _DeltaTime)
{

}