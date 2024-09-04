#include "StageScene.h"

StageScene::~StageScene()
{
	delete player_;
	delete fade_;
}

void StageScene::Initialize()
{
	player_ = new Player;
	player_->Initialize({ 640,400 }, playerTexture);

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
		player_->Update();
		
		break;
	case StageScene::Phase::kDeath:
		break;
	case StageScene::Phase::kStageClear:
		break;
	case StageScene::Phase::kFadeOut:
		fade_->Update();
		break;
	default:
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
	default:
		break;
	}
}

void StageScene::Draw()
{
	switch (phase_)
	{
	case StageScene::Phase::kFadeIn:
		player_->Draw();
		fade_->Draw();
		break;
	case StageScene::Phase::kPlay:
		player_->Draw();
		break;
	case StageScene::Phase::kDeath:
		break;
	case StageScene::Phase::kStageClear:
		break;
	case StageScene::Phase::kFadeOut:
		fade_->Draw();

		break;
	default:
		break;
	}
	
}
