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



	// �������� �͵��� ����� ������ Loading�����Դϴ�.
	//CreateActor<Player>();

	//float Time = NewTime.TimeCheckEnd();
}

void PlayLevel::Update(float _DeltaTime)
{

}
