#include "InlaidLibraryLevel.h"

#include "Player.h"
#include "PlayGameUI.h"

#include "Monster.h"
#include "ContentsEnums.h"
//00분대 : Dust,
//01분대 : Dust(물량)
//02분대 : Dust, Musc(Ectoplasm)
//03분대 : Mummy,
//04분대 : Dust, Mummy
//05분대 : Mummy,
//06분대 : Dullahan, Musc
//07분대 : Dullahan, Musc, Musc2
//08분대 : Ghost, Musc,
//09분대 : Ghost, Mummy
//10분대 : Musc,
//11분대 : Lionhead, ColossalMedusaHead
//12분대 : Dullahan, MedusaHead,
//13분대 : Mummy, Dullahan,
//14분대 : Mummy, Musc2, MedusaHead,
//15분대 : MedusaHead,
//16분대 : Dullahan, EliteDullahan, ApprenticeWitch
//17분대 : Musc, Musc2, ApprenticeWitch,
//18분대 : ApprenticeWitch, Lionhead
//19분대 : ApprenticeWitch, EliteDullahan,
//20분대 : EliteDullahan, Lionhead,
//21분대 : Lionhead
//22분대 : Lionhead, UndeadSassyWitch,
//23분대 : EliteDullahan, Dullahan, UndeadSassyWitch
//24분대 : UndeadSassyWitch
//25분대 : GiantBat(흡혈박쥐), GlowingSkull(두개골), UndeadSassyWitc
//26분대 : GiantMedusa,
//27분대 : GiantMedusa, MedusaHead
//28분대 : ApprenticeWitch,
//29분대 : ColossalMedusaHead, BigDust, BigMusc, ColossalLionhead,

void InlaidLibraryLevel::SetState()
{
	if (Player::IsStop == true || nullptr == NewUI)
	{
		return;
	}
	float LevelTime = NewUI->GetStageTime();
	if (LevelTime > NextSettingTime * 60)
	{
		NextSettingTime++;
	}
	else
	{
		return;
	}

	if (0 <= LevelTime && LevelTime < 1 * 60)//00분대 : Dust,
	{
		MaxMonster = 50;
		RegenInterval = 3.0f;

		SponableMonster.clear();
		SponableMonster.push_back("Dust");
	}
	else if (1 * 60 <= LevelTime && LevelTime < 2 * 60)//01분대 : Dust(물량)
	{
		MaxMonster = 80;
		RegenInterval = 3.0f;

		SponableMonster.clear();
		SponableMonster.push_back("Dust");
	}
	else if (2 * 60 <= LevelTime && LevelTime < 3 * 60)//02분대 : Dust, Musc(Ectoplasm)
	{
		MaxMonster = 100;
		RegenInterval = 4.0f;

		SponableMonster.clear();
		SponableMonster.push_back("Dust");
		SponableMonster.push_back("Musc");
	}
	else if (3 * 60 <= LevelTime && LevelTime < 4 * 60)//03분대 : Mummy,
	{
		Monster::MonsterName = "GiantMummy";
		Monster* Boss = CreateActor<Monster>(VSRenderOrder::Monster);
		Boss->SetBoxBossOn();

		MaxMonster = 60;
		RegenInterval = 4.0f;

		SponableMonster.clear();
		SponableMonster.push_back("Mummy");
	}
	else if (4 * 60 <= LevelTime && LevelTime < 5 * 60)//04분대 : Dust, Mummy
	{
		MaxMonster = 100;
		RegenInterval = 4.0f;

		SponableMonster.clear();
		SponableMonster.push_back("Dust");
		SponableMonster.push_back("Mummy");
	}
	else if (5 * 60 <= LevelTime && LevelTime < 6 * 60)	//05분대 : Mummy,			
	{		
		Monster::MonsterName = "GiantMummy";
		Monster* Boss = CreateActor<Monster>(VSRenderOrder::Monster);
		Boss->SetBoxBossOn();

		MaxMonster = 100;														   
		RegenInterval = 4.0f;		

		SponableMonster.clear();
		SponableMonster.push_back("Mummy");										   
	}
	else if (6 * 60 <= LevelTime && LevelTime < 7 * 60)//06분대 : Dullahan, Musc
	{
		MaxMonster = 30;
		RegenInterval = 2.0f;

		SponableMonster.clear();
		SponableMonster.push_back("Dullahan");
		SponableMonster.push_back("Musc");
	}
	else if (7 * 60 <= LevelTime && LevelTime < 8 * 60)//07분대 : Dullahan, Musc, Musc2
	{
		MaxMonster = 80;
		RegenInterval = 2.0f;

		SponableMonster.clear();
		SponableMonster.push_back("Musc");
		SponableMonster.push_back("Musc2");
		SponableMonster.push_back("Dullahan");
	}
	else if (8 * 60 <= LevelTime && LevelTime < 9 * 60)//08분대 : Ghost, Musc,
	{
		Monster::MonsterName = "BigMusc2";
		Monster* Boss = CreateActor<Monster>(VSRenderOrder::Monster);
		Boss->SetBoxBossOn();

		MaxMonster = 80;
		RegenInterval = 1.0f;
		

		SponableMonster.clear();
		SponableMonster.push_back("Ghost");
		SponableMonster.push_back("Musc2");
	}
	else if (9 * 60 <= LevelTime && LevelTime < 10 * 60)//09분대 : Ghost, Mummy
	{
		MaxMonster = 200;
		RegenInterval = 0.5f;

		SponableMonster.clear();
		SponableMonster.push_back("Ghost");
		SponableMonster.push_back("Mummy");
	}
	else if (10 * 60 <= LevelTime && LevelTime < 11 * 60)//10분대 : Musc,
	{
		Monster::MonsterName = "BigLionHead";
		Monster* Boss = CreateActor<Monster>(VSRenderOrder::Monster);
		Boss->SetBoxBossOn();

		MaxMonster = 100;														 
		RegenInterval = 0.5f;			

		SponableMonster.clear();												 
		SponableMonster.push_back("Musc2");											 
	}																			 
	else if (11 * 60 <= LevelTime && LevelTime < 12 * 60)//11분대 : Lionhead, MedusaHead
	{
		Monster::MonsterName = "MedusaHeadBoss"; // 보스 추가 필요함
		Monster* Boss = CreateActor<Monster>(VSRenderOrder::Monster);
		Boss->SetBoxBossOn();

		MaxMonster = 120;
		RegenInterval = 2.0f;

		SponableMonster.clear();
		SponableMonster.push_back("MedusaHead");
		SponableMonster.push_back("LionHead");
	}
	else if (12 * 60 <= LevelTime && LevelTime < 13 * 60)//12분대 : Dullahan, MedusaHead
	{
		Monster::MonsterName = "GlowingBat";
		Monster* Boss = CreateActor<Monster>(VSRenderOrder::Monster);
		Boss->SetBoxBossOn();

		MaxMonster = 80;
		RegenInterval = 1.0f;

		SponableMonster.clear();
		SponableMonster.push_back("Dullahan");
		SponableMonster.push_back("MedusaHead");
	}
	else if (13 * 60 <= LevelTime && LevelTime < 14 * 60)//13분대 : Mummy, Dullahan,
	{
		Monster::MonsterName = "BigDust";
		Monster* Boss = CreateActor<Monster>(VSRenderOrder::Monster);
		Boss->SetBoxBossOn();

		MaxMonster = 120;
		RegenInterval = 0.5f;
		
		SponableMonster.clear();
		SponableMonster.push_back("Mummy");
		SponableMonster.push_back("Dullahan");
	}
	else if (14 * 60 <= LevelTime && LevelTime < 15 * 60) //14분대 : Mummy, Musc2, MedusaHead,
	{
		Monster::MonsterName = "SilverBat";
		Monster* Boss = CreateActor<Monster>(VSRenderOrder::Monster);
		Boss->SetBoxBossOn();

		MaxMonster = 300;
		RegenInterval = 0.1f;

		SponableMonster.clear();
		SponableMonster.push_back("Mummy");
		SponableMonster.push_back("Musc2");
		SponableMonster.push_back("MedusaHead");
	}
	else if (15 * 60 <= LevelTime && LevelTime < 16 * 60) //15분대 : MedusaHead,
	{		
		Monster::MonsterName = "QueenMedusa";
		Monster* Boss = CreateActor<Monster>(VSRenderOrder::Monster);
		Boss->SetBoxBossOn();

		MaxMonster = 100;																		 
		RegenInterval = 0.1f;	

		SponableMonster.clear();
		SponableMonster.push_back("MedusaHead");
	}
	else if (16 * 60 <= LevelTime && LevelTime < 17 * 60)//16분대 : Dullahan, EliteDullahan, ApprenticeWitch
	{
		Monster::MonsterName = "GlowingBat";
		Monster* Boss = CreateActor<Monster>(VSRenderOrder::Monster);
		Boss->SetBoxBossOn();

		MaxMonster = 100;
		RegenInterval = 1.0f;
		
		SponableMonster.clear();
		SponableMonster.push_back("Dullahan");
		SponableMonster.push_back("EliteDullahan");
		SponableMonster.push_back("ApprenticeWitch");
	}
	else if (17 * 60 <= LevelTime && LevelTime < 18 * 60)//17분대 : Musc, Musc2, ApprenticeWitch,
	{
		MaxMonster = 200;
		RegenInterval = 1.0f;
		SponableMonster.clear();
		SponableMonster.push_back("ApprenticeWitch");
		SponableMonster.push_back("Musc");
		SponableMonster.push_back("Musc2");
	}
	else if (18 * 60 <= LevelTime && LevelTime < 19 * 60)//18분대 : ApprenticeWitch, Lionhead
	{
		Monster::MonsterName = "MasterWitch";
		Monster* Boss = CreateActor<Monster>(VSRenderOrder::Monster);
		Boss->SetBoxBossOn();

		MaxMonster = 60;
		RegenInterval = 0.5f;

		SponableMonster.clear();
		SponableMonster.push_back("ApprenticeWitch");		  
		SponableMonster.push_back("LionHead");				
	}
	else if (19 * 60 <= LevelTime && LevelTime < 20 * 60)//19분대 : ApprenticeWitch, EliteDullahan,
	{
		MaxMonster = 120;
		RegenInterval = 0.5f;

		SponableMonster.clear();
		SponableMonster.push_back("ApprenticeWitch");
		SponableMonster.push_back("EliteDullahan");
	}
	else if (20 * 60 <= LevelTime && LevelTime < 21 * 60) //20분대 : EliteDullahan, Lionhead,
	{
		Monster::MonsterName = "Nesuferit";
		Monster* Boss = CreateActor<Monster>(VSRenderOrder::Monster);
		Boss->SetBoxBossOn();

		MaxMonster = 100;										 
		RegenInterval = 0.1f;									 
																 
		SponableMonster.clear();								 
		SponableMonster.push_back("ApprenticeWitch");				 
		SponableMonster.push_back("EliteDullahan");
	}
	else if (21 * 60 <= LevelTime && LevelTime < 22 * 60) // 21분대 : Lionhead
	{
		Monster::MonsterName = "GlowingBat";
		CreateActor<Monster>(VSRenderOrder::Monster);

		MaxMonster = 100;
		RegenInterval = 0.1f;

		SponableMonster.clear();
		SponableMonster.push_back("LionHead");
	}
	else if (22 * 60 <= LevelTime && LevelTime < 23 * 60)//22분대 : Lionhead, UndeadSassyWitch,
	{
		Monster::MonsterName = "GlowingBat";
		Monster* Boss = CreateActor<Monster>(VSRenderOrder::Monster);
		Boss->SetBoxBossOn();

		MaxMonster = 80;
		RegenInterval = 1.0f;

		SponableMonster.clear();
		SponableMonster.push_back("UndeadSassyWitch");
		//SponableMonster.push_back("Lionhead");
	}
	else if (23 * 60 <= LevelTime && LevelTime < 24 * 60)//23분대 : EliteDullahan, Dullahan, UndeadSassyWitch
	{
		Monster::MonsterName = "BigLionHead";
		Monster* Boss = CreateActor<Monster>(VSRenderOrder::Monster);
		Boss->SetBoxBossOn();

		MaxMonster = 120;
		RegenInterval = 0.1f;

		SponableMonster.clear();
		SponableMonster.push_back("EliteDullahan");
		SponableMonster.push_back("Dullahan");
		SponableMonster.push_back("UndeadSassyWitch");
	}
	else if (24 * 60 <= LevelTime && LevelTime < 25 * 60) // 24분대 : UndeadSassyWitch
	{
		MaxMonster = 300;
		RegenInterval = 0.1f;

		SponableMonster.clear();
		SponableMonster.push_back("UndeadSassyWitch");
	}
	else if (25 * 60 <= LevelTime && LevelTime < 26 * 60)//25분대 : GiantBat(흡혈박쥐), GlowingSkull(두개골), UndeadSassyWitch
	{
		Monster::MonsterName = "Hag";
		Monster* Boss = CreateActor<Monster>(VSRenderOrder::Monster);
		Boss->SetBoxBossOn();

		MaxMonster = 300;
		RegenInterval = 0.1f;

		SponableMonster.clear();
		SponableMonster.push_back("GiantBat");
		SponableMonster.push_back("GlowingSkull");
		SponableMonster.push_back("UndeadSassyWitch");
	}																				
	else if (26 * 60 <= LevelTime && LevelTime < 27 * 60)	//26분대 : GiantMedusa,	
	{			
		Monster::MonsterName = "QueenMedusa";
		Monster* Boss = CreateActor<Monster>(VSRenderOrder::Monster);
		Boss->SetBoxBossOn();

		MaxMonster = 100;															
		RegenInterval = 0.1f;	

		SponableMonster.clear();
		SponableMonster.push_back("GiantMedusa");

	}
	else if (27 * 60 <= LevelTime && LevelTime < 28 * 60)//27분대 : GiantMedusa, MedusaHead
	{
		Monster::MonsterName = "QueenMedusa";
		Monster* Boss = CreateActor<Monster>(VSRenderOrder::Monster);
		Boss->SetBoxBossOn();

		MaxMonster = 300;
		RegenInterval = 0.1f;

		SponableMonster.clear();
		//SponableMonster.push_back("GiantMedusa");
		SponableMonster.push_back("MedusaHead");
	}
	else if (28 * 60 <= LevelTime && LevelTime < 29 * 60)//28분대 : ApprenticeWitch,
	{
		Monster::MonsterName = "QueenMedusa";
		Monster* Boss = CreateActor<Monster>(VSRenderOrder::Monster);
		Boss->SetBoxBossOn();

		MaxMonster = 250;
		RegenInterval = 0.1f;

		SponableMonster.clear();
		SponableMonster.push_back("ApprenticeWitch");
	}
	else if (29 * 60 <= LevelTime && LevelTime < 30 * 60) //29분대 : MedusaHead, BigDust, BigMusc, ColossalLionhead,
	{
		MaxMonster = 250;
		RegenInterval = 0.1f;

		SponableMonster.clear();
		SponableMonster.push_back("MedusaHead");
		SponableMonster.push_back("BigDust");
		SponableMonster.push_back("BigMusc2");
		SponableMonster.push_back("BigLionhead");
	}
	else
	{
		MaxMonster = 1;
		RegenInterval = 10.0f;

		SponableMonster.clear();
		//SponableMonster.insert("Reaper");

	}

}
