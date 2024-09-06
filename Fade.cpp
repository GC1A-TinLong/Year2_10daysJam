#include "Fade.h"
#include "Novice.h"

void Fade::Initialize()
{
	textureHandle_ = Novice::LoadTexture("./Resources/Fade/blackfade.png");
	seethrough_ = 0xFFFFFF00;
}

void Fade::Update()
{
	counter_ += 1.0f / 60.0f;

	if (counter_ >= duration_) {
		counter_ = duration_;
	}

	float progress = counter_ / duration_;
	int alpha = 0;

	switch (status_)
	{
	case Status::None:
		break;
	case Status::FadeIn:

		alpha = static_cast<int>((1.0f - progress) * 255);
		seethrough_ = +alpha;

		break;
	case Status::FadeOut:

		alpha = static_cast<int>(progress * 255);
		seethrough_ = +alpha;

		break;
	default:
		break;
	}
	//seethrough_ = (seethrough_ & 0x00FFFFFF) | (alpha << 24);
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

bool Fade::IsFinished() const
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
	Novice::DrawSprite(pos_.x, pos_.y, textureHandle_, (float)size_.x, (float)size_.y, 0.0f, seethrough_);
}
