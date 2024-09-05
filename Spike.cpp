#include "Spike.h"
#include "Novice.h"
#include "Input.h"

void Spike::Initialize(const Vector2& pos)
{
	pos_ = pos;
	plainTexture_ = Novice::LoadTexture("./Resources/StageAssets/Spike.png");
	bloodTexture_ = Novice::LoadTexture("./Resources/StageAssets/SpikeBlood.png");
}

void Spike::Update()
{
	if (Input::GetInstance()->TriggerKey(DIK_R)) {
		isStart ^= true;
	}
	if (isStart) {
		pos_.y += kSpeed;
	}
}

void Spike::Draw()
{
	Novice::DrawSprite((int)pos_.x, (int)pos_.y, bloodTexture_, 1.f, 1.f, 0, WHITE);
}

const Object Spike::GetObject_() const
{
	Object result{};
	result.pos = pos_;
	result.size = size;
	return result;
}
