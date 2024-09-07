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
	
		randX = rand() % amplitude - amplitude / 2;
		randY = rand() % amplitude - amplitude / 2;
}
