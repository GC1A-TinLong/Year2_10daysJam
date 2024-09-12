#pragma once
#include "IScene.h"
#include "Input.h"
#include "Novice.h"
#include "Fade.h"

class ClearScene :public IScene
{
public:

	~ClearScene();
	void Initialize() override;
	void ChangePhase();
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

	Fade* fade_ = nullptr;
	float duration_ = 1.0f;
	Phase phase_;

	Vector2 pos_;
	Vector2 scale = { 1.f,1.f };
	Size size = { 1920 , 1080 };
	uint32_t texture_;
	uint32_t textTexture_;

	//Animation
	Vector2 animationPos_ = { 0.f, 0.f };
	float animationFrames = 3840.f;
	int animationTimer_ = 0;

};

