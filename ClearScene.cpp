#include "ClearScene.h"

ClearScene::~ClearScene()
{
	delete fade_;
}

void ClearScene::Initialize()
{
	phase_ = Phase::kFadeIn;
	fade_ = new Fade();
	fade_->Initialize();
	fade_->Start(Status::FadeIn, duration_);
	texture_ = Novice::LoadTexture("./Resources/Clear/clear.png");
}

void ClearScene::ChangePhase()
{
	switch (phase_)
	{
	case ClearScene::Phase::kFadeIn:
		if (fade_->IsFinished())
		{
			phase_ = Phase::kPlay;
		}
		break;
	case ClearScene::Phase::kPlay:
		if (Input::GetInstance()->TriggerKey(DIK_C))
		{
			fade_->Start(Status::FadeOut, duration_);
			phase_ = Phase::kFadeOut;
		}
		break;
	case ClearScene::Phase::kDeath:
		break;
	case ClearScene::Phase::kStageClear:
		break;
	case ClearScene::Phase::kFadeOut:
		if (fade_->IsFinished()) {
			sceneNo = TITLE;
		}
		break;
	default:
		break;
	}
}

void ClearScene::Update()
{
	ChangePhase();
	switch (phase_)
	{
	case ClearScene::Phase::kFadeIn:
		fade_->Update();
		break;
	case ClearScene::Phase::kPlay:
		animationTimer_++;

		if (animationPos_.x >= animationFrames - size.width && animationTimer_ >= 30)
		{
			animationPos_.x = 0;
			animationTimer_ = 0;
		}

		if (animationTimer_ >= 30)
		{
			animationPos_.x += size.width;
			animationTimer_ = 0;
		}
		break;
	case ClearScene::Phase::kDeath:
		break;
	case ClearScene::Phase::kStageClear:
		break;
	case ClearScene::Phase::kFadeOut:
		fade_->Update();
		break;
	default:
		break;
	}

}

void ClearScene::Draw()
{
	switch (phase_)
	{
	case ClearScene::Phase::kFadeIn:
		Novice::DrawSpriteRect((int)pos_.x, (int)pos_.y, (int)animationPos_.x, (int)animationPos_.y, size.width, size.height, texture_,
			(size.width / animationFrames), 1.f, 0.0f, WHITE);
		fade_->Draw();
		break;
	case ClearScene::Phase::kPlay:
		Novice::DrawSpriteRect((int)pos_.x, (int)pos_.y, (int)animationPos_.x, (int)animationPos_.y, size.width, size.height, texture_,
			(size.width / animationFrames), 1.f, 0.0f, WHITE);
		
		break;
	case ClearScene::Phase::kDeath:
		break;
	case ClearScene::Phase::kStageClear:
		break;
	case ClearScene::Phase::kFadeOut:
		Novice::DrawSpriteRect((int)pos_.x, (int)pos_.y, (int)animationPos_.x, (int)animationPos_.y, size.width, size.height, texture_,
			(size.width / animationFrames), 1.f, 0.0f, WHITE);
		fade_->Draw();

		break;
	default:
		break;
	}
	
}
