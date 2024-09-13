#include "UserInterface.h"
#include "algorithm"
UserInterface::~UserInterface()
{
}
void UserInterface::Initialize(int currentStage)
{
	batteryColor = 0x00FF1AFF; //Green
	batteryA = 0;
	if (currentStage == -1) {
		stageNumberHandle = Novice::LoadTexture("./Resources/StageText/SELECT.png");
	}
	else if (currentStage == 0) {
		stageNumberHandle = Novice::LoadTexture("./Resources/StageText/TUTORIAL.png");
	}
	else if (currentStage == 1)
	{
		stageNumberHandle = Novice::LoadTexture("./Resources/StageText/1.png");
	} 
	else if (currentStage == 2)
	{
		stageNumberHandle = Novice::LoadTexture("./Resources/StageText/2.png");
	}
}

void UserInterface::Update(bool isShowingDrillUI, bool isTutorial)
{
	if (isDrilling_) { length_ -= drillEnergyReductionSpeed; }
	else { length_ += drillEnergyRestorationSpeed; }

	if (drillPower_ >= 255)
	{
		G = 255;
		R = 510 - (int)drillPower_;

	}
	else
	{
		R = 255;
		G = (int)drillPower_;
	}

	R = std::clamp((int)R, 0, 255); // Clamp R to 255
	G = std::clamp((int)G, 0, 255); //Clamp G to 255
	length_ = std::clamp(length_, 0.f, 323.f);

	// Adjusting battery UI alpha
	if (!isTutorial) {
		batteryA = 255;
	}
	else if (isShowingDrillUI && isTutorial) {
		isStartIncreaseAlpha = true;
		isStartBlinking = true;
	}
	if (isStartIncreaseAlpha) {
		batteryA += 6;
		if (batteryA >= 255) {
			batteryA = 255;
			isStartIncreaseAlpha = false;
		}
	}
	// Adjusting drill UI blink alpha
	if (isStartBlinking) {
		if (drillBoxA >= 118 && drillBoxA <= 255) { alphaSpeed = -3; }
		else if (drillBoxA <= 0 || drillBoxA > 255) { alphaSpeed = 3; }
		drillBoxA += alphaSpeed;
	}
	else { drillBoxA = 0; }

	drillBoxColor = (drillBoxR << 24) | (drillBoxG << 16) | (drillBoxB << 8) | drillBoxA;
	batteryUIColor = (R << 24) | (G << 16) | (B << 8) | batteryA;
	batteryColor = (batteryR << 24) | (batteryG << 16) | (batteryB << 8) | batteryA;
}

void UserInterface::Countdown()
{

}

void UserInterface::Draw() const
{
	//UI
	/*Novice::DrawBox(0, 0, 144, 1080, 0.0f, BLACK, kFillModeSolid);
	Novice::DrawBox(0, 1056, 1440, 50, 0.0f, BLACK, kFillModeSolid);
	Novice::DrawBox(0, 0, 1440, 96, 0.0f, BLACK, kFillModeSolid);
	Novice::DrawBox(1440, 0, 1920, 1080, 0.0f, BLACK, kFillModeSolid);*/
	Novice::DrawSprite(0, 0, UIHandle, 1.0f, 1.0f, 0.0f, WHITE); //STAGE


	//UI TEXT
	Novice::DrawSprite(200, 20, stageTextHandle_, 1.0f, 1.0f, 0.0f, WHITE); //STAGE
	Novice::DrawSprite(420, 20, stageNumberHandle, 1.0f, 1.0f, 0.0f, WHITE); //1
	Novice::DrawSprite(1520, 370, controlsHandle, 1.0f, 1.0f, 0.0f, WHITE); //CONROLS
	Novice::DrawSprite(1520, 470, letterDHandle, 1.0f, 1.0f, 0.0f, WHITE); //D
	Novice::DrawSprite(1520, 570, letterAHandle, 1.0f, 1.0f, 0.0f, WHITE); //A
	Novice::DrawSprite(1620, 470, rightPlayer, 1.0f, 1.0f, 0.0f, WHITE); //Player Right
	Novice::DrawSprite(1620, 570, leftPlayer, 1.0f, 1.0f, 0.0f, WHITE); //Player Left
	Novice::DrawSprite(1520, 670, spaceHandle, 1.0f, 1.0f, 0.0f, WHITE); //SPACE
	Novice::DrawSprite(1750, 650, jumpPlayer, 1.0f, 1.0f, 0.0f, WHITE); //Player Jump
	Novice::DrawSprite(1736, 725, jumpLines, 1.0f, 1.0f, 0.0f, WHITE); //Player Jump Lines

	//Energy
	Novice::DrawSprite(1509, 100, EnergyHandle, 1.0f, 1.0f, 0.0f, batteryColor); //HP Battery
	Novice::DrawBox(1516, 104, (int)length_, 82, 0.0f, batteryUIColor, kFillModeSolid); // COLOR
	Novice::DrawSprite(1510, 100, energyLineHandle, 1.0f, 1.0f, 0.0f, batteryColor); //HP line
	Novice::DrawSprite(1560, 30, batteryText, 1.0f, 1.0f, 0.0f, batteryColor); //BATTERY text
	//Drill
	Novice::DrawBox(1500, 780, 340, 235, 0, drillBoxColor, kFillModeSolid);	// Drill Box Blink
	//Novice::DrawSprite(1500, 780, blackEdge, 1.f, 1.f, 0, WHITE);	// Black Edge for drill box blink
	Novice::DrawSprite(1540, 800, drillText, 1.0f, 1.0f, 0.0f, batteryColor); //DRILL
	Novice::DrawSprite(1520, 900, letterSHandle, 1.0f, 1.0f, 0.0f, batteryColor); //S
	Novice::DrawSprite(1725, 885, drillingPlayer, 1.0f, 1.0f, 0.0f, batteryColor); //Drilling Player

	//Life
	Novice::DrawSprite(1570, 205, lifeTextHandle, 1.0f, 1.0f, 0.0f, WHITE); //LIFE
	Novice::DrawSprite(1500, 270, lifeHandle[playerHP_], 1.0f, 1.0f, 0.0f, WHITE); //LIFE
	//Novice::DrawSpriteRect(1500, 300, (int)animationPos_.x, (int)animationPos_.y, size_.width, size_.height, lifeHandle, size_.width / animationFrames, 1.f, 0.0f, WHITE);

	//Novice::ScreenPrintf(0, 0, "%f", length_);
	//Novice::ScreenPrintf(0, 20, "%d", playerHP_);



}
