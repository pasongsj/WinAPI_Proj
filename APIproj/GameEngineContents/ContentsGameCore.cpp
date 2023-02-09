#include "ContentsGameCore.h"
#include <GameEnginePlatform/GameEngineWindow.h>

#include "MadForestLevel.h"
#include "InlaidLibraryLevel.h"
#include "TitleLevel.h"
#include "PlayLevel.h"
#include "OpeningLevel.h"

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

	GameEngineWindow::SettingWindowSize({ 1536.0f, 960.0f });  // // 1536 x 960 1280x800

	new int(); // leak체크용

	//CreateLevel<MadForestLevel>("MadForestLevelt");
	CreateLevel<InlaidLibraryLevel>("InlaidLibraryLevel");
	CreateLevel<TitleLevel>("TitleLevel");
	CreateLevel<PlayLevel>("PlayLevel");
	CreateLevel< OpeningLevel>("OpeningLevel");
	ChangeLevel("TitleLevel");
}

void ContentsGameCore::Update()
{

}
void ContentsGameCore::End()
{

}