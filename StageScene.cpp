#include "StageScene.h"

StageScene::~StageScene()
{
	delete player_;
}

void StageScene::Initialize()
{
	// Player
	player_ = new Player;
	player_->Initialize({ 640,400 });

	// Spike
	spike_.resize(kSpikeNum);
	for (int i = 0; i < kSpikeNum; i++)
	{
		spike_[i] = new Spike;
		int initPosX = 300;
		spike_[i]->Initialize({ initPosX + i * 48,0 });
	}
}

void StageScene::Update()
{
	// Player
	player_->Update();

	// Spike
	for (auto* spike : spike_) {
		spike->Update();
	}

	if (Input::GetInstance()->TriggerKey(DIK_SPACE)) {
		sceneNo = CLEAR;
	}
}

void StageScene::Draw()
{
	// Player
	player_->Draw();

	// Spike
	for (auto* spike : spike_) {
		spike->Draw();
	}
}

void StageScene::CheckAllCollision()
{
#pragma region player & spike collision
	/*for (int i = 0; i < kSpikeNum; i++)
	{
		if(isCollideBox()
	}*/

#pragma endregion

#pragma region player & item collision

#pragma endregion
}
