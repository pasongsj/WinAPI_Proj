#pragma once
 
 // 랜더링에 관련된 기능을 모두 집약한다.
 // 액터를 하나를 랜더링 할 때 같이 따라오는 이미지가 있다 ex) player에 따라오는 HP bar
 // actor에서 render를 list로 보관하여 연쇄적으로 랜더링 할 수 있도록
class GameEngineRender
{
public:
	// constrcuter destructer
	GameEngineRender() ;
	~GameEngineRender();

	// delete Function
	GameEngineRender(const GameEngineRender& _Other) = delete;
	GameEngineRender(GameEngineRender&& _Other) noexcept = delete;
	GameEngineRender& operator=(const GameEngineRender& _Other) = delete;
	GameEngineRender& operator=(GameEngineRender&& _Other) noexcept = delete;

protected:

private:

};

