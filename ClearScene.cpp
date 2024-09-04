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
}
