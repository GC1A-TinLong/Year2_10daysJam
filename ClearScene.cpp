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
		fade_->Draw();
		break;
	case ClearScene::Phase::kPlay:
		break;
	case ClearScene::Phase::kDeath:
		break;
	case ClearScene::Phase::kStageClear:
		break;
	case ClearScene::Phase::kFadeOut:
		fade_->Draw();

		break;
	default:
		break;
	}
}
