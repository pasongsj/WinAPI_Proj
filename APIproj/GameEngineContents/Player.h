#pragma once
#include <GameEngineCore/GameEngineResources.h>
#include <GameEngineCore/GameEngineActor.h>
#include <vector>
#include "Weapon.h"

enum class PlayerState
{
	IDLE,
	MOVE,
	IDLE_DMGED,
	MOVE_DMGED,
};

class Active
{
public:

	float MaxHealth		= 100;	//�ִ�ü�� ��
	float Recovery		= 0;		// ȸ�� ��
	int	  Armor			= 0;			// ���� ����1�� 10%������ �ݰ� �� 
	float ActiveSpeed	= 100;	// �̵��ӵ� % ��

	float Might			= 100;		// ���� % ��
	float Area			= 100;		// ���ݹ��� % ��
	float Speed			= 100;		// ����ü �ӵ� % ��
	float Duration		= 100;	// ���ӽð� % �� 
	int   Amount		= 0;			// ����ü �� ��
	float Cooldown		= 100;	// ��Ÿ�� % ��

	float Luck			= 100;			// ��� %
	float Growth		= 0;			// ����% ��
	int   Greed			= 100;		// Ž��%  Ž�� ��ġ�� ���� ��� ȹ�淮�� < (�⺻ ��ġ + �߰� �ɷ�ġ) x �������� ��� ���ʽ� >
	
	int   Magnet		= 0;		    // �ڼ� ��

	int   Revival		= 0;		// ��Ȱ
	int   Reroll		= 0;			// ���ΰ�ħ
	int   Skip			= 0;			// �ǳʶٱ�
};

class ActiveLevel
{
public:
	int LevelBracer		 = 0;
	int LevelCandle		 = 0;
	int LevelClover		 = 0;
	int LevelEmptytome	 = 0;
	int LevelMagnet		 = 0;
	int LevelSpinach	 = 0;
	int LevelWing		 = 0;
	int LevelDuplicator	 = 0;
	int LevelPummarola	 = 0;
	int LevelSpellbinder = 0;
	int LevelCrown		 = 0;
	int LevelHollowHeart = 0;
	int LevelArmor		 = 0;
};


class Player : public GameEngineActor
{
public:
	static bool IsStop;

	static Player* MainPlayer;
	static std::string PlayerName;
	static std::string BasicWeapon;

	bool LevelUpUI = false;
	bool OpenBoxUI = false;
	// constrcuter destructer
	Player() ;
	~Player();

	// delete Function
	Player(const Player& _Other) = delete;
	Player(Player&& _Other) noexcept = delete;
	Player& operator=(const Player& _Other) = delete;
	Player& operator=(Player&& _Other) noexcept = delete;

	inline int GetPlayerLevel()
	{
		return PlayerLevel;
	}

	inline void Attack(float _Att) {
		Hp -= _Att;
	}
	inline void SetHp(float _Hp) {
		Hp = _Hp;
	}

	inline float GetHp() {
		return Hp;
	}

	inline float GetPlayerExp()
	{
		return PlayerExp;
	}

	inline std::string GetDirString() {
		return DirString;
	}

	inline float4 GetLastMoveVec()
	{
		return LastMoveVec;
	}
	inline void SetLastMoveVec(const float4& _Vec)
	{
		LastMoveVec = _Vec;
	}

	int GetMaxExp();

	void PushWeapon(const std::string_view& _Weapon);
	void PushActive(const std::string_view& _Active);

	Active GetPlayerActive()
	{
		return PlayerActive;
	}

	void CollisionOnOff()
	{
		BodyCollision->OnOffSwtich();
	}

	void GetHp(float _Hp)
	{
		if (Hp + _Hp > PlayerActive.MaxHealth)
		{
			Hp = PlayerActive.MaxHealth;
		}
		else Hp += _Hp;
	}
 
	void SetBGSize(const float4& _Size)
	{
		BGSize = _Size;
	}

	/*std::vector<std::pair<int, std::string>> GetWeapon()
	{
		std::vector<std::pair<int, std::string>> _Return;
		for (Weapon* _Weapon : MyWeapon)
		{
			_Return.push_back(make_pair(_Weapon->GetWeaponLevel(), _Weapon->GetWeaponName()));
		}

	}*/

protected:
	void Start() override;
	void Update(float _DeltaTime) override;
	void Render(float _DeltaTime) override;

private:
	float4 BGSize = float4::Zero;

	Active PlayerActive;
	ActiveLevel PlayerActiveLevel;

	//float AccTime = 0.0f;
	int StartFrame = 0;
	float MoveSpeed = 300.0f;
	float4 MoveVec = float4::Zero;
	float4 LastMoveVec = float4::Zero;

	float Hp = 100;
	float PlayerExp = 0;
	int PlayerLevel = 1;
	float DmgedAnimationDelay = 0.0f;//��������
	//float4 HpbarScale = { 70, 9 };

	PlayerState StateValue = PlayerState::IDLE;
	std::string DirString = "Right_";

	GameEngineRender* AnimationRender = nullptr;
	GameEngineCollision* BodyCollision = nullptr;
	std::vector<Weapon*> MyWeapon;

	GameEngineRender* HpRedBar = nullptr;
	float4 MaxHpScale = float4::Zero;

	void DirCheck(const std::string_view& _AnimationName);// ����üũ

	// State
	void ChangeState(PlayerState _State); // Idle, Move ������ȯ
	void UpdateState(float _Time);

	// FSM ���� ����� �Ҷ� �̵��ϸ鼭 ������ ������ ����.
	void IdleStart();
	void IdleUpdate(float _Time);
	void IdleEnd();

	void MoveStart();
	void MoveUpdate(float _Time);
	void MoveEnd();

	void IdleDmgedStart();
	void IdleDmgedUpdate(float _Time);
	void IdleDmgedEnd();

	void MoveDmgedStart();
	void MoveDmgedUpdate(float _Time);
	void MoveDmgedEnd();

	// �Լ��и�
	void PressMove();
	bool CheckMonsterCollision();
	void Movecalculation(float _DeltaTime);


	void WeaponUpdate(float _DeltaTime);
	void CheckLevelUp();
	
	void UpdateActiveItem(float _DeltaTime);

	void CheckObtainItems();

	//GameEngineSoundPlayer ExpGemPlayer = GameEngineResources::GetInst().SoundPlayToControl("GetGem.mp3");
};

