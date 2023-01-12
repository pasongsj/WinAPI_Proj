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
//	GameEngineTime NewTime;

//	NewTime.TimeCheckStart();

	// 이런 경로를 절대 경로.
	// "D:\Project\AR45\WINAPI\APIApp\ContentsResources\Iamge\Heros.bmp";

	// std::string Text = "D:\Project\AR45\WINAPI\APIApp\ContentsResources\Iamge\Heros.bmp";

	GameEngineDirectory Dir;

	Dir.MoveParentToDirectory("ContentsResources");
	Dir.Move("ContentsResources");
	Dir.Move("Image");

	//GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("enemiesM.BMP"));

	{
		GameEngineImage* Image = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("enemiesM.BMP"));
		Image->Cut(4, 8);
	}



	// 만들어야할 것들을 만드는 시점이 Loading시점입니다.
	CreateActor<Player>();

	//float Time = NewTime.TimeCheckEnd();
}

void PlayLevel::Update()
{

}
