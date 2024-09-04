#include "StageScene.h"

StageScene::~StageScene()
{
	delete player_;
	delete fade_;
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

#pragma region Fade

	phase_ = Phase::kFadeIn;
	fade_ = new Fade();
	fade_->Initialize();
	fade_->Start(Status::FadeIn, duration_);

#pragma endregion

}

void StageScene::Update()
{
	ChangePhase();
	switch (phase_)
	{
	case StageScene::Phase::kFadeIn:
		fade_->Update();
		break;

	case StageScene::Phase::kPlay:
		// Player
		player_->Update();

		// Spike
		for (auto* spike : spike_) {
			spike->Update();
		}
		
		break;
	case StageScene::Phase::kDeath:
		break;
	case StageScene::Phase::kStageClear:
		break;

	case StageScene::Phase::kFadeOut:
		fade_->Update();
		break;
	}

	
}

void StageScene::ChangePhase()
{
	switch (phase_)
	{
	case StageScene::Phase::kFadeIn:
		if (fade_->IsFinished())
		{
			phase_ = Phase::kPlay;
		}
		break;

	case StageScene::Phase::kPlay:
		if (Input::GetInstance()->TriggerKey(DIK_SPACE))
		{
			fade_->Start(Status::FadeOut, duration_);
			phase_ = Phase::kFadeOut;
		}
		break;

	case StageScene::Phase::kDeath:
		break;
	case StageScene::Phase::kStageClear:
		break;
	case StageScene::Phase::kFadeOut:
		if (fade_->IsFinished()) {
			sceneNo = CLEAR;
		}
		break;
	}
}

void StageScene::Draw()
{
	switch (phase_)
	{
	case StageScene::Phase::kFadeIn:
		// Player
		player_->Draw();
		// Fade
		fade_->Draw();
		break;
	case StageScene::Phase::kPlay:
		// Player
		player_->Draw();

		// Spike
		for (auto* spike : spike_) {
			spike->Draw();
		}
		break;
	case StageScene::Phase::kDeath:
		break;
	case StageScene::Phase::kStageClear:
		break;

	case StageScene::Phase::kFadeOut:
		fade_->Draw();
		break;
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
