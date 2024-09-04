#pragma once
#include "IScene.h"
#include "Input.h"
#include "Novice.h"
#include "Player.h"

class StageScene :public IScene
{
public:
	~StageScene();

	void Initialize() override;
	void Update() override;
	void Draw() override;

private:
	Player* player_ = nullptr;
	uint32_t playerTexture = Novice::LoadTexture("./Resources/player.png");
};

