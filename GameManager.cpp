#include "GameManager.h"

GameManager::GameManager()
{
	// calling contructor
	sceneArr_[TITLE] = std::make_unique<TitleScene>();
	sceneArr_[BASIC_TUTORIAL] = std::make_unique<BasicTutorialScene>();
	sceneArr_[STAGE] = std::make_unique<StageScene>();
	sceneArr_[CLEAR] = std::make_unique<ClearScene>();
	sceneArr_[STAGE2] = std::make_unique<StageScene2>();

	currentSceneNo_ = TITLE;
	prevSceneNo_ = TITLE;
	sceneArr_[currentSceneNo_]->Initialize();
	pause_ = new Pause();
	pause_->Initialize();
	titleScene_ = new TitleScene;
	titleScene_->Initialize();

}

GameManager::~GameManager()
{
	delete pause_;
	delete titleScene_;
}

int GameManager::Run()
{
	while (Novice::ProcessMessage() == 0) {
		Novice::BeginFrame();

		// scene check
		prevSceneNo_ = currentSceneNo_;
		currentSceneNo_ = sceneArr_[currentSceneNo_]->GetSceneNo();
		// check if the scene has changed
		if (prevSceneNo_ != currentSceneNo_) {
			sceneArr_[currentSceneNo_]->Initialize();
		}
		if (!pause_->GetIsPaused())
		{
			sceneArr_[currentSceneNo_]->Update();
		}
		sceneArr_[currentSceneNo_]->Draw();

		// PAUSE
		if (pause_->GetIsPaused())
		{
			pause_->Update();
			pause_->Draw();
		}

		if (currentSceneNo_ == TITLE) 
		{
			titleScene_->Update();
		}

		if (Input::GetInstance()->TriggerKey(DIK_ESCAPE) && !isPaused && currentSceneNo_ != TITLE)
		{
			pause_->SetIsPaused(true);
			isPaused = true;
			pauseTimer = 1;
		}

		if (!pause_->GetIsPaused() && pauseTimer > 0) { pauseTimer++; }
		if (pauseTimer > 5) { isPaused = false; }

		if (Input::GetInstance()->TriggerKey(DIK_F)) {
			isFullScreen ^= true;
		}
		if (isFullScreen) { Novice::SetWindowMode(kFullscreen); }
		else { Novice::SetWindowMode(kWindowed); }

		Novice::EndFrame();

		if (pause_->GetCloseGame() || titleScene_->GetPressedExit()) {
			break;
		}
	}
	return 0;
}
