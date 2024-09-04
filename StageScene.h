#pragma once
#include "IScene.h"
#include "Input.h"
#include "Novice.h"
#include "Player.h"
#include "Fade.h"
#include "Spike.h"
#include <vector>

class StageScene :public IScene
{
public:
	~StageScene();

	void Initialize() override;
	void Update() override;
	void ChangePhase();
	void Draw() override;

	void CheckAllCollision();

private:
	// Player
	Player* player_ = nullptr;
	uint32_t playerTexture = Novice::LoadTexture("./Resources/player.png");
	Fade* fade_ = nullptr;
	float duration_ = 1.0f;
	Phase phase_;

	// Spike
	static inline const uint8_t kSpikeNum = 15;
	std::vector<Spike*>spike_;
};

