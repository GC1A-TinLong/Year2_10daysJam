#include "GameManager.h"

GameManager::GameManager()
{
	// calling contructor
	sceneArr_[TITLE] = std::make_unique<TitleScene>();
	sceneArr_[STAGE] = std::make_unique<StageScene>();
	sceneArr_[CLEAR] = std::make_unique<ClearScene>();

	currentSceneNo_ = TITLE;
	prevSceneNo_ = TITLE;
}

GameManager::~GameManager()
{
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

		sceneArr_[currentSceneNo_]->Update();

		sceneArr_[currentSceneNo_]->Draw();

		Novice::EndFrame();

		if (Input::GetInstance()->TriggerKey(DIK_ESCAPE)) {
			break;
		}
	}
	return 0;
}
