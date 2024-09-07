#include "Backgroud.h"
#include "Novice.h"
#include <ctime>

void Background::Initialize(int backgroundHandle[MAXBACKGROUNDS])
{
	for (int i = 0; i < MAXBACKGROUNDS; i++)
	{
		backgroundHandle_[i] = backgroundHandle[i];
	}

	//backgroundHandle_[0] = Novice::LoadTexture("./Resources/Background/Bg1.png");
	//backgroundHandle_[1] = Novice::LoadTexture("./Resources/Background/Bg2.png");
	seed = (unsigned int)time(nullptr);
	srand(seed);
}

void Background::Update()
{
	RandomizeX();
	ResetY();
}

void Background::ResetY()
{
	for (int i = 0; i < 2; i++)
	{
		pos_[i].y -= 4;
		if (pos_[i].y <= -1080)
		{
			pos_[i].y = 1080;
		}
	}
}

void Background::RandomizeX()
{
	for (int i = 0; i < 2; i++)
	{
		if (pos_[i].y <= -1070) 
		{
			randX[i] = rand() % amplitude - amplitude / 2;
		}
	}
	
}

void Background::Draw()
{
	for (int i = 0; i < 2; i++)
	{
		Novice::DrawSprite((int)pos_[i].x + randX[i], (int)pos_[i].y, backgroundHandle_[i], 1, 1, 0.0f, WHITE);
	}
}
