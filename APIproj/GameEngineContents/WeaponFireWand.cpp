#include "WeaponFireWand.h"
#include "ContentsEnums.h"
#include "Player.h"
#include <GameEngineCore/GameEngineLevel.h>
#include <GameEngineBase/GameEngineRandom.h>

#include "Monster.h"

WeaponFireWand::WeaponFireWand()
{
}

WeaponFireWand::~WeaponFireWand()
{
}


void WeaponFireWand::ReSet()
{
	if (0 == WeaponRender.size()) {
		return;
	}
	float4 _Pos = Player::MainPlayer->GetPos();
	_Pos.y -= 32;
	SetPos(_Pos);

	float4 MainDir = float4{ GameEngineRandom::MainRandom.RandomFloat(-1.0f, 1.0f) ,GameEngineRandom::MainRandom.RandomFloat(-1.0f, 1.0f) }.GetNormalize();

	int _Num = 0;/*GetNumOfWeapon();*/
	int index = 0;

	while (_Num< GetNumOfWeapon())
	{

		if (WeaponRender.size() - 1 < index) // ����ü�� ������ ��
		{
			Init();
		}

		if (true == WeaponRender[index]->IsUpdate()) // ���� Ȱ������ ����ü ����
		{
			index++;
			continue;
		}

		// off�� ����ü reset
		WeaponRender[index]->SetPosition(float4::Zero);   //��ġ ����
		WeaponCollision[index]->SetPosition(float4::Zero);

		Passes[index] = GetWeaponPass(); // ���� �� �ʱ�ȭ
		if (0 == (_Num & 1)) // ¦�����?
		{
			MainDir.RotaitonZDeg(static_cast<float>(_Num * 3));
			WeaponDir[index] = MainDir;
		}
		else // Ȧ�����?
		{
			MainDir.RotaitonZDeg(static_cast<float>(-_Num * 3));
			WeaponDir[index] = MainDir;
		}

		WeaponRender[index]->SetAngle(7); // float4{1, 0}��ġ����
		float GetAng = float4{ 1,0 }.GetAngelBetweenVec(WeaponDir[index]) * GameEngineMath::RadToDeg;
		WeaponRender[index]->SetAngleAdd(GetAng); // ȸ������ ����

		WeaponRender[index]->SetScale(GetWeaponRenderScale()); // ũ�� ����
		WeaponCollision[index]->SetScale(GetWeaponCollisionScale());

		DelayTime[index] = static_cast<float>(_Num) * -ProjectileInterval; // ���ư��� Ÿ�̹� �ٰ�ȭ

		WeaponRender[index]->On();
		WeaponCollision[index]->On();

		index++;
		++_Num;
	}

	WaitTime = 0;
}

bool WeaponFireWand::IsInScreen(float4 _Pos)
{
	CollisionData Screen = { Player::MainPlayer->GetPos() , GameEngineWindow::GetScreenSize() };
	if (Screen.Bot() > _Pos.y && Screen.Top() < _Pos.y && Screen.Left() < _Pos.x && Screen.Right() > _Pos.x)
	{
		return true;
	}
	return false;
}

void WeaponFireWand::Init() // ����ü ����
{
	{
		GameEngineRender* Render = CreateRender(VSRenderOrder::Weapon);
		Render->SetImage("FireWand.bmp");
		Render->SetScaleToImage();
		Render->SetRotFilter("FireWandBlack.bmp");

		GameEngineCollision* Collision = CreateCollision(VSRenderOrder::Weapon);
		Collision->SetScale({ 25,25 });

		WeaponRender.push_back(Render);
		WeaponCollision.push_back(Collision);
		WeaponDir.push_back(float4::Zero);
		Passes.push_back(1);
		SetWeaponScale(Render->GetScale(), Collision->GetScale());
		DelayTime.push_back(0.0f);
		Render->Off();
		Collision->Off();

	}
}

void WeaponFireWand::Start()
{
	SetWeaponName("FireWand");
	SetNumOfWeapon(3);
	SetCoolTime(3.0f);
	SetRunTime(10.0f);
	float _Dmg[9] = { 0.0f,20.0f,30.0f,40.0f,50.0f,60.0f,70.0f,80.0f,90.0f };
	SetDmg(_Dmg);
	SetWeaponSpeed(400.0f);

	Weapon::Weapons[GetWeaponName()] = this;

	for (int i = 0;i < GetNumOfWeapon();i++)
	{
		Init();
	}

	this->Off();
}

void WeaponFireWand::Update(float _DeltaTime)
{
	if (WeaponRender.size() == 0 || WeaponCollision.size() == 0)
	{
		MsgAssert("���ⷣ���� �������� �ʾҽ��ϴ�.");
		return;
	}

	/*if (WaitTime > GetRunTime())
	{
		for (int i = 0;i < WeaponRender.size();++i)
		{
			WeaponRender[i]->Off();
			WeaponCollision[i]->Off();
		}
		return;
	}*/



	for (int i = 0;i < WeaponRender.size();++i)
	{
		if (false == WeaponRender[i]->IsUpdate() || false == IsInScreen(GetPos()+WeaponRender[i]->GetPosition())) // �̹� off�� ����ü �Ǵ� ȭ������� ���� off�� ����ü
		{
			WeaponRender[i]->Off();
			WeaponCollision[i]->Off();
			continue;
		}
		if (DelayTime[i] < 0.0f) // ����ü ������Ÿ�� ����
		{
			DelayTime[i] += _DeltaTime;
			continue;
		}
		WeaponRender[i]->SetMove(WeaponDir[i] * _DeltaTime * GetWeaponSpeed());
		WeaponCollision[i]->SetMove(WeaponDir[i] * _DeltaTime * GetWeaponSpeed());
		std::vector<GameEngineCollision*> Collision;
		if (true == WeaponCollision[i]->Collision({ .TargetGroup = static_cast<int>(VSRenderOrder::Monster), .ThisColType = CollisionType::CT_CirCle }, Collision))
		{

			for (size_t i = 0; i < Collision.size(); i++)
			{
				GameEngineActor* ColActor = Collision[i]->GetActor();
				Monster* ColWeaponActor = dynamic_cast<Monster*> (ColActor);
				ColWeaponActor->Attack(GetDmg());
				--Passes[i];
				if (Passes[i] <= 0) {
					WeaponRender[i]->Off();
					WeaponCollision[i]->Off();
					return; // or Continue;
				}

			}
		}
	}
}
