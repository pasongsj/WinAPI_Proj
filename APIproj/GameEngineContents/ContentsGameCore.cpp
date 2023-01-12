#include "ContentsGameCore.h"
#include <GameEnginePlatform/GameEngineWindow.h>

#include "MadForestLevel.h"
#include "InlaidLibraryLevel.h"
#include "TitleLevel.h"
#include "PlayLevel.h"

// static초기화
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

	new int(); // leak체크용

	CreateLevel<MadForestLevel>("MadForest");
	//CreateLevel<MadForestLevel>("MadForest");
	CreateLevel<InlaidLibraryLevel>("InlaidLibrary");
	CreateLevel<TitleLevel>("Title");
	CreateLevel<PlayLevel>("Play");
	ChangeLevel("Play");
}

void ContentsGameCore::Update()
{

}
void ContentsGameCore::End()
{

}