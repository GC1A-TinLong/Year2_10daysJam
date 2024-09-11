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
	//randX = rand() % amplitude - amplitude / 2;
}

void Background::Update(float scrollSpeed)
{
	//RandomizeX();
	ResetY(scrollSpeed);
}

void Background::ResetY(float scrollSpeed)
{
	for (int i = 0; i < MAXBACKGROUNDS; i++)
	{
		pos_[i].y -= scrollSpeed;
		if (pos_[i].y <= -1080)
		{
			pos_[i].y = 1080;
		}
	}
}

//void Background::RandomizeX()
//{
//	if (pos_[0].y == 1070)
//	{
//		randX = rand() % amplitude - amplitude / 2;
//	}
//	/*for (int i = 0; i < 2; i++)
//	{
//		if (pos_[0].y <= -1070) 
//		{
//			randX = rand() % amplitude - amplitude / 2;
//		}
//	}*/
//	
//}

void Background::Draw() const
{
	for (int i = 0; i < MAXBACKGROUNDS; i++)
	{
		Novice::DrawSprite((int)pos_[i].x, (int)pos_[i].y, backgroundHandle_[i], 1, 1, 0.0f, WHITE);
	}
}
