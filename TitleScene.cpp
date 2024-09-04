#include "TitleScene.h"

void TitleScene::Initialize()
{
}

void TitleScene::Update()
{
	if (Input::GetInstance()->TriggerKey(DIK_SPACE)) {
		sceneNo = STAGE;
	}
}

void TitleScene::Draw()
{
	Novice::DrawSprite(0, 0, textureHandle_, 1.0f, 1.0f, 0, WHITE);
}
