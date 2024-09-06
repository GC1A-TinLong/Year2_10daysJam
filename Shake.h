#pragma once
#include "MathFunction.h"

class Shake
{
public:

	void Initialize();

	void ActivateShake(int amplitude, int maxTimer);

	void InfiniteShake(int amplitude);

	bool GetIsFinished() const { return isShakeFinished_; };

	void SetIsFinished(bool isShakeFinished) { isShakeFinished_ = isShakeFinished; };

	int GetRandX() const { return randX; };
	int GetRandY() const { return randY; };

private:

	float shakeAmplitude_ = 4.f; //determined in Initialize
	float shakeEndTimer_ = 5.1f; //determined in Initialize
	unsigned int seed;
	bool isShakeFinished_ = false;
	unsigned int randX = 0;
	unsigned int randY = 0;
	int amplitude_;
	int timer = 0;
	bool shake = false;

	//Infinite shake bool
	bool infiniteShake = false;

};

