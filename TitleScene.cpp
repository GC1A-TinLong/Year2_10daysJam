#include "TitleScene.h"

TitleScene::~TitleScene()
{
	delete fade_;
}

void TitleScene::Initialize()
{
	titleHandle_ = Novice::LoadTexture("./Resources/Title/Title1.png");
	phase_ = Phase::kFadeIn;
	fade_ = new Fade();
	fade_->Initialize();
	fade_->Start(Status::FadeIn, duration_);
}

void TitleScene::Update()
{

	fade_->Update();

	Animation();

	Menuing();

	if (Input::GetInstance()->TriggerKey(DIK_SPACE) && fade_->IsFinished() && !hasPressedDown) {
		fade_->Start(Status::FadeOut, duration_);
		isSpaceClicked = true;
	}

	if (Input::GetInstance()->TriggerKey(DIK_SPACE) && fade_->IsFinished() && hasPressedDown) {
		fade_->Start(Status::FadeOut, duration_);
		hasPressedExit = true;
	}

	if (fade_->IsFinished() && isSpaceClicked) {
		finished_ = true;
		isSpaceClicked = false;
		sceneNo = BASIC_TUTORIAL;
	}


}

void TitleScene::Animation()
{
	if (pressTimer <= 7)
	{
		pressTimer++;
	}

	animationTimer++;

	if (animationTimer > maxFrames)
	{
		animationTimer = 0;
	}
	if (!hasPressedDown)
	{
		if (animationTimer < 30)
		{
			animationPos_.x = 0;

		}
		else if (animationTimer < 60)
		{
			animationPos_.x = 1920;

		}
	}
	else
	{
		if (animationTimer < 30)
		{
			animationPos_.x = 3840;

		}
		else if (animationTimer < 60)
		{
			animationPos_.x = 5760;

		}
	}

}

void TitleScene::Menuing()
{
	if ((Input::GetInstance()->TriggerKey(DIK_DOWN) || Input::GetInstance()->TriggerKey(DIK_S) || Input::GetInstance()->TriggerKey(DIK_UP) || Input::GetInstance()->TriggerKey(DIK_W)) && !hasPressedDown && pressTimer >= 5)
	{
		hasPressedDown = true;
		pressTimer = 0;
		animationPos_.x = 3840;
		animationTimer = 0;
	}

	if ((Input::GetInstance()->TriggerKey(DIK_DOWN) || Input::GetInstance()->TriggerKey(DIK_S) || Input::GetInstance()->TriggerKey(DIK_UP) || Input::GetInstance()->TriggerKey(DIK_W)) && hasPressedDown && pressTimer >= 5)
	{
		hasPressedDown = false;
		pressTimer = 0;
		animationPos_.x = 0;
		animationTimer = 0;
	}


	/*if (Input::GetInstance()->TriggerKey(DIK_SPACE) && hasPressedDown)
	{
		hasPressedDown = false;
	}*/
}



void TitleScene::Draw()
{
	Novice::DrawSpriteRect((int)pos_.x, (int)pos_.y, (int)animationPos_.x, (int)animationPos_.y, 1920, 1080, titleHandle_, 1920.f / animationFrames, 1.0f, 0.0f, WHITE);
	fade_->Draw();
}
