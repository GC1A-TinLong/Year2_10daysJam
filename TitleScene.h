#pragma once
#include "IScene.h"
#include "Input.h"
#include "Novice.h"
#include "Fade.h"

enum class Phase
{
	kFadeIn,
	kPlay,
	kDeath,
	kStageClear,
	kFadeOut,
};

class TitleScene :public IScene
{
public:
	void Initialize() override;
	void Update() override;
	void Draw() override;

private:
	//uint32_t textureHandle_ = Novice::LoadTexture("./Resources/title.png");
	Fade* fade_ = nullptr;
	float duration_ = 1.0f;
	Phase phase_;
};
