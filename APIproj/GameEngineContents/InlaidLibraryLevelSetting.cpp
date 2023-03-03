#include "InlaidLibraryLevel.h"

#include "Player.h"


void InlaidLibraryLevel::SetState(float _DeltaTime)
{
	if (Player::IsStop == true)
	{
		return;
	}
	LevelTime += _DeltaTime;
	if (0 <= LevelTime && LevelTime < 1 * 60)
	{
		MaxMonster = 50;
		RegenInterval = 3.0f;
		SponableMonster.insert("Dust");
	}
	else if (1 * 60 <= LevelTime && LevelTime < 2 * 60)
	{
		MaxMonster = 80;
		RegenInterval = 3.0f;
	}
	else if (2 * 60 <= LevelTime && LevelTime < 3 * 60)
	{
		MaxMonster = 100;
		RegenInterval = 4.0f;
		SponableMonster.insert("Musc");
	}
	else if (3 * 60 <= LevelTime && LevelTime < 4 * 60)
	{
		MaxMonster = 60;
		RegenInterval = 4.0f;
		SponableMonster.clear();
		SponableMonster.insert("Mummy");
	}
	else if (4 * 60 <= LevelTime && LevelTime < 5 * 60)
	{
		MaxMonster = 100;
		RegenInterval = 4.0f;
		SponableMonster.insert("Dust");
	}
	else if (5 * 60 <= LevelTime && LevelTime < 6 * 60)
	{
		MaxMonster = 100;
		RegenInterval = 4.0f;
		SponableMonster.erase("Dust");
	}
	else if (6 * 60 <= LevelTime && LevelTime < 7 * 60)
	{
		MaxMonster = 30;
		RegenInterval = 2.0f;
		SponableMonster.clear();
		SponableMonster.insert("Dullahan");
		SponableMonster.insert("Musc");
	}
	else if (7 * 60 <= LevelTime && LevelTime < 8 * 60)
	{
		MaxMonster = 80;
		RegenInterval = 2.0f;
	}
	else if (8 * 60 <= LevelTime && LevelTime < 9 * 60)
	{
		MaxMonster = 80;
		RegenInterval = 1.0f;
		SponableMonster.erase("Dullahan");
		SponableMonster.insert("Ghost");
	}
	else if (9 * 60 <= LevelTime && LevelTime < 10 * 60)
	{
		MaxMonster = 200;
		RegenInterval = 0.5f;
		SponableMonster.erase("Musc");
		SponableMonster.insert("Mummy");
	}
	else if (10 * 60 <= LevelTime && LevelTime < 11 * 60)
	{
		MaxMonster = 100;
		RegenInterval = 0.5f;
		SponableMonster.clear();
		SponableMonster.insert("Musc");
	}
	else if (11 * 60 <= LevelTime && LevelTime < 12 * 60)
	{
		MaxMonster = 120;
		RegenInterval = 2.0f;
		SponableMonster.clear();
		SponableMonster.insert("ColossalMedusaHead");
		SponableMonster.insert("LionHead");
	}
	else if (12 * 60 <= LevelTime && LevelTime < 13 * 60)
	{
		MaxMonster = 80;
		RegenInterval = 1.0f;
		SponableMonster.erase("LionHead");
		SponableMonster.insert("Dullahan");
	}
	else if (13 * 60 <= LevelTime && LevelTime < 14 * 60)
	{
		MaxMonster = 120;
		RegenInterval = 0.5f;
		SponableMonster.erase("ColossalMedusaHead");
		SponableMonster.insert("Mummy");
	}
	else if (14 * 60 <= LevelTime && LevelTime < 15 * 60)
	{
		MaxMonster = 300;
		RegenInterval = 0.1f;
		SponableMonster.erase("Dullahan");
		SponableMonster.insert("ColossalMedusaHead");
		SponableMonster.insert("Musc");
	}
	else if (15 * 60 <= LevelTime && LevelTime < 16 * 60)
	{
		MaxMonster = 100;
		RegenInterval = 0.1f;
	}
	else if (16 * 60 <= LevelTime && LevelTime < 17 * 60)
	{
		MaxMonster = 100;
		RegenInterval = 1.0f;
	}
	else if (17 * 60 <= LevelTime && LevelTime < 18 * 60)
	{
		MaxMonster = 200;
		RegenInterval = 1.0f;
	}
	else if (18 * 60 <= LevelTime && LevelTime < 19 * 60)
	{
		MaxMonster = 60;
		RegenInterval = 0.5f;
	}
	else if (19 * 60 <= LevelTime && LevelTime < 20 * 60)
	{
		MaxMonster = 120;
		RegenInterval = 0.5f;
	}
	else if (20 * 60 <= LevelTime && LevelTime < 21 * 60)
	{
		MaxMonster = 100;
		RegenInterval = 0.1f;
	}
	else if (21 * 60 <= LevelTime && LevelTime < 22 * 60)
	{
		MaxMonster = 100;
		RegenInterval = 0.1f;
	}
	else if (22 * 60 <= LevelTime && LevelTime < 23 * 60)
	{
		MaxMonster = 80;
		RegenInterval = 1.0f;
	}
	else if (23 * 60 <= LevelTime && LevelTime < 24 * 60)
	{
		MaxMonster = 120;
		RegenInterval = 0.1f;
	}
	else if (24 * 60 <= LevelTime && LevelTime < 25 * 60)
	{
		MaxMonster = 300;
		RegenInterval = 0.1f;
	}
	else if (25 * 60 <= LevelTime && LevelTime < 26 * 60)
	{
		MaxMonster = 300;
		RegenInterval = 0.1f;
	}
	else if (26 * 60 <= LevelTime && LevelTime < 27 * 60)
	{
		MaxMonster = 100;
		RegenInterval = 0.1f;
	}
	else if (27 * 60 <= LevelTime && LevelTime < 28 * 60)
	{
		MaxMonster = 300;
		RegenInterval = 0.1f;
	}
	else if (28 * 60 <= LevelTime && LevelTime < 29 * 60)
	{
		MaxMonster = 250;
		RegenInterval = 0.1f;
	}
	else if (29 * 60 <= LevelTime && LevelTime < 30 * 60)
	{
		MaxMonster = 250;
		RegenInterval = 0.1f;
	}
	else
	{
		MaxMonster = 1;
		RegenInterval = 10.0f;
	}

}
