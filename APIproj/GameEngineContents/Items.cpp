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

void Items::Start()
{
	ItemRender = CreateRender(VSRenderOrder::Item);
	ItemCollision = CreateCollision(VSRenderOrder::Item);
	//ItemRender->SetImage("exp0.bmp");
	ItemRender->SetImageToScaleToImage("exp0.bmp");

	/*ItemRender->SetScale({ 32,45 });*/
	ItemCollision->SetScale(ItemRender->GetScale());

	//ItemRender->SetScaleToImage();
	ItemRender->SetPosition({ 0,-ItemRender->GetScale().hy()});
	ItemCollision->SetPosition({ 0,-ItemRender->GetScale().hy()});
}

void Items::Update(float _DeltaTime)
{

}