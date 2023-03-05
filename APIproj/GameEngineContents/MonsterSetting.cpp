#include "Monster.h"
#include "Player.h"


void Monster::Setting()
{
	if ("Dust" == MonsterName)
	{
		Hp = 5;
		Dmg = 5;
		MoveSpeed = 140;
		Exp = 1;
		EndFrame[0] = 1;
		EndFrame[1] = 1;
		EndFrame[2] = 9;

	}
	else if ("Musc" == MonsterName)
	{
		//1 - 2:00, 6:00, 7:00, 17:00
		Hp = 1;
		Dmg = 2;
		MoveSpeed = 160;
		Exp = 1;
		//2 - 7:00, 8:00, 10:00, 14:00, 17:00
		Hp = 13;
		Dmg = 4;
		MoveSpeed = 160;
		Exp = 1;

		EndFrame[0] = 3;
		EndFrame[1] = 3;
		EndFrame[2] = 1;

	}
	else if ("Mummy" == MonsterName)
	{
		Hp = 15;
		Dmg = 3;
		MoveSpeed = 140;
		Exp = 2;

		EndFrame[0] = 3;
		EndFrame[1] = 2;
		EndFrame[2] = 4;

	}
	else if ("Dullahan" == MonsterName)
	{
		//2 - 6:00, 7:00, 12:00, 13:00, 16:00, 23:00
		Hp = 70;
		Dmg = 8;
		MoveSpeed = 100;
		Exp = 2;
		//3 - 16:00, 19:00, 20:00, 23:00
		Hp = 150;
		Dmg = 8;
		MoveSpeed = 100;
		Exp = 2;

		EndFrame[0] = 1;
		EndFrame[1] = 1;
		EndFrame[2] = 3;

	}
	else if ("ColossalMedusaHead" == MonsterName)
	{ // 추가설정 필요
		Hp = 1;
		Dmg = 1;
		MoveSpeed = 600;
		Exp = 1;
		//
		Hp = 25;
		Dmg = 1;
		MoveSpeed = 240;
		Exp = 2;

		EndFrame[0] = 3;
		EndFrame[1] = 3;
		EndFrame[2] = 4;

	}
	else if ("LionHead" == MonsterName) // 
	{
		Hp = 3 * Player::MainPlayer->GetHp();
		Dmg = 3;
		MoveSpeed = 200;
		Exp = 2;

		EndFrame[0] = 2;
		EndFrame[1] = 2;
		EndFrame[2] = 3;

	}
	else if ("Ghost" == MonsterName)
	{
		Hp = 10;
		Dmg = 5;
		MoveSpeed = 200;
		Exp = 2;

		EndFrame[0] = 1;
		EndFrame[1] = 1;
		EndFrame[2] = 6;

	}

}
