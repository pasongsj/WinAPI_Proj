#include "GameEngineActor.h"
#include "GameEngineRender.h"
#include "GameEngineLevel.h"
#include "GameEngineCollision.h"

GameEngineActor::GameEngineActor() 
{
}

GameEngineActor::~GameEngineActor() 
{
	for (GameEngineRender* _Render : RenderList)
	{
		if (nullptr == _Render)
		{
			continue;
		}

		delete _Render;
		_Render = nullptr;
	}
}

GameEngineLevel* GameEngineActor::GetLevel()
{
	return GetOwner<GameEngineLevel>();
}

GameEngineRender* GameEngineActor::CreateRender(const std::string_view& _Image, int _Order /*= 0*/)
{
	GameEngineRender* Render = CreateRender(_Order);
	Render->SetImage(_Image);
	Render->SetOwner(this);
	return Render;
}

GameEngineRender* GameEngineActor::CreateRender(int _Order /*= 0*/)
{
	GameEngineRender* Render = new GameEngineRender();
	Render->SetOwner(this);
	Render->SetOrder(_Order);
	RenderList.push_back(Render);
	return Render;
}

GameEngineCollision* GameEngineActor::CreateCollision(int _GroupIndex)
{
	GameEngineCollision* Collision = new GameEngineCollision();
	// �и��� �� ���� ���� �ʴ�.
	Collision->SetOwner(this);
	Collision->SetOrder(_GroupIndex);
	CollisionList.push_back(Collision);
	return Collision;
}