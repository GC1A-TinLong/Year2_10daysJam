#include "Goal.h"
#include "Novice.h"

Goal::Goal()
{
}

Goal::~Goal()
{
}

void Goal::Initialize(Vector2 pos)
{
	pos_ = pos;
	texture_ = Novice::LoadTexture("./Resources/Goal/Goal.png");
	textTexture_ = Novice::LoadTexture("./Resources/Goal/GoalText.png");
}

void Goal::Update(float scrollSpeed)
{
	pos_.y -= scrollSpeed;

	if (pos_.y <= 1080)
	{

		animationTimer_++;

		if (animationPos_.x >= animationFrames - size.width && animationTimer_ >= 30)
		{
			animationPos_.x = 0;
			animationTimer_ = 0;
		}

		if (animationTimer_ >= 30)
		{
			animationPos_.x += size.width;
			animationTimer_ = 0;
		}
	}

	if (pos_.y < 780) 
	{
		stopMoving = true;
	}
}

void Goal::Draw()
{
	if (pos_.y <= 1080.f) 
	{
		Novice::DrawSprite((int)pos_.x, (int)pos_.y, texture_, scale.x, scale.y, 0.0f, WHITE);
		Novice::DrawSpriteRect((int)pos_.x, (int)pos_.y, (int)animationPos_.x, (int)animationPos_.y, size.width, size.height, textTexture_,
			(size.width / animationFrames), 1.f, 0.0f, WHITE);
	}
}

const Object Goal::GetObject_() const
{
	Object result{};
	result.pos = pos_;
	result.size = size;
	return result;
}
