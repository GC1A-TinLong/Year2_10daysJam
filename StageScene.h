#pragma once
#include "IScene.h"
#include "Input.h"
#include "Novice.h"
#include "Player.h"
#include "Fade.h"

class StageScene :public IScene
{
public:
	~StageScene();

	void Initialize() override;
	void Update() override;
	void ChangePhase();
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

	Player* player_ = nullptr;
	uint32_t playerTexture = Novice::LoadTexture("./Resources/player.png");
	Fade* fade_ = nullptr;
	float duration_ = 1.0f;
	Phase phase_;
};

