#pragma once
#include <GameEngineCore/GameEngineActor.h>

enum class PlayerState
{
	IDLE,
	MOVE,
};

class Player : public GameEngineActor
{
public:
	static Player* MainPlayer;

	// constrcuter destructer
	Player() ;
	~Player();

	// delete Function
	Player(const Player& _Other) = delete;
	Player(Player&& _Other) noexcept = delete;
	Player& operator=(const Player& _Other) = delete;
	Player& operator=(Player&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;
	void Render(float _DeltaTime) override;

private:
	float AccTime = 0.0f;
	int StartFrame = 0;
	float MoveSpeed = 1000.0f;
	float4 MoveVec = float4::Zero;

	GameEngineRender* AnimationRender = nullptr;

	PlayerState StateValue = PlayerState::IDLE;
	std::string DirString = "Right_";

	void DirCheck(const std::string_view& _AnimationName);// 방향체크

	// State
	void ChangeState(PlayerState _State); // Idle, Move 상태전환
	void UpdateState(float _Time);

	// FSM 내가 어떤일을 할때 이동하면서 가만히 있을수 없다.
	void IdleStart();
	void IdleUpdate(float _Time);
	void IdleEnd();

	void MoveStart();
	void MoveUpdate(float _Time);
	void MoveEnd();
	void Movecalculation(float _DeltaTime);
};

