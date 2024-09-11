#pragma once
#include "MathFunction.h"

enum class PauseStatus 
{
	None,
	PauseMenu1,
	PauseMenu2,

};

class Pause
{
public:

	void Initialize();

	void Update();

	void PauseAnimation();

	void PauseMenu1Menuing();
	void PauseMenu2Menuing();

	void Draw();

	bool GetIsPaused() { return isPaused_; };

	bool GetCloseGame() { return closeGame; };

	void SetIsPaused(bool isPaused) { isPaused_ = isPaused; };

private:

	

	int pause1Handle_;
	int pause2Handle_;
	int pauseTextOnlyHandle_;
	Vector2 pos_ = { 0,0 };
	Vector2 scale = { 0.25,1 };
	bool hasPressedDown = false;
	int animationTimer = 0;
	int maxFrames = 60;
	int pressTimer = 0;
	bool isPaused_ = false;
	bool isOnMeny2 = false;
	bool closeGame = false;
	PauseStatus pauseStatus_ = PauseStatus::None;



};

