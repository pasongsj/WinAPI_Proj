#include "Monster.h"
#include "Player.h"


void Monster::Setting()
{
	MonsterRenderScale = float4{ 70, 140 };

	if ("Dust" == Name)
	{
		Hp = 5;
		Dmg = 5;
		MoveSpeed = 140;
		Exp = 1;
		EndFrame[0] = 1;
		EndFrame[1] = 1;
		EndFrame[2] = 9;

	}
	else if ("Musc" == Name)
	{
		//1 - 2:00, 6:00, 7:00, 17:00
		Hp = 1;
		Dmg = 2;
		MoveSpeed = 160;
		Exp = 1;
		//2 - 7:00, 8:00, 10:00, 14:00, 17:00

		EndFrame[0] = 3;
		EndFrame[1] = 3;
		EndFrame[2] = 1;

	}
	else if ("Mummy" == Name)
	{
		Hp = 15;
		Dmg = 3;
		MoveSpeed = 140;
		Exp = 2;

		EndFrame[0] = 3;
		EndFrame[1] = 2;
		EndFrame[2] = 4;

	}
	else if ("Dullahan" == Name)
	{
		//2 - 6:00, 7:00, 12:00, 13:00, 16:00, 23:00
		Hp = 70;
		Dmg = 8;
		MoveSpeed = 100;
		Exp = 2;

		EndFrame[0] = 1;
		EndFrame[1] = 1;
		EndFrame[2] = 3;

	}
	else if ("SmallMedusaHead" == Name)
	{ // 추가설정 필요
		Hp = 1;
		Dmg = 1;
		MoveSpeed = 240;
		Exp = 1;
		

		EndFrame[0] = 3;
		EndFrame[1] = 3;
		EndFrame[2] = 4;

	}
	else if ("LionHead" == Name) // 
	{
		Hp = 3.0f * Player::MainPlayer->GetPlayerLevel();
		Dmg = 3;
		MoveSpeed = 200;
		Exp = 2;

		EndFrame[0] = 2;
		EndFrame[1] = 2;
		EndFrame[2] = 3;

	}
	else if ("Ghost" == Name)
	{
		Hp = 10;
		Dmg = 5;
		MoveSpeed = 200;
		Exp = 1.5f;

		EndFrame[0] = 1;
		EndFrame[1] = 1;
		EndFrame[2] = 6;

	}
	// -- 추가된부분
	else if ("GiantMedusa " == Name)
	{
		Hp = 800;
		Dmg = 15;
		MoveSpeed = 150;
		Exp = 3;

		EndFrame[0] = 2;
		EndFrame[1] = 2;
		EndFrame[2] = 4;
	}
	else if ("QueenMedusa" == Name)
	{
		MonsterRenderScale = float4{ 104, 208 };
		Hp = 150.0f * Player::MainPlayer->GetPlayerLevel();
		Dmg = 20;
		MoveSpeed = 160;
		Exp = 30;

		EndFrame[0] = 2;
		EndFrame[1] = 2;
		EndFrame[2] = 4;
	}
	else if ("BigMusc2 " == Name)
	{
		MonsterRenderScale = float4{ 104, 208 };
		Hp = 50;
		Dmg = 10;
		MoveSpeed = 170;
		Exp = 30;

		EndFrame[0] = 2;
		EndFrame[1] = 2;
		EndFrame[2] = 4;
	}
	else if ("BigLionHead" == Name)
	{
		MonsterRenderScale = float4{ 104, 208 };
		Hp = 50;
		Dmg = 10;
		MoveSpeed = 170;
		Exp = 30;

		EndFrame[0] = 2;
		EndFrame[1] = 2;
		EndFrame[2] = 3;
	}
	else if ("BigDust " == Name)
	{
		MonsterRenderScale = float4{ 104, 208 };
		Hp = 50.0f;
		Dmg = 10.0f;
		MoveSpeed = 170.0f;
		Exp = 30.0f;

		EndFrame[0] = 1;
		EndFrame[1] = 1;
		EndFrame[2] = 9;
	}
	else if ("MedusaHead" == Name)
	{
		MonsterRenderScale = float4{ 80, 160 };
		Hp = 25;
		Dmg = 1;
		MoveSpeed = 240;
		Exp = 2;

		EndFrame[0] = 3;
		EndFrame[1] = 3;
		EndFrame[2] = 4;
	}
	else if ("MedusaHeadBoss" == Name)
	{
		MonsterRenderScale = float4{ 80, 160 };
		Hp = 40.0f * Player::MainPlayer->GetPlayerLevel();
		Dmg = 10;
		MoveSpeed = 170;
		Exp = 30;

		EndFrame[0] = 3;
		EndFrame[1] = 3;
		EndFrame[2] = 4;
	}
	else if ("ApprenticeWitch" == Name)
	{
		Hp = 220;
		Dmg = 14;
		MoveSpeed = 130;
		Exp = 3;

		EndFrame[0] = 3;
		EndFrame[1] = 3;
		EndFrame[2] = 4;
	}
	else if ("EliteDullahan" == Name)
	{
		Hp = 150;
		Dmg = 8;
		MoveSpeed = 100;
		Exp = 2;

		EndFrame[0] = 2;
		EndFrame[1] = 2;
		EndFrame[2] = 3;
	}
	else if ("GiantBat" == Name)
	{
		MonsterRenderScale = float4{ 80, 160 };
		Hp = 270;
		Dmg = 10;
		MoveSpeed = 140;
		Exp = 2.5f;

		EndFrame[0] = 3;
		EndFrame[1] = 3;
		EndFrame[2] = 4;
	}
	else if ("GiantMummy" == Name)
	{
		MonsterRenderScale = float4{ 104, 208 };
		Hp = 500;
		Dmg = 20;
		MoveSpeed = 80;
		Exp = 3;// 박스

		EndFrame[0] = 2;
		EndFrame[1] = 2;
		EndFrame[2] = 5;
	}
	else if ("GlowingBat" == Name)
	{
		Hp = 50.0f *Player::MainPlayer->GetPlayerLevel();
		Dmg = 10;
		MoveSpeed = 140;
		Exp = 30;

		EndFrame[0] = 2;
		EndFrame[1] = 2;
		EndFrame[2] = 3;
	}
	else if ("GlowingSkull" == Name)
	{
		Hp = 6.5f * Player::MainPlayer->GetPlayerLevel();
		Dmg = 14;
		MoveSpeed = 140;
		Exp = 2;

		EndFrame[0] = 3;
		EndFrame[1] = 3;
		EndFrame[2] = 3;
	}
	else if ("Hag" == Name)
	{
		MonsterRenderScale = float4{ 104, 208 };

		Hp = 250.0f * Player::MainPlayer->GetPlayerLevel();
		Dmg = 30;
		MoveSpeed = 210;
		Exp = 50;

		EndFrame[0] = 2;
		EndFrame[1] = 2;
		EndFrame[2] = 3;
	}
	else if ("Musc2" == Name)
	{
		Hp = 13;
		Dmg = 4;
		MoveSpeed = 160;
		Exp = 1;

		EndFrame[0] = 2;
		EndFrame[1] = 2;
		EndFrame[2] = 4;
	}
	else if ("Nesuferit" == Name)
	{
		MonsterRenderScale = float4{ 104, 208 };

		Hp = 200.0f * Player::MainPlayer->GetPlayerLevel();
		Dmg = 30;
		MoveSpeed = 160;
		Exp = 50;

		EndFrame[0] = 3;
		EndFrame[1] = 3;
		EndFrame[2] = 4;
	}
	else if ("SilverBat" == Name)
	{
		Hp = 50.0f * Player::MainPlayer->GetPlayerLevel();
		Dmg = 10;
		MoveSpeed = 140;
		Exp = 30;

		EndFrame[0] = 2;
		EndFrame[1] = 2;
		EndFrame[2] = 3;
	}
	else if ("UndeadSassyWitch" == Name)
	{
		Hp = 500;
		Dmg = 20;
		MoveSpeed = 200;
		Exp = 3;

		EndFrame[0] = 3;
		EndFrame[1] = 3;
		EndFrame[2] = 5;
	}
	else if ("MasterWitch" == Name)
	{
		MonsterRenderScale = float4{ 104, 208 };
		Hp = 150.0f *Player::MainPlayer->GetPlayerLevel();
		Dmg = 30;
		MoveSpeed = 200;
		Exp = 3;

		EndFrame[0] = 3;
		EndFrame[1] = 3;
		EndFrame[2] = 5;
	}



	

}
