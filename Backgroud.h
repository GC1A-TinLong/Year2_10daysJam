#pragma once
#include "MathFunction.h"

class Background
{
public:

	void Initialize();
	void Update();
	void Draw();

	void ResetY();

	void RandomizeX();


private:

	int backgroundHandle[2] = {};
	Vector2 pos_[2] =
	{
		{0,0}, {0,1080}
	};
	unsigned int seed;
	unsigned int randX[2] = {0,0};
	int amplitude = 100;


};

