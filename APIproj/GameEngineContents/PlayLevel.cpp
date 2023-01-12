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

	// �̷� ��θ� ���� ���.
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



	// �������� �͵��� ����� ������ Loading�����Դϴ�.
	CreateActor<Player>();

	//float Time = NewTime.TimeCheckEnd();
}

void PlayLevel::Update()
{

}
