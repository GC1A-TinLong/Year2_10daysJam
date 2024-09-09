#pragma once
#include "Novice.h"
#include <iostream>

class UserInterface
{
public:

	void Initialize();
	void Update();
	void Draw() const;

	//Setter
	void SetDrillPower(float drillPower) { drillPower_ = drillPower; };
	void SetIsDrilling(bool isDrilling) { isDrilling_ = isDrilling; };


private:
	//UI Handles
	int stageTextHandle = Novice::LoadTexture("./Resources/StageText/STAGE.png");
	int stage1Handle = Novice::LoadTexture("./Resources/StageText/1.png");
	int controlsHandle = Novice::LoadTexture("./Resources/StageText/CONTROLS.png");
	int letterDHandle = Novice::LoadTexture("./Resources/StageText/D.png");
	int letterAHandle = Novice::LoadTexture("./Resources/StageText/A.png");
	int rightPlayer = Novice::LoadTexture("./Resources/Player/digPlayer(R).gif");
	int leftPlayer = Novice::LoadTexture("./Resources/Player/digPlayer(L).gif");
	int spaceHandle = Novice::LoadTexture("./Resources/StageText/SPACE.png");

	//HP
	int hpHandle = Novice::Novice::LoadTexture("./Resources/HP/HP.png");
	int hpLineHandle = Novice::Novice::LoadTexture("./Resources/HP/HPLines.png");

	int HPTextHandle = Novice::Novice::LoadTexture("./Resources/StageText/HP.png");

	float length_ = 324.f;
	float drillPower_;
	uint32_t color;
	uint32_t R = 0;
	uint32_t G = 255;
	uint32_t B = 34;
	bool isDrilling_ = false;
	float test_ = 0.f;
	float drillEnergyReductionSpeed = 1.3f * 2;
	float drillEnergyRestorationSpeed = 0.65f * 2;
	
	
};

