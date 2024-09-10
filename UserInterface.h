#pragma once
#include "Novice.h"
#include <iostream>
#include "MathFunction.h"

class UserInterface
{
public:

	~UserInterface();
	void Initialize();
	void Update(bool isShowingDrillUI, bool isTutorial);
	void Draw() const;

	//Setter
	void SetDrillPower(float drillPower) { drillPower_ = drillPower; };
	void SetIsDrilling(bool isDrilling) { isDrilling_ = isDrilling; };
	void SetPlayerHP(int playerHP) { playerHP_ = playerHP; };


private:
	//UI Handles
	unsigned int stageTextHandle = Novice::LoadTexture("./Resources/StageText/STAGE.png");
	unsigned int stage1Handle = Novice::LoadTexture("./Resources/StageText/1.png");
	unsigned int controlsHandle = Novice::LoadTexture("./Resources/StageText/CONTROLS.png");
	unsigned int letterDHandle = Novice::LoadTexture("./Resources/StageText/D.png");
	unsigned int letterAHandle = Novice::LoadTexture("./Resources/StageText/A.png");
	unsigned int rightPlayer = Novice::LoadTexture("./Resources/Player/digPlayer(R).gif");
	unsigned int leftPlayer = Novice::LoadTexture("./Resources/Player/digPlayer(L).gif");
	unsigned int spaceHandle = Novice::LoadTexture("./Resources/StageText/SPACE.png");
	unsigned int jumpPlayer = Novice::LoadTexture("./Resources/Player/player.gif");
	unsigned int jumpLines = Novice::LoadTexture("./Resources/StageText/fakejump.png");
	unsigned int letterSHandle = Novice::LoadTexture("./Resources/StageText/S.png");
	unsigned int drillingPlayer = Novice::LoadTexture("./Resources/StageText/drillingUI.png");

	//Battery
	unsigned int EnergyHandle = Novice::LoadTexture("./Resources/HP/HP.png");
	unsigned int energyLineHandle = Novice::LoadTexture("./Resources/HP/HPLines.png");
	unsigned int batteryText = Novice::LoadTexture("./Resources/StageText/BATTERY.png");

	//Drill
	unsigned int drillText = Novice::LoadTexture("./Resources/StageText/DRILL.png");
	unsigned int drilledBlock = Novice::LoadTexture("./Resources/StageAssets/BrokenBlock.png");
	unsigned int drillLines = Novice::LoadTexture("./Resources/StageText/fakeDrill.png");
	unsigned int sparkHandle = Novice::LoadTexture("./Resources/Player/UIspark.png");

	//Life
	unsigned int lifeTextHandle = Novice::LoadTexture("./Resources/StageText/HP.png");

	int lifeHandle[6] =
	{
		{Novice::LoadTexture("./Resources/Life/Life0.png")},
		{Novice::LoadTexture("./Resources/Life/Life1.png")},
		{Novice::LoadTexture("./Resources/Life/Life2.png")},
		{Novice::LoadTexture("./Resources/Life/Life3.png")},
		{Novice::LoadTexture("./Resources/Life/Life4.png")},
		{Novice::LoadTexture("./Resources/Life/Life5.png")},
	};

	float length_ = 324.f;
	float drillPower_;
	unsigned int batteryColor;
	unsigned int R = 0;
	unsigned int G = 255;
	unsigned int B = 34;
	bool isDrilling_ = false;
	float test_ = 0.f;
	float drillEnergyReductionSpeed = 1.3f * 2;
	float drillEnergyRestorationSpeed = 0.65f * 2;
	int playerHP_ = 5;

	// Drill
	uint32_t drillColor;
	uint32_t drillR = 255;
	uint32_t drillG = 255;
	uint32_t drillB = 255;
	uint32_t drillA = 0;
	bool isStartIncreaseAlpha = false;
	
	//HP
	/*Size size_ = { 348,90 };
	float animationFrames = 2088.f;
	Vector2 animationPos_ = { 0.f, 0.f };*/



};

