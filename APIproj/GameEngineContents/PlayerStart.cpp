#include "Player.h"
#include <GameEnginePlatform/GameEngineInput.h>
#include "ContentsEnums.h"

void Player::Start()
{
	MainPlayer = this;
	if ("" == PlayerName) {
		MsgAssert("플레이어가 선택되지 않았습니다.");
		return;
	}

	//SetMove(GameEngineWindow::GetScreenSize().half());
	//SetPos(GameEngineWindow::GetScreenSize().half());
	//SetMove(float4{2048,948});

	if (false == GameEngineInput::IsKey("LeftMove"))
	{
		GameEngineInput::CreateKey("LeftMove", 'A');
		GameEngineInput::CreateKey("RightMove", 'D');
		GameEngineInput::CreateKey("DownMove", 'S');
		GameEngineInput::CreateKey("UpMove", 'W');
	}
	if ("Antonio" == PlayerName)
	{
		Hp = 120;
	}

	std::string RImage = "Right" + PlayerName + ".BMP";
	std::string LImage = "Left" + PlayerName + ".BMP";
	std::string DmgRImage = "Right" + PlayerName + "Dmged.BMP";
	std::string DmgLImage = "Left" + PlayerName + "Dmged.BMP";

	{
		AnimationRender = CreateRender(VSRenderOrder::Player);
		AnimationRender->SetScale({ 70, 140 }); // 실제 크기 64 x 64
		{
			AnimationRender->CreateAnimation({ .AnimationName = "Right_Idle",  .ImageName = RImage, .Start = 3, .End = 3 , .Loop = false }); //RightAntonio.bmp
			AnimationRender->CreateAnimation({ .AnimationName = "Right_Move",  .ImageName = RImage, .Start = 0, .End = 3, .InterTime = 0.1f });
			AnimationRender->CreateAnimation({ .AnimationName = "Right_Idle_Dmged",  .ImageName = DmgRImage, .Start = 3, .End = 3, .Loop = false });
			AnimationRender->CreateAnimation({ .AnimationName = "Right_Move_Dmged",  .ImageName = DmgRImage, .Start = 0, .End = 3, .InterTime = 0.1f });
		}
		{
			AnimationRender->CreateAnimation({ .AnimationName = "Left_Idle",  .ImageName = LImage, .Start = 3, .End = 3, .Loop = false });
			AnimationRender->CreateAnimation({ .AnimationName = "Left_Move",  .ImageName = LImage, .Start = 0, .End = 3, .InterTime = 0.1f });
			AnimationRender->CreateAnimation({ .AnimationName = "Left_Idle_Dmged",  .ImageName = DmgLImage, .Start = 3, .End = 3, .Loop = false });
			AnimationRender->CreateAnimation({ .AnimationName = "Left_Move_Dmged",  .ImageName = DmgLImage, .Start = 0, .End = 3, .InterTime = 0.1f });
		}
		GameEngineRender* HpBlackBar = CreateRender("HpBlackBar.bmp", VSRenderOrder::Player);
		HpBlackBar->SetScaleToImage();
		HpBlackBar->SetPosition({ 0,HpBlackBar->GetScale().y });

		HpRedBar = CreateRender("HpRedBar.bmp", VSRenderOrder::Player);
		HpRedBar->SetPosition({ 0,HpBlackBar->GetScale().y });
		MaxHpScale = HpBlackBar->GetScale();
	}

	{
		BodyCollision = CreateCollision(VSRenderOrder::Player);
		BodyCollision->SetScale({ 64, 64 });
		BodyCollision->SetPosition({ 0, -BodyCollision->GetScale().hy() });
	}

	{
		MyWeapon.push_back(Weapon::Weapons[BasicWeapon]);
		MyWeapon.back()->On();
		/*MyWeapon.push_back(Weapon::Weapons["RuneTracer"]);
		MyWeapon.back()->On();*/
		/*MyWeapon.push_back(Weapon::Weapons["Whip"]);
		MyWeapon.push_back(Weapon::Weapons["MagicWand"]);*/
		//MyWeapon.push_back(Weapon::Weapons["Knife"]);
	}
	/*for (Weapon* arm : MyWeapon) {
		arm->ReSet();
	}*/

	ChangeState(PlayerState::IDLE); // 시작 시 기본 상태 설정
}