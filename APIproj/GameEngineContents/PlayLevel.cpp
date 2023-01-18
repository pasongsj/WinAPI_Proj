#include "PlayLevel.h"
#include "Player.h"
#include <GameEngineBase/GameEngineDirectory.h>
#include <GameEngineCore/GameEngineResources.h>
//#include <GameEngineBase/GameEngineTime.h>

PlayLevel::PlayLevel()
{
}

PlayLevel::~PlayLevel()
{
}
void PlayLevel::Loading()
{

	GameEngineDirectory Dir;

	Dir.MoveParentToDirectory("ContentsResources");
	Dir.Move("ContentsResources");
	Dir.Move("Image");

	//GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("enemiesM.BMP"));

	/*{
		GameEngineImage* Image = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("enemiesM.BMP"));
		Image->Cut(32, 10);
	}*/



	// 만들어야할 것들을 만드는 시점이 Loading시점입니다.
	//CreateActor<Player>();

	//float Time = NewTime.TimeCheckEnd();
}

void PlayLevel::Update(float _DeltaTime)
{

}
