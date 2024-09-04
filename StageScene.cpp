#include "StageScene.h"

StageScene::~StageScene()
{
	delete player_;
}

void StageScene::Initialize()
{
	player_ = new Player;
	player_->Initialize({ 640,400 }, playerTexture);
}

void StageScene::Update()
{
	player_->Update();

	if (Input::GetInstance()->TriggerKey(DIK_SPACE)) {
		sceneNo = CLEAR;
	}
}

void StageScene::Draw()
{
	player_->Draw();
}
