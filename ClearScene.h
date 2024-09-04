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

};

