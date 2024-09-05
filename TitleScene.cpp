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
	fade_->Update();

	if (Input::GetInstance()->TriggerKey(DIK_SPACE) && fade_->IsFinished()) {
		fade_->Start(Status::FadeOut, duration_);
		isSpaceClicked = true;
	}

	if (fade_->IsFinished() && isSpaceClicked) {
		finished_ = true;
		isSpaceClicked = false;
		sceneNo = STAGE;
	}
}

void TitleScene::Draw()
{
	//Novice::DrawSprite(0, 0, textureHandle_, 1.0f, 1.0f, 0, WHITE);
	fade_->Draw();
}
