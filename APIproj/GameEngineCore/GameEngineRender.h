#pragma once
 
 // �������� ���õ� ����� ��� �����Ѵ�.
 // ���͸� �ϳ��� ������ �� �� ���� ������� �̹����� �ִ� ex) player�� ������� HP bar
 // actor���� render�� list�� �����Ͽ� ���������� ������ �� �� �ֵ���
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

