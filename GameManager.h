#pragma once
#include <memory>
#include "IScene.h"
#include "TitleScene.h"
#include "StageScene.h"
#include "ClearScene.h"
#include "Novice.h"
#include "Input.h"

class GameManager
{
private:
	// for maintaining the scene
	std::unique_ptr<IScene>sceneArr_[3];

	int currentSceneNo_;
	int prevSceneNo_;

public:
	GameManager();
	~GameManager();

	int Run();
};

