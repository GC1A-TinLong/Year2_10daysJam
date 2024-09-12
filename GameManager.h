#pragma once
#include <memory>
#include "Novice.h"
#include "Input.h"
#include "Pause.h"

#include "IScene.h"
#include "TitleScene.h"
#include "BasicTutorialScene.h"
#include "StageSelect.h"
#include "StageScene.h"
#include "StageScene2.h"
#include "ClearScene.h"



class GameManager
{
private:
	// for maintaining the scene
	std::unique_ptr<IScene>sceneArr_[6];

	int currentSceneNo_;
	int prevSceneNo_;

	bool isFullScreen = false;
	Pause* pause_ = nullptr;
	TitleScene* titleScene_ = nullptr;

public:
	GameManager();
	~GameManager();
	int Run();

	int pauseTimer = 0;
	bool isPaused = false;
};

