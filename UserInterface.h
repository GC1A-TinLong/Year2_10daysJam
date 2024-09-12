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

	//Battery
	unsigned int EnergyHandle = Novice::LoadTexture("./Resources/HP/energy1.png");
	unsigned int energyLineHandle = Novice::LoadTexture("./Resources/HP/HPLines.png");
	unsigned int batteryText = Novice::LoadTexture("./Resources/StageText/BATTERY.png");

	//Drill
	unsigned int drillText = Novice::LoadTexture("./Resources/StageText/DRILL.png");
	unsigned int drillingPlayer = Novice::LoadTexture("./Resources/StageText/drillingUI.png");
	unsigned int blackEdge = Novice::LoadTexture("./Resources/StageText/blackEdge.png");

	//Life
	unsigned int lifeTextHandle = Novice::LoadTexture("./Resources/StageText/HP.png");

	int lifeHandle[5] =
	{
		{Novice::LoadTexture("./Resources/Life/LifeNew1.png")},
		{Novice::LoadTexture("./Resources/Life/LifeNew2.png")},
		{Novice::LoadTexture("./Resources/Life/LifeNew3.png")},
		{Novice::LoadTexture("./Resources/Life/LifeNew4.png")},
		{Novice::LoadTexture("./Resources/Life/LifeNew5.png")},
	};

	float length_ = 324.f;
	float drillPower_;
	unsigned int batteryColor;
	unsigned int R = 0;
	unsigned int G = 255;
	unsigned int B = 34;
	bool isDrilling_ = false;
	float test_ = 0.f;
	float drillEnergyReductionSpeed = 1.3f * 4;
	float drillEnergyRestorationSpeed = 0.65f * 4;
	int playerHP_ = 4;

	// Drill
	uint32_t drillBoxColor;
	uint32_t drillBoxR = 235;
	uint32_t drillBoxG = 255;
	uint32_t drillBoxB = 41;
	uint32_t drillBoxA = 0;
	int alphaSpeed = 3;
	bool isStartBlinking = false;

	// Battery
	uint32_t batteryUIColor;
	uint32_t batteryR = 255;
	uint32_t batteryG = 255;
	uint32_t batteryB = 255;
	uint32_t batteryA = 0;
	bool isStartIncreaseAlpha = false;
	
	//HP
	/*Size size_ = { 348,90 };
	float animationFrames = 2088.f;
	Vector2 animationPos_ = { 0.f, 0.f };*/



};

