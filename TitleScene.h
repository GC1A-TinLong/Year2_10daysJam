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
	void Animation();
	void Menuing();
	void Audio();
	void Draw() override;

	//Getter
	bool GetPressedExit() const { return hasPressedExit; };

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
	bool isSpaceClicked = false;
	bool finished_ = false;
	Vector2 pos_ = { 0.f, 0.f };
	Vector2 animationPos_ = { 0.f, 0.f };
	float animationFrames = 7680.f;
	int animationTimer_ = 0;
	int titleHandle_;
	bool hasPressedDown = false;
	int animationTimer = 0;
	int maxFrames = 60;
	int pressTimer = 0;
	bool hasPressedExit = false;

	//Audio
	int movementAudioHandle;
	int movementPlayHandle = -1;
	static inline const float kMovementAudioVolume = 0.05f;

	int selectAudioHandle;
	int selectPlayHandle = -1;
	static inline const float kSelectAudioVolume = 0.05f;
};
