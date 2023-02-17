#include "Items.h"
#include <GameEngineCore/GameEngineRender.h>
#include <GameEngineCore/GameEngineCollision.h>
#include "ContentsEnums.h"

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
	ItemRender->SetImage("exp0.bmp");
	ItemRender->SetScale({ 65,90 });
	ItemCollision->SetScale({ 60,85 });
}

void Items::Update(float _DeltaTime)
{

}