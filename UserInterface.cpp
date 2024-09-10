#include "UserInterface.h"
#include "algorithm"
void UserInterface::Initialize()
{
	color = 0x00FF1AFF; //Green
}

void UserInterface::Update()
{
	
	
	if (isDrilling_) 
	{
		length_ -= drillEnergyReductionSpeed;
	}
	else 
	{
		length_ += drillEnergyRestorationSpeed;
	}

	

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
	color = (R << 24) | (G << 16) | (B << 8) | 255;

}

void UserInterface::Draw() const
{
	//UI
	Novice::DrawBox(0, 0, 144, 1080, 0.0f, BLACK, kFillModeSolid);
	Novice::DrawBox(0, 1032, 1440, 1032, 0.0f, BLACK, kFillModeSolid);
	Novice::DrawBox(0, 0, 1440, 96, 0.0f, BLACK, kFillModeSolid);
	Novice::DrawBox(1440, 0, 1920, 1080, 0.0f, BLACK, kFillModeSolid);

	//UI TEXT
	Novice::DrawSprite(200, 20, stageTextHandle, 1.0f, 1.0f, 0.0f, WHITE); //STAGE
	Novice::DrawSprite(420, 15, stage1Handle, 1.0f, 1.0f, 0.0f, WHITE); //1
	Novice::DrawSprite(1520, 370, controlsHandle, 1.0f, 1.0f, 0.0f, WHITE); //CONROLS
	Novice::DrawSprite(1520, 470, letterDHandle, 1.0f, 1.0f, 0.0f, WHITE); //D
	Novice::DrawSprite(1520, 570, letterAHandle, 1.0f, 1.0f, 0.0f, WHITE); //A
	Novice::DrawSprite(1620, 470, rightPlayer, 1.0f, 1.0f, 0.0f, WHITE); //Player Right
	Novice::DrawSprite(1620, 570, leftPlayer, 1.0f, 1.0f, 0.0f, WHITE); //Player Left
	Novice::DrawSprite(1520, 670, spaceHandle, 1.0f, 1.0f, 0.0f, WHITE); //SPACE
	Novice::DrawSprite(1750, 670, jumpPlayer, 1.0f, 1.0f, 0.0f, WHITE); //Player Jump
	Novice::DrawSprite(1736, 745, jumpLines, 1.0f, 1.0f, 0.0f, WHITE); //Player Jump Lines
	Novice::DrawSprite(1520, 900, letterSHandle, 1.0f, 1.0f, 0.0f, WHITE); //S

	//Energy
	Novice::DrawSprite(1509, 100, EnergyHandle, 1.0f, 1.0f, 0.0f, WHITE); //HP Battery
	Novice::DrawBox(1516, 104, (int)length_, 82, 0.0f, color, kFillModeSolid); // COLOR
	Novice::DrawSprite(1510, 100, energyLineHandle, 1.0f, 1.0f, 0.0f, WHITE); //HP line
	Novice::DrawSprite(1560, 30, batteryText, 1.0f, 1.0f, 0.0f, WHITE); //BATTERY

	//Drill
	Novice::DrawSprite(1540, 800, drillText, 1.0f, 1.0f, 0.0f, WHITE); //DRILL
	Novice::DrawSprite(1750, 900, jumpPlayer, 1.0f, 1.0f, 0.0f, WHITE); //Player Jump
	Novice::DrawSprite(1745, 960, drilledBlock, 1.0f, 1.0f, 0.0f, WHITE); //Destroyed Block
	Novice::DrawSprite(1725, 955, drillLines, 1.0f, 1.0f, 0.0f, WHITE); //Drill Lines

	//Life
	Novice::DrawSprite(1570, 205, lifeTextHandle, 1.0f, 1.0f, 0.0f, WHITE); //LIFE
	Novice::DrawSprite(1500, 270, lifeHandle[playerHP_], 1.0f, 1.0f, 0.0f, WHITE); //LIFE
	//Novice::DrawSpriteRect(1500, 300, (int)animationPos_.x, (int)animationPos_.y, size_.width, size_.height, lifeHandle, size_.width / animationFrames, 1.f, 0.0f, WHITE);



	Novice::ScreenPrintf(0, 0, "%f", length_);
	Novice::ScreenPrintf(0, 20, "%d", playerHP_);


}
