#include "DepthMeter.h"

DepthMeter::DepthMeter()
{
}

DepthMeter::~DepthMeter()
{
}

void DepthMeter::Initialize(int goalPos)
{
	goalPos_ = goalPos;
	pos_ = { 20,140 };
	playerPos_ = { 25,140 };
	startY = pos_.y;
}

void DepthMeter::Update()
{
	DepthCounter();
	MoveDownwards();
}

void DepthMeter::DepthCounter()
{
	playerStartPos_--;
	depthCounter_ = (playerYDepth_ - playerStartPos_) /10.f;
	depthCounter_ = std::clamp(depthCounter_, 0.f, 999.f);

	units = (int)depthCounter_ % 10;
	tens = ((int)depthCounter_ / 10) % 10;
	hundreds = ((int)depthCounter_ / 100) % 10;

	if (tens > 0) 
	{
		showTens = true;
	}

	if (hundreds > 0) 
	{
		showHundreds = true;
	}

}

void DepthMeter::MoveDownwards()
{
	t = std::clamp((playerYDepth_ - playerStartPos_) / (goalPos_ - playerStartPos_), 0.0f, 1.0f);

	// Linearly interpolate posY based on t
	posY = startY + t * (endY - startY);
}

void DepthMeter::Draw()
{
	Novice::DrawSprite((int)pos_.x, (int)pos_.y, meterSprite_, 1.0f, 1.0f, 0.0f, WHITE); //STAGE
	Novice::DrawSprite((int)playerPos_.x, (int)playerPos_.y, meterPlayer_, 1.0f, 1.0f, 0.0f, WHITE); //STAGE
	Novice::DrawSprite(100, (int)posY, numbers[units], 1.0f, 1.0f, 0.0f, WHITE); //STAGE
	if (showTens) 
	{
		Novice::DrawSprite(80, (int)posY, numbers[tens], 1.0f, 1.0f, 0.0f, WHITE); //STAGE
	}
	if (hundreds)
	{
		Novice::DrawSprite(60, (int)posY, numbers[hundreds], 1.0f, 1.0f, 0.0f, WHITE); //STAGE
	}
	Novice::DrawSprite(120, (int)posY, mHandle_, 1.0f, 1.0f, 0.0f, WHITE); //STAGE
	Novice::DrawSprite(15, 110, starthandle_, 1.0f, 1.0f, 0.0f, WHITE); //STAGE
	Novice::DrawSprite(15, 950, goalhandle_, 1.0f, 1.0f, 0.0f, WHITE); //STAGE
	Novice::ScreenPrintf(0, 0, "%f", depthCounter_);
	Novice::ScreenPrintf(0, 20, "%d", units);
	Novice::ScreenPrintf(0, 40, "%f", t);

}
