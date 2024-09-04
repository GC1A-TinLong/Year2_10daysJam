#pragma once
#include "IScene.h"
#include "Input.h"
#include "Novice.h"
#include "Fade.h"

class TitleScene :public IScene
{
public:
	~TitleScene();

	void Initialize() override;
	void Update() override;
	void Draw() override;

private:
	//uint32_t textureHandle_ = Novice::LoadTexture("./Resources/title.png");
	Fade* fade_ = nullptr;
	float duration_ = 1.0f;
	Phase phase_;
	int clicks_ = 0;
	bool finished_ = false;
};
