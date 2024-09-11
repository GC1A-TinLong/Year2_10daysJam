#pragma once
#include "MathFunction.h"
#define MAXBACKGROUNDS 2

class Background
{
public:

	void Initialize(int backgroundHandle[MAXBACKGROUNDS]);

	void Update(float scrollSpeed);
	void Draw() const;

	void ResetY(float scrollSpeed);

	//void RandomizeX();


private:


	int backgroundHandle_[MAXBACKGROUNDS] = {};
	Vector2 pos_[MAXBACKGROUNDS] =
	{
		{0,0}, 
		{0,1080.f},
		/*{0,2160.f},
		{0,3240.f},*/
	};
	unsigned int seed;
	//unsigned int randX = 0;
	int amplitude = 100;


};

