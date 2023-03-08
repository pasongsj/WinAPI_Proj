#pragma once
#include <GameEngineCore/GameEngineActor.h>

class Button;
class ObtainBox : public GameEngineActor
{
public:
	static ObtainBox* ObtainBoxAni;
	// constrcuter destructer
	ObtainBox() ;
	~ObtainBox();

	// delete Function
	ObtainBox(const ObtainBox& _Other) = delete;
	ObtainBox(ObtainBox&& _Other) noexcept = delete;
	ObtainBox& operator=(const ObtainBox& _Other) = delete;
	ObtainBox& operator=(ObtainBox&& _Other) noexcept = delete;

	void UIOn();
	void UIOff();

	void OpeningBoxAnimation();
	bool IsOpened = false;

protected:

	void Start() override;
	void Update(float _DeltaTime) override;

private:
	float GoldBox = 3.0f;
	float SilverBox = /*13.0f;*/ 90.0f;
	float BronzeBox = 100.0f;
	float AnimationTime = 0.0f;

	GameEngineRender* ObtainBoxUI = nullptr;
	GameEngineRender* OpenedBoxUI = nullptr;
	GameEngineRender* OpeningAnimation = nullptr;

	Button* OpenBoxButton = nullptr;
	Button* CloseUIButton = nullptr;

};

