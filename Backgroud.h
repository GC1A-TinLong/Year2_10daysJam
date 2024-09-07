#pragma once
#include "MathFunction.h"
#define MAXBACKGROUNDS 2

class Background
{
public:

	void Initialize(int backgroundHandle[MAXBACKGROUNDS]);

	void Update();
	void Draw();

	void ResetY();

	void RandomizeX();


private:


	int backgroundHandle_[MAXBACKGROUNDS] = {};
	Vector2 pos_[MAXBACKGROUNDS] =
	{
		{0,0}, {0,1080}
	};
	unsigned int seed;
	unsigned int randX[MAXBACKGROUNDS] = {0,0};
	int amplitude = 100;


};

