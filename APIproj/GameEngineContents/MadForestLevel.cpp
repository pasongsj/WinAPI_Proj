#include "MadForestLevel.h"
#include "Player.h"

MadForestLevel::MadForestLevel()
{
}

MadForestLevel::~MadForestLevel()
{
}

void MadForestLevel::Loading()
{
	// �������� �͵��� ����� ������ Loading�����Դϴ�.
	CreateActor<Player>();
}

void MadForestLevel::Update()
{

}
