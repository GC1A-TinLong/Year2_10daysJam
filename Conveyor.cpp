#include "Conveyor.h"
#include "Player.h"
#include "Novice.h"
void Conveyor::Initialize(Vector2 pos/*, Size size*/, bool isRight, float scrollSpeed)
{
	pos_ = pos;
	//size_ = size;
	isRight_ = isRight;
	scrollSpeed_ = scrollSpeed;
	if (isRight_) 
	{
		texture_ = Novice::LoadTexture("./Resources/Conveyor/Conveyor32.png"); //Right
	}
	else 
	{
		texture_ = Novice::LoadTexture("./Resources/Conveyor/Conveyorleft24.png"); //Left
	}
}

void Conveyor::Update()
{
	pos_.y -= scrollSpeed_;
	Animation();
	DestroyIfOOB();
}

void Conveyor::DestroyIfOOB()
{
	if (pos_.y <= -48.f)
	{
		isAboveScreen_ = true;
	}
}

void Conveyor::Animation()
{
	animationTimer_++;

	if (animationPos_.x >= animationFrames - size_.width && animationTimer_ >= 30)
	{
		animationPos_.x = 0;
		animationTimer_ = 0;
	}

	if (animationTimer_ >= 30)
	{
		animationPos_.x += size_.width;
		animationTimer_ = 0;
	}
}

void Conveyor::Draw()
{
	if (pos_.y >= -48.f && pos_.y <= 1080.f)
	{
		Novice::DrawSpriteRect((int)(pos_.x), (int)pos_.y,(int)animationPos_.x, (int)animationPos_.y, size_.width, size_.height, texture_, size_.width / animationFrames, 1.f, 0.0f, WHITE);
	}
}

//void Conveyor::OnCollisionPlayer(Player* player)
//{
//	(void)player;
//}

Object Conveyor::GetObject_()
{
	Object result{};
	result.pos = pos_;
	result.size = size_;
	return result;
}
