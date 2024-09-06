#pragma once
#include "MathFunction.h"

class Shake
{
public:

	void Initialize(float shakeAmplitude, float shakeEndTimer);

	void ActivateShake(Vector2& pos);

private:

	float shakeAmplitude_ = 4.f; //determined in Initialize
	float shakeEndTimer_ = 5.1f; //determined in Initialize
	unsigned int seed;
};

