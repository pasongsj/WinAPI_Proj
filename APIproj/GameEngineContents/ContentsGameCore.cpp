#include "ContentsGameCore.h"
#include <GameEnginePlatform/GameEngineWindow.h>

#include "MadForestLevel.h"
#include "InlaidLibraryLevel.h"
#include "TitleLevel.h"
#include "PlayLevel.h"

#include <GameEnginePlatform/GameEngineWindow.h>

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

	GameEngineWindow::SettingWindowSize({ (900.0f / 800.0f) * 1280.0f, (900.0f / 800.0f) * 800.0f }); 

	new int(); // leak체크용

	//CreateLevel<MadForestLevel>("MadForestLevelt");
	CreateLevel<InlaidLibraryLevel>("InlaidLibraryLevel");
	CreateLevel<TitleLevel>("TitleLevel");
	CreateLevel<PlayLevel>("PlayLevel");
	ChangeLevel("TitleLevel");
}

void ContentsGameCore::Update()
{

}
void ContentsGameCore::End()
{

}