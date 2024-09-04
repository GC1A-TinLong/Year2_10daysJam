#include "StageScene.h"

void StageScene::Initialize()
{
}

void StageScene::Update()
{
	if (Input::GetInstance()->TriggerKey(DIK_SPACE)) {
		sceneNo = CLEAR;
	}
}

void StageScene::Draw()
{
	Novice::DrawSprite(0, 0, textureHandle_, 1.0f, 1.0f, 0, WHITE);
}
