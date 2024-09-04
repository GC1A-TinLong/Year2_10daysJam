#include "ClearScene.h"

void ClearScene::Initialize()
{
}

void ClearScene::Update()
{
	if (Input::GetInstance()->TriggerKey(DIK_SPACE)) {
		sceneNo = TITLE;
	}
}

void ClearScene::Draw()
{
	Novice::DrawSprite(0, 0, textureHandle_, 1.0f, 1.0f, 0, WHITE);
}
