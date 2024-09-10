#include "Goal.h"
#include "Novice.h"

Goal::Goal()
{
}

Goal::~Goal()
{
}

void Goal::Initialize(Vector2 pos, float scrollSpeed)
{
	pos_ = pos;
	scrollSpeed_ = scrollSpeed;
	texture_ = Novice::LoadTexture("./Resources/Goal/Goal.png");
}

void Goal::Update()
{
	pos_.y -= scrollSpeed_;
}

void Goal::Draw()
{
	if (pos_.y <= 1080.f) 
	{
		Novice::DrawSprite((int)pos_.x, (int)pos_.y, texture_, scale.x, scale.y, 0.0f, WHITE);
	}
}

const Object Goal::GetObject_() const
{
	Object result{};
	result.pos = pos_;
	result.size = size;
	return result;
}
