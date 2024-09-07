#pragma once
#include "MathFunction.h"

class Background
{
public:

	void Initialize();

	void Update();

	void ResetY();

	void RandomizeX();

	void Draw();

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

