#include "ContentsGameCore.h"
#include "MadForestLevel.h"
#include "InlaidLibraryLevel.h"

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
	new int(); // leak체크용
	CreateLevel<MadForestLevel>("MadForest");
	CreateLevel<InlaidLibraryLevel>("InlaidLibrary");
	ChangeLevel("Title");
}

void ContentsGameCore::Update()
{

}
void ContentsGameCore::End()
{

}