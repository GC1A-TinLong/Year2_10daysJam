#include "SpikeTrap.h"
#include "Novice.h"

void SpikeTrap::Initialize(const Vector2& pos, float scrollSpeed)
{
	pos_ = pos;
	scrollSpeed_ = scrollSpeed;
	texture_ = Novice::LoadTexture("./Resources/StageAssets/SpikeBloodTrap.png");
}

void SpikeTrap::Update()
{
	pos_.y -= scrollSpeed_;
}

void SpikeTrap::Draw()
{
	Novice::DrawSprite((int)pos_.x, (int)pos_.y, texture_, 1.f, 1.f, 0, WHITE);
}

const Object SpikeTrap::GetObject_() const
{
	Object result{};
	result.pos = { pos_.x, pos_.y + heightHitboxOffset };
	result.size = size;
	return result;
}
