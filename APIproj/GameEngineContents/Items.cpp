#include "Items.h"
#include <GameEngineCore/GameEngineRender.h>
#include <GameEngineCore/GameEngineCollision.h>
#include "ContentsEnums.h"

//std::map<std::string, Items> Items::AllItems;

Items::Items()
{
}

Items::~Items()
{
}

void Items::SetExp(int _Exp)
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

void Items::Start()
{
	ItemRender = CreateRender(VSRenderOrder::Item);
	ItemCollision = CreateCollision(VSRenderOrder::Item);

	ItemRender->SetImageToScaleToImage("ExperienceGemBlue.bmp");

	ItemCollision->SetScale(ItemRender->GetScale());

	ItemRender->SetPosition({ 0,-ItemRender->GetScale().hy()});
	ItemCollision->SetPosition({ 0,-ItemRender->GetScale().hy()});
}

void Items::Update(float _DeltaTime)
{

}