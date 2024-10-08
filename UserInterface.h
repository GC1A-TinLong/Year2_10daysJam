#pragma once
#include "Novice.h"
#include <iostream>
#include "MathFunction.h"

class UserInterface
{
public:

	~UserInterface();
	/// <summary>
	/// -1 = StageSelect, 0 = Tutorial
	/// </summary>
	void Initialize(int currentStage);
	void Update(bool isShowingDrillUI, bool isTutorial);
	void Countdown();
	void Draw() const;

	//Setter
	void SetDrillPower(float drillPower) { drillPower_ = drillPower; };
	void SetIsDrilling(bool isDrilling) { isDrilling_ = isDrilling; };
	void SetPlayerHP(int playerHP) { playerHP_ = playerHP; };
	void SetStartGame(bool startGame) { startGame_ = startGame; };

	//Getter
	bool GetStartGame()const { return startGame_; };
	

private:

	//UI Handles
	unsigned int stageTextHandle_ = Novice::LoadTexture("./Resources/StageText/STAGE.png");
	unsigned int stageNumberHandle;
	unsigned int controlsHandle = Novice::LoadTexture("./Resources/StageText/CONTROLS.png");
	unsigned int letterDHandle = Novice::LoadTexture("./Resources/StageText/D.png");
	unsigned int letterAHandle = Novice::LoadTexture("./Resources/StageText/A.png");
	unsigned int rightPlayer = Novice::LoadTexture("./Resources/Player/digPlayer(R).gif");
	unsigned int leftPlayer = Novice::LoadTexture("./Resources/Player/digPlayer(L).gif");
	unsigned int spaceHandle = Novice::LoadTexture("./Resources/StageText/SPACE.png");
	unsigned int jumpPlayer = Novice::LoadTexture("./Resources/Player/player.gif");
	unsigned int jumpLines = Novice::LoadTexture("./Resources/StageText/fakejump.png");
	unsigned int letterSHandle = Novice::LoadTexture("./Resources/StageText/S.png");
	unsigned int UIHandle = Novice::LoadTexture("./Resources/StageText/UI.png");

	//Battery
	unsigned int EnergyHandle = Novice::LoadTexture("./Resources/HP/energy1.png");
	unsigned int energyLineHandle = Novice::LoadTexture("./Resources/HP/HPLines.png");
	unsigned int batteryText = Novice::LoadTexture("./Resources/StageText/BATTERY.png");

	//Drill
	unsigned int drillText = Novice::LoadTexture("./Resources/StageText/DRILL.png");
	unsigned int drillingPlayer = Novice::LoadTexture("./Resources/StageText/drillingUI.png");/*
	unsigned int blackEdge = Novice::LoadTexture("./Resources/StageText/blackEdge.png");
	unsigned int transparentEdge = Novice::LoadTexture("./Resources/StageText/transparentEdge.png");*/
	unsigned int yellow = Novice::LoadTexture("./Resources/StageText/yellow.png");

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
	uint32_t drillBoxR = 255;
	uint32_t drillBoxG = 255;
	uint32_t drillBoxB = 255;
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
	
	//Countdown
	Vector2 pos_{ 0.f,0.f };
	Size size_ = { 1920,1080 };
	Vector2 scale = { 1.f,1.f };

	//Animation
	Vector2 animationPos_ = { 0.f, 0.f };
	float animationFrames = 7680.f;
	int animationTimer_ = 0;
	uint32_t texture_;
	bool startGame_ = false;
	bool isExploding_ = false;



};

