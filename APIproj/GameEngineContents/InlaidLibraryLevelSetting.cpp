#include "InlaidLibraryLevel.h"

#include "Player.h"
//00�д� : Dust,
//01�д� : Dust(����)
//02�д� : Dust, Musc(Ectoplasm)
//03�д� : Mummy,
//04�д� : Dust, Mummy
//05�д� : Mummy,
//06�д� : Dullahan, Musc
//07�д� : Dullahan, Musc, Musc2
//08�д� : Ghost, Musc,
//09�д� : Ghost, Mummy
//10�д� : Musc,
//11�д� : Lionhead, ColossalMedusaHead
//12�д� : Dullahan, MedusaHead,
//13�д� : Mummy, Dullahan,
//14�д� : Mummy, Musc2, MedusaHead,
//15�д� : MedusaHead,
//16�д� : Dullahan, EliteDullahan, ApprenticeWitch
//17�д� : Musc, Musc2, ApprenticeWitch,
//18�д� : ApprenticeWitch, Lionhead
//19�д� : ApprenticeWitch, EliteDullahan,
//20�д� : EliteDullahan, Lionhead,
//21�д� : Lionhead
//22�д� : Lionhead, UndeadSassyWitch,
//23�д� : EliteDullahan, Dullahan, UndeadSassyWitch
//24�д� : UndeadSassyWitch
//25�д� : GiantBat(��������), GlowingSkull(�ΰ���), UndeadSassyWitc
//26�д� : GiantMedusa,
//27�д� : GiantMedusa, MedusaHead
//28�д� : ApprenticeWitch,
//29�д� : ColossalMedusaHead, BigDust, BigMusc, ColossalLionhead,

void InlaidLibraryLevel::SetState(float _DeltaTime)
{
	if (Player::IsStop == true)
	{
		return;
	}
	LevelTime += _DeltaTime;

	if (0 <= LevelTime && LevelTime < 1 * 60)//00�д� : Dust,
	{
		MaxMonster = 50;
		RegenInterval = 3.0f;

		SponableMonster.clear();
		SponableMonster.insert("Dust");
	}
	else if (1 * 60 <= LevelTime && LevelTime < 2 * 60)//01�д� : Dust(����)
	{
		MaxMonster = 80;
		RegenInterval = 3.0f;

		SponableMonster.clear();
		SponableMonster.insert("Dust");
	}
	else if (2 * 60 <= LevelTime && LevelTime < 3 * 60)//02�д� : Dust, Musc(Ectoplasm)
	{
		MaxMonster = 100;
		RegenInterval = 4.0f;

		SponableMonster.clear();
		SponableMonster.insert("Dust");
		SponableMonster.insert("Musc");
	}
	else if (3 * 60 <= LevelTime && LevelTime < 4 * 60)//03�д� : Mummy,
	{
		MaxMonster = 60;
		RegenInterval = 4.0f;

		SponableMonster.clear();
		SponableMonster.insert("Mummy");
	}
	else if (4 * 60 <= LevelTime && LevelTime < 5 * 60)//04�д� : Dust, Mummy
	{
		MaxMonster = 100;
		RegenInterval = 4.0f;

		SponableMonster.clear();
		SponableMonster.insert("Dust");
		SponableMonster.insert("Mummy");
	}
	else if (5 * 60 <= LevelTime && LevelTime < 6 * 60)	//05�д� : Mummy,			
	{																			   
		MaxMonster = 100;														   
		RegenInterval = 4.0f;		

		SponableMonster.clear();
		SponableMonster.insert("Mummy");										   
	}
	else if (6 * 60 <= LevelTime && LevelTime < 7 * 60)//06�д� : Dullahan, Musc
	{
		MaxMonster = 30;
		RegenInterval = 2.0f;

		SponableMonster.clear();
		SponableMonster.insert("Dullahan");
		SponableMonster.insert("Musc");
	}
	else if (7 * 60 <= LevelTime && LevelTime < 8 * 60)//07�д� : Dullahan, Musc, Musc2
	{
		MaxMonster = 80;
		RegenInterval = 2.0f;

		SponableMonster.clear();
		SponableMonster.insert("Musc");
		//SponableMonster.insert("Musc2");
		SponableMonster.insert("Mummy");
	}
	else if (8 * 60 <= LevelTime && LevelTime < 9 * 60)//08�д� : Ghost, Musc,
	{
		MaxMonster = 80;
		RegenInterval = 1.0f;
		

		SponableMonster.clear();
		SponableMonster.insert("Ghost");
		SponableMonster.insert("Musc");
	}
	else if (9 * 60 <= LevelTime && LevelTime < 10 * 60)//09�д� : Ghost, Mummy
	{
		MaxMonster = 200;
		RegenInterval = 0.5f;

		SponableMonster.clear();
		SponableMonster.insert("Ghost");
		SponableMonster.insert("Mummy");
	}
	else if (10 * 60 <= LevelTime && LevelTime < 11 * 60)//10�д� : Musc,
	{
		MaxMonster = 100;														 
		RegenInterval = 0.5f;			

		SponableMonster.clear();												 
		SponableMonster.insert("Musc");											 
	}																			 
	else if (11 * 60 <= LevelTime && LevelTime < 12 * 60)//11�д� : Lionhead, MedusaHead
	{
		MaxMonster = 120;
		RegenInterval = 2.0f;

		SponableMonster.clear();
		SponableMonster.insert("MedusaHead");
		SponableMonster.insert("LionHead");
	}
	else if (12 * 60 <= LevelTime && LevelTime < 13 * 60)//12�д� : Dullahan, MedusaHead
	{
		MaxMonster = 80;
		RegenInterval = 1.0f;

		SponableMonster.clear();
		SponableMonster.insert("Dullahan");
		//SponableMonster.insert("MedusaHead");
	}
	else if (13 * 60 <= LevelTime && LevelTime < 14 * 60)//13�д� : Mummy, Dullahan,
	{
		MaxMonster = 120;
		RegenInterval = 0.5f;
		
		SponableMonster.clear();
		SponableMonster.insert("Mummy");
		SponableMonster.insert("Dullahan");
	}
	else if (14 * 60 <= LevelTime && LevelTime < 15 * 60) //14�д� : Mummy, Musc2, MedusaHead,
	{
		MaxMonster = 300;
		RegenInterval = 0.1f;

		SponableMonster.clear();
		SponableMonster.insert("Mummy");
		//SponableMonster.insert("Musc2");
		//SponableMonster.insert("MedusaHead");
	}
	else if (15 * 60 <= LevelTime && LevelTime < 16 * 60) //15�д� : MedusaHead,
	{																							 
		MaxMonster = 100;																		 
		RegenInterval = 0.1f;	

		SponableMonster.clear();
		//SponableMonster.insert("MedusaHead");
	}
	else if (16 * 60 <= LevelTime && LevelTime < 17 * 60)//16�д� : Dullahan, EliteDullahan, ApprenticeWitch
	{
		MaxMonster = 100;
		RegenInterval = 1.0f;
		
		SponableMonster.clear();
		SponableMonster.insert("Dullahan");
		//SponableMonster.insert("EliteDullahan");
		//SponableMonster.insert("ApprenticeWitch");
	}
	else if (17 * 60 <= LevelTime && LevelTime < 18 * 60)//17�д� : Musc, Musc2, ApprenticeWitch,
	{
		MaxMonster = 200;
		RegenInterval = 1.0f;
		SponableMonster.clear();
		//SponableMonster.insert("ApprenticWitch");
		SponableMonster.insert("Musc");
		//SponableMonster.insert("BigMusc");
	}
	else if (18 * 60 <= LevelTime && LevelTime < 19 * 60)//18�д� : ApprenticeWitch, Lionhead
	{
		MaxMonster = 60;
		RegenInterval = 0.5f;

		SponableMonster.clear();
		//SponableMonster.insert("ApprenticWitch");		  
		SponableMonster.insert("LionHead");				
	}
	else if (19 * 60 <= LevelTime && LevelTime < 20 * 60)//19�д� : ApprenticeWitch, EliteDullahan,
	{
		MaxMonster = 120;
		RegenInterval = 0.5f;

		SponableMonster.clear();
		//SponableMonster.insert("ApprenticWitch");
		//SponableMonster.insert("EliteDullahan");
	}
	else if (20 * 60 <= LevelTime && LevelTime < 21 * 60) //20�д� : EliteDullahan, Lionhead,
	{
		MaxMonster = 100;										 
		RegenInterval = 0.1f;									 
																 
		SponableMonster.clear();								 
		//SponableMonster.insert("ApprenticWitch");				 
		//SponableMonster.insert("EliteDullahan");
	}
	else if (21 * 60 <= LevelTime && LevelTime < 22 * 60) // 21�д� : Lionhead
	{
		MaxMonster = 100;
		RegenInterval = 0.1f;

		SponableMonster.clear();
		SponableMonster.insert("Lionhead");
	}
	else if (22 * 60 <= LevelTime && LevelTime < 23 * 60)//22�д� : Lionhead, UndeadSassyWitch,
	{
		MaxMonster = 80;
		RegenInterval = 1.0f;

		SponableMonster.clear();
		SponableMonster.insert("Lionhead");
		//SponableMonster.insert("UndeadSassyWitch");
	}
	else if (23 * 60 <= LevelTime && LevelTime < 24 * 60)//23�д� : EliteDullahan, Dullahan, UndeadSassyWitch
	{
		MaxMonster = 120;
		RegenInterval = 0.1f;

		SponableMonster.clear();
		//SponableMonster.insert("EliteDullahan");
		SponableMonster.insert("Dullahan");
		//SponableMonster.insert("UndeadSassyWitch");
	}
	else if (24 * 60 <= LevelTime && LevelTime < 25 * 60) // 24�д� : UndeadSassyWitch
	{
		MaxMonster = 300;
		RegenInterval = 0.1f;

		SponableMonster.clear();
		//SponableMonster.insert("UndeadSassyWitch");
	}
	else if (25 * 60 <= LevelTime && LevelTime < 26 * 60)//25�д� : GiantBat(��������), GlowingSkull(�ΰ���), UndeadSassyWitch
	{
		MaxMonster = 300;
		RegenInterval = 0.1f;

		SponableMonster.clear();
		//SponableMonster.insert("GiantBat");
		//SponableMonster.insert("GlowingSkull");
		//SponableMonster.insert("UndeadSassyWitch");
	}																				
	else if (26 * 60 <= LevelTime && LevelTime < 27 * 60)	//26�д� : GiantMedusa,	
	{																				
		MaxMonster = 100;															
		RegenInterval = 0.1f;	

		SponableMonster.clear();
		//SponableMonster.insert("GiantMedusa");

	}
	else if (27 * 60 <= LevelTime && LevelTime < 28 * 60)//27�д� : GiantMedusa, MedusaHead
	{
		MaxMonster = 300;
		RegenInterval = 0.1f;

		SponableMonster.clear();
		//SponableMonster.insert("GiantMedusa");
		//SponableMonster.insert("MedusaHead");
	}
	else if (28 * 60 <= LevelTime && LevelTime < 29 * 60)//28�д� : ApprenticeWitch,
	{
		MaxMonster = 250;
		RegenInterval = 0.1f;

		SponableMonster.clear();
		//SponableMonster.insert("ApprenticWitch");
	}
	else if (29 * 60 <= LevelTime && LevelTime < 30 * 60) //29�д� : MedusaHead, BigDust, BigMusc, ColossalLionhead,
	{
		MaxMonster = 250;
		RegenInterval = 0.1f;

		SponableMonster.clear();
		SponableMonster.insert("MedusaHead");
		//SponableMonster.insert("BigDust");
		//SponableMonster.insert("BigMusc");
		//SponableMonster.insert("ColossalLionhead");
	}
	else
	{
		MaxMonster = 1;
		RegenInterval = 10.0f;

		SponableMonster.clear();
		//SponableMonster.insert("Reaper");

	}

}
