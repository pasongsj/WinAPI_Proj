#include "ContentsGameCore.h"
#include "MadForestLevel.h"
#include "InlaidLibraryLevel.h"

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
	new int(); // leaküũ��
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