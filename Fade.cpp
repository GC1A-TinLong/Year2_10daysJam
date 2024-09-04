#include "Fade.h"
#include "Novice.h"

void Fade::Initialize()
{
	textureHandle_ = Novice::LoadTexture("./Resources/Sprites/blackfade.png");
	color_ = WHITE;
}

void Fade::Update()
{
	switch (status_)
	{
	case Status::None:
		break;
	case Status::FadeIn:

		counter_ += 1.0f / 60.0f;
		if (counter_ >= duration_)
		{
			counter_ = duration_;

		}

		break;
	case Status::FadeOut:
		counter_ += 1.0f / 60.0f;
		if (counter_ >= duration_)
		{
			counter_ = duration_;
		}
		break;
	default:
		break;
	}
}

void Fade::Start(Status status, float duration)
{
	status_ = status;
	duration_ = duration;
	counter_ = 0.0f;
}

void Fade::Stop()
{
	status_ = Status::None;
	counter_ = 0.0f;
}

bool Fade::IsFinished()
{
	switch (status_)
	{
	case Status::None:
		break;
	case Status::FadeIn:

	case Status::FadeOut:
		if (counter_ >= duration_)
		{
			return true;
		}
		else
		{
			return false;
		}
	}
	return false;
}

void Fade::ResetCounter()
{
	if (counter_ >= 0.0f)
	{
		counter_ = 0.0f;
	}
}

void Fade::Draw()
{
	if (status_ == Status::None)
	{
		return;
	}
	Novice::DrawSprite(pos_.x, pos_.y, textureHandle_, (float)size_.x, (float)size_.y, 0.0f, color_);
}
