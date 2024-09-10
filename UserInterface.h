#pragma once
#include "Novice.h"
#include <iostream>
#include "MathFunction.h"

class UserInterface
{
public:

	void Initialize();
	void Update();
	void Draw() const;

	//Setter
	void SetDrillPower(float drillPower) { drillPower_ = drillPower; };
	void SetIsDrilling(bool isDrilling) { isDrilling_ = isDrilling; };
	void SetPlayerHP(int playerHP) { playerHP_ = playerHP; };


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
	int jumpPlayer = Novice::LoadTexture("./Resources/Player/player.gif");
	int jumpLines = Novice::LoadTexture("./Resources/StageText/fakejump.png");
	int letterSHandle = Novice::LoadTexture("./Resources/StageText/S.png");

	//Battery
	int EnergyHandle = Novice::Novice::LoadTexture("./Resources/HP/HP.png");
	int energyLineHandle = Novice::Novice::LoadTexture("./Resources/HP/HPLines.png");
	int batteryText = Novice::Novice::LoadTexture("./Resources/StageText/BATTERY.png");

	//Drill
	int drillText = Novice::Novice::LoadTexture("./Resources/StageText/DRILL.png");
	int drilledBlock = Novice::Novice::LoadTexture("./Resources/StageAssets/BrokenBlock.png");
	int drillLines = Novice::Novice::LoadTexture("./Resources/StageText/fakeDrill.png");

	//Life
	int lifeTextHandle = Novice::Novice::LoadTexture("./Resources/StageText/HP.png");

	int lifeHandle[6] =
	{
		{Novice::Novice::LoadTexture("./Resources/Life/Life0.png")},
		{Novice::Novice::LoadTexture("./Resources/Life/Life1.png")},
		{Novice::Novice::LoadTexture("./Resources/Life/Life2.png")},
		{Novice::Novice::LoadTexture("./Resources/Life/Life3.png")},
		{Novice::Novice::LoadTexture("./Resources/Life/Life4.png")},
		{Novice::Novice::LoadTexture("./Resources/Life/Life5.png")},
	};


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
	int playerHP_ = 5;
	
	//HP
	/*Size size_ = { 348,90 };
	float animationFrames = 2088.f;
	Vector2 animationPos_ = { 0.f, 0.f };*/
};

