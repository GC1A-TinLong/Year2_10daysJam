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
	fireworksTexture_ = Novice::LoadTexture("./Resources/Goal/fireworks.png");
}

void Goal::CollisionPlayer(Player* player)
{
	(void)player;
	startFireworks = true;
}

void Goal::FireWorks()
{
		fireworksAnimationTimer_++;

		if (fireworksAnimationPos_.x >= fireworksAnimationFrames - size.width && fireworksAnimationTimer_ >= 5)
		{
			isWaitTimer = true;
		}
		if (isWaitTimer) 
		{
			waitTimer++;
		}
		

		if (waitTimer >= 20)
		{
			fireworksAnimationPos_.x = 0;
			fireworksAnimationTimer_ = 0;
			isWaitTimer = false;
			waitTimer = 0;
		}

		if (fireworksAnimationTimer_ >= 5)
		{
			fireworksAnimationPos_.x += size.width;
			fireworksAnimationTimer_ = 0;
		}
}

void Goal::Update(float scrollSpeed)
{
	FireWorks();
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
	Novice::DrawSpriteRect((int)pos_.x, (int)pos_.y - 300 , (int)fireworksAnimationPos_.x, (int)fireworksAnimationPos_.y, size.width, size.height, fireworksTexture_,
		(size.width / fireworksAnimationFrames), 1.f, 0.0f, WHITE);
}

const Object Goal::GetObject_() const
{
	Object result{};
	result.pos = pos_;
	result.size = size;
	return result;
}
