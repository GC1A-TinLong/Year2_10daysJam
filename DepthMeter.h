#pragma once
#include "MathFunction.h"
#include "Novice.h"

class DepthMeter
{
public:
	
	DepthMeter();

	~DepthMeter();

	void Initialize();

	void Update();

	void DepthCounter();

	void Draw();

	//Setter
	void SetPlayerYPos(float playerYDepth) { playerYDepth_ = playerYDepth; };

private:

	//Depth meter sprite
	Vector2 pos_;
	Vector2 playerPos_;
	int meterSprite_ = Novice::LoadTexture("./Resources/ProgressionMeter/meter.png");
	int meterPlayer_ = Novice::LoadTexture("./Resources/ProgressionMeter/meterPlayer.png");
	int starthandle_ = Novice::LoadTexture("./Resources/ProgressionMeter/START.png");
	int goalhandle_ = Novice::LoadTexture("./Resources/ProgressionMeter/GOAL.png");
	int zeroHandle_ = Novice::LoadTexture("./Resources/ProgressionMeter/0.png");
	int mHandle_ = Novice::LoadTexture("./Resources/ProgressionMeter/M.png");
	
	//this contains number 0 to 9
	int numbers[10] =  
	{
		{Novice::LoadTexture("./Resources/ProgressionMeter/0.png")},
		{Novice::LoadTexture("./Resources/ProgressionMeter/1.png")},
		{Novice::LoadTexture("./Resources/ProgressionMeter/2.png")},
		{Novice::LoadTexture("./Resources/ProgressionMeter/3.png")},
		{Novice::LoadTexture("./Resources/ProgressionMeter/4.png")},
		{Novice::LoadTexture("./Resources/ProgressionMeter/5.png")},
		{Novice::LoadTexture("./Resources/ProgressionMeter/6.png")},
		{Novice::LoadTexture("./Resources/ProgressionMeter/7.png")},
		{Novice::LoadTexture("./Resources/ProgressionMeter/8.png")},
		{Novice::LoadTexture("./Resources/ProgressionMeter/9.png")},
	};


	float depthCounter_ = 0.f;
	float playerYDepth_;
	float playerStartPos_ = 400.f;
	int units = 0;
	int tens = 0;
	int hundreds = 0;
	//int index;

};

