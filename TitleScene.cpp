#include "TitleScene.h"

TitleScene::~TitleScene()
{
	delete fade_;
}

void TitleScene::Initialize()
{
	phase_ = Phase::kFadeIn;
	fade_ = new Fade();
	fade_->Initialize();
	fade_->Start(Status::FadeIn, duration_);
}

void TitleScene::Update()
{
	switch (phase_)
	{
	case Phase::kFadeIn:
		fade_->Update();
		break;
	case Phase::kPlay:
		break;
	case Phase::kDeath:
		break;
	case Phase::kStageClear:
		break;
	case Phase::kFadeOut:
		break;
	default:
		break;
	}
	if (Input::GetInstance()->TriggerKey(DIK_SPACE)) {
		sceneNo = STAGE;
	}

}

void TitleScene::Draw()
{
	//Novice::DrawSprite(0, 0, textureHandle_, 1.0f, 1.0f, 0, WHITE);
	switch (phase_)
	{
	case Phase::kFadeIn:
		fade_->Draw();
		break;
	case Phase::kPlay:
		break;
	case Phase::kDeath:
		break;
	case Phase::kStageClear:
		break;
	case Phase::kFadeOut:
		break;
	default:
		break;
	}
}
