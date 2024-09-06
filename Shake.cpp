#include "Shake.h"
#include <ctime>

void Shake::Initialize(float shakeAmplitude, float shakeEndTimer)
{
	shakeAmplitude_ = shakeAmplitude;
	shakeEndTimer_ = shakeEndTimer;
}


void Shake::ActivateShake(Vector2& pos)
{
	srand(seed);
	float shrinkrate = shakeAmplitude_ * 0.145f;
	Vector2 randDistance{};

	if (shakeAmplitude_ >= 1)
	{
		randDistance.x = rand() % (int)shakeAmplitude_ - shakeAmplitude_ / 2.0f;

		randDistance.y = rand() % (int)shakeAmplitude_ - shakeAmplitude_ / 2.0f;
	}

	if (shakeEndTimer_ >= 0 && shakeEndTimer_ < shakeEndTimer_ * 0.2f)
	{
		shakeAmplitude_ -= shrinkrate;
	}
	else if (shakeEndTimer_ >= shakeEndTimer_ * 0.2f && shakeEndTimer_ < shakeEndTimer_ * 0.6f)
	{
		shakeAmplitude_ -= shrinkrate * 0.75f;
	}
	else if (shakeEndTimer_ >= shakeEndTimer_ * 0.6f)
	{
		shakeAmplitude_ -= shrinkrate * 0.25f;
	}

	pos.x += randDistance.x;
	pos.y += randDistance.y;
}
