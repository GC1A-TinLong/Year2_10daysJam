#pragma once
#include <memory>
#include "IScene.h"
#include "TitleScene.h"
#include "BasicTutorialScene.h"
#include "StageScene.h"
#include "ClearScene.h"
#include "Novice.h"
#include "Input.h"
#include "Pause.h"

class GameManager
{
private:
	// for maintaining the scene
	std::unique_ptr<IScene>sceneArr_[4];

	int currentSceneNo_;
	int prevSceneNo_;

	bool isFullScreen = false;
	Pause* pause_ = nullptr;

public:
	GameManager();
	~GameManager();
	int Run();

	int pauseTimer = 0;
	bool isPaused = false;
};

