#include "Shake.h"
#include <ctime>
#include "Novice.h"
#include "Input.h"

void Shake::Initialize()
{
	
	seed = (unsigned int)time(nullptr);
	srand(seed);
	
}


void Shake::ActivateShake(int amplitude, int maxTimer)
{
	/*srand(seed);
	Vector2 randDistance{};
	float shrinkrate = shakeAmplitude_ * 0.245f;

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

	if (shrinkrate <= 0.1f)
	{
		isShakeFinished_ = true;
	}

	pos.x += randDistance.x;
	pos.y += randDistance.y;*/
	if (Input::GetInstance()->TriggerKey(DIK_X))
	{
		shake = true;
	}
	if (shake) {
		timer++;
	}
	if (timer >= 1 && timer < 20) {
		randX = rand() % amplitude - amplitude / 2;
		randY = rand() % amplitude - amplitude / 2;
	}
	else if (timer >= 20 && timer < 40) {
		randX = rand() % amplitude / 2 - amplitude / 3;
		randY = rand() % amplitude / 2 - amplitude / 3;
	}
	else if (timer >= 40 && timer < 60) {
		randX = rand() % amplitude / 3 - amplitude / 4;
		randY = rand() % amplitude / 3 - amplitude / 4;
	}
	else {
		randX = 0;
		randY = 0;
	}

	if (timer >= maxTimer) {
		shake = false;
		timer = 0;
	}

}

void Shake::InfiniteShake(int amplitude)
{
	if (infiniteShake) 
	{
		randX = rand() % amplitude - amplitude / 2;
		randY = rand() % amplitude - amplitude / 2;
	}
}
