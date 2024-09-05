#pragma once
#include "IScene.h"
#include "Input.h"
#include "Novice.h"
#include "Fade.h"

class TitleScene :public IScene
{
public:
	~TitleScene();

	void Initialize() override;
	void Update() override;
	void Draw() override;

private:
	enum class Phase
	{
		kFadeIn,
		kPlay,
		kDeath,
		kStageClear,
		kFadeOut,
	};

	//uint32_t textureHandle_ = Novice::LoadTexture("./Resources/title.png");
	Fade* fade_ = nullptr;
	float duration_ = 1.0f;
	Phase phase_;
	bool isSpaceClicked = false;
	bool finished_ = false;
};
