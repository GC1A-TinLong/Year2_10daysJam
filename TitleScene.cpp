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
		clicks_ = 1;
	}

	if (fade_->IsFinished() && clicks_ == 1) {
		finished_ = true;
		clicks_ = 0;
		sceneNo = STAGE;
	}


}



void TitleScene::Draw()
{
	//Novice::DrawSprite(0, 0, textureHandle_, 1.0f, 1.0f, 0, WHITE);
	fade_->Draw();

}
