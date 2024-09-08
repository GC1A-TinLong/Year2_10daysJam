#pragma once
#include "Novice.h"

class UserInterface
{
public:

	void Initialize();
	void Update();
	void Draw() const;

	//Setter
	void SetHPFrames(int hpFrames) { hpFrames_ = hpFrames; };


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
	int hpHandle[4]
	{
		{Novice::Novice::LoadTexture("./Resources/HP/HP4.png")},
		{Novice::Novice::LoadTexture("./Resources/HP/HP3.png")},
		{Novice::Novice::LoadTexture("./Resources/HP/HP2.png")},
		{Novice::Novice::LoadTexture("./Resources/HP/HP1.png")},
	};

	int hpFrames_ = 3;

	
};

