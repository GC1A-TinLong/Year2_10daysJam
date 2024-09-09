#include "UserInterface.h"

void UserInterface::Initialize()
{
}

void UserInterface::Update()
{
}

void UserInterface::Draw() const
{
	//UI
	Novice::DrawBox(0, 0, 144, 1080, 0.0f, BLACK, kFillModeSolid);
	Novice::DrawBox(0, 1032, 1440, 1032, 0.0f, BLACK, kFillModeSolid);
	Novice::DrawBox(0, 0, 1440, 96, 0.0f, BLACK, kFillModeSolid);
	Novice::DrawBox(1440, 0, 1920, 1080, 0.0f, BLACK, kFillModeSolid);

	//UI TEXT
	Novice::DrawSprite(200, 20, stageTextHandle, 1.0f, 1.0f, 0.0f, WHITE); //TEXT
	Novice::DrawSprite(420, 15, stage1Handle, 1.0f, 1.0f, 0.0f, WHITE); //1
	Novice::DrawSprite(1520, 250, controlsHandle, 1.0f, 1.0f, 0.0f, WHITE); //CONROLS
	Novice::DrawSprite(1520, 350, letterDHandle, 1.0f, 1.0f, 0.0f, WHITE); //D
	Novice::DrawSprite(1520, 450, letterAHandle, 1.0f, 1.0f, 0.0f, WHITE); //A
	Novice::DrawSprite(1620, 350, rightPlayer, 1.0f, 1.0f, 0.0f, WHITE); //Player Right
	Novice::DrawSprite(1620, 450, leftPlayer, 1.0f, 1.0f, 0.0f, WHITE); //Player Left
	Novice::DrawSprite(1520, 550, spaceHandle, 1.0f, 1.0f, 0.0f, WHITE); //SPACE

	//HP
	Novice::DrawSprite(1510, 100, hpHandle[hpFrames_], 1.0f, 1.0f, 0.0f, WHITE); //HP
	Novice::DrawSprite(1580, 30, HPTextHandle, 1.0f, 1.0f, 0.0f, WHITE); //HP


}
