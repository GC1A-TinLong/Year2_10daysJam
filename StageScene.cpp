#include "StageScene.h"

StageScene::~StageScene()
{
	delete player_;
	delete fade_;
	for (auto* spike : spike_) {
		delete spike;
	}
	spike_.clear();
}

void StageScene::Initialize()
{
	// Player
	player_ = new Player;
	player_->Initialize({ 640.f,400.f });

	// Spike
	spike_.resize(kSpikeNum);
	for (int i = 0; i < kSpikeNum; i++)
	{
		spike_[i] = new Spike;
		float initPosX = 300.f;
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
		CheckAllCollision();

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
		// Fade
		fade_->Draw();
		// Player
		player_->Draw();
		// Spike
		for (auto* spike : spike_) {
			spike->Draw();
		}
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
	Object obj1, obj2;
	obj1 = player_->GetObject_();
	for (int i = 0; i < kSpikeNum; i++)
	{
		obj2 = spike_[i]->GetObject_();
		if (isCollideObject(obj1, obj2)) {
			player_->OnCollision();
			break;
		}
	}

#pragma endregion

#pragma region player & item collision

#pragma endregion
}
