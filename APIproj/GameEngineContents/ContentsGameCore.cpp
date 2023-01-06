#include "ContentsGameCore.h"
#include <GameEnginePlatform/GameEngineWindow.h>

#include "MadForestLevel.h"
#include "InlaidLibraryLevel.h"
#include "TitleLevel.h"

// static�ʱ�ȭ
ContentsGameCore ContentsGameCore::Core;

ContentsGameCore::ContentsGameCore()
{
}

ContentsGameCore::~ContentsGameCore()
{
}

void ContentsGameCore::Start()
{

	GameEngineWindow::SettingWindowSize({ (900.0f / 1080.0f) * 1726.0f, (900.0f / 1080.0f) * 1080.0f }); //1726 x 1080

	new int(); // leaküũ��

	CreateLevel<MadForestLevel>("MadForest");
	//CreateLevel<MadForestLevel>("MadForest");
	CreateLevel<InlaidLibraryLevel>("InlaidLibrary");
	CreateLevel<TitleLevel>("Title");
	ChangeLevel("MadForest");
}

void ContentsGameCore::Update()
{

}
void ContentsGameCore::End()
{

}