#pragma once
#include "IScene.h"
#include "Input.h"
#include "Novice.h"

class TitleScene :public IScene
{
public:
	void Initialize() override;
	void Update() override;
	void Draw() override;

private:
	uint32_t textureHandle_ = Novice::LoadTexture("./Resources/title.png");
};
