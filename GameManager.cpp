#include "GameManager.h"

GameManager::GameManager()
{
	// calling contructor
	sceneArr_[TITLE] = std::make_unique<TitleScene>();
	sceneArr_[BASIC_TUTORIAL] = std::make_unique<BasicTutorialScene>();
	sceneArr_[STAGESELECT] = std::make_unique<StageSelect>();
	sceneArr_[STAGE] = std::make_unique<StageScene>();
	sceneArr_[STAGE2] = std::make_unique<StageScene2>();
	sceneArr_[STAGE3] = std::make_unique<StageScene3>();
	sceneArr_[STAGE4] = std::make_unique<StageScene4>();
	sceneArr_[LAST_STAGE] = std::make_unique<LastStage>();
	sceneArr_[CLEAR] = std::make_unique<ClearScene>();

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
		Novice::SetWindowMode(kFullscreen);

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
		Audio();
		// PAUSE
		if (pause_->GetIsPaused())
		{
			pause_->Update();
			pause_->Draw();
			Novice::SetAudioVolume(BGMPlayHandle, 0.01f);
		}
		else 
		{
			Novice::SetAudioVolume(BGMPlayHandle, 0.015f);

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

		Novice::EndFrame();

		if (pause_->GetCloseGame() || titleScene_->GetPressedExit()) {
			break;
		}
	}
	return 0;
}

void GameManager::Audio()
{
	if (Novice::IsPlayingAudio(BGMPlayHandle) == 0 || BGMPlayHandle == -1) {
		BGMPlayHandle = Novice::PlayAudio(BGMAudioHandle, 1, kBGMAudioVolume);
	}
}
