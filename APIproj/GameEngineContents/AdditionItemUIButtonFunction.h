#pragma once
#include "AdditionItemUI.h"
#include "Player.h"

//0MaxHealth
//1Recovery
//2Armor
//3ActiveSpeed
//
//4Might
//5Area
//6Speed
//7Duration
//8Amount
//9Cooldown
//
//10Luck
//11Growth
//12Greed
//
//13Magnet
//
//14Revival
//15Reroll
//16Skip

void PushLevelupBracer()
{
	Player::MainPlayer->PushActive("Bracer");
	Player::MainPlayer->LevelUpUI = false;
}
void PushLevelupCandle()
{
	Player::MainPlayer->PushActive("Candle");
	Player::MainPlayer->LevelUpUI = false;
}
void PushLevelupClover()
{
	Player::MainPlayer->PushActive("Clover");
	Player::MainPlayer->LevelUpUI = false;
}
void PushLevelupEmptytome()
{
	Player::MainPlayer->PushActive("Emptytome");
	Player::MainPlayer->LevelUpUI = false;
}
void PushLevelupFirewand()
{
	Player::MainPlayer->PushWeapon("FireWand");
	Player::MainPlayer->LevelUpUI = false;
}
void PushLevelupHp()
{
	Player::MainPlayer->PushActive("Hp");
	Player::MainPlayer->LevelUpUI = false;
}
void PushLevelupKingBible()
{
	Player::MainPlayer->PushWeapon("KingBible");
	Player::MainPlayer->LevelUpUI = false;
}
void PushLevelupKnife()
{
	Player::MainPlayer->PushWeapon("Knife");
	Player::MainPlayer->LevelUpUI = false;
}
void PushLevelupMagicwand()
{
	Player::MainPlayer->PushWeapon("MagicWand");
	Player::MainPlayer->LevelUpUI = false;
}
void PushLevelupMagnet()
{
	Player::MainPlayer->PushActive("Magnet");
	Player::MainPlayer->LevelUpUI = false;
}
void PushLevelupMoney()
{
	//Player::MainPlayer->PushWeapon("Money");
	Player::MainPlayer->LevelUpUI = false;
}
void PushLevelupWhip()
{
	Player::MainPlayer->PushWeapon("Whip");
	Player::MainPlayer->LevelUpUI = false;
}
void PushLevelupRunetracer()
{
	Player::MainPlayer->PushWeapon("RuneTracer");
	Player::MainPlayer->LevelUpUI = false;
}
void PushLevelupSpinach()
{
	Player::MainPlayer->PushActive("Spinach");
	Player::MainPlayer->LevelUpUI = false;
}
void PushLevelupWing()
{
	Player::MainPlayer->PushActive("Wing");
	Player::MainPlayer->LevelUpUI = false;
}
void PushLevelupDuplicator()
{
	Player::MainPlayer->PushActive("Duplicator");
	Player::MainPlayer->LevelUpUI = false;
}
void PushLevelupPummarola()
{
	Player::MainPlayer->PushActive("Pummarola");
	Player::MainPlayer->LevelUpUI = false;
}
void PushLevelupSpellbinder()
{
	Player::MainPlayer->PushActive("Spellbinder");
	Player::MainPlayer->LevelUpUI = false;
}
void PushLevelupCrown()
{
	Player::MainPlayer->PushActive("Crown");
	Player::MainPlayer->LevelUpUI = false;
}
void PushLevelupHollowHeart()
{
	Player::MainPlayer->PushActive("HollowHeart");
	Player::MainPlayer->LevelUpUI = false;
}
void PushLevelupArmor()
{
	Player::MainPlayer->PushActive("Armor");
	Player::MainPlayer->LevelUpUI = false;
}