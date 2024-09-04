#pragma once
#include "MathFunction.h"

class BlockNotDestroyable
{

public:

	~BlockNotDestroyable();

	void Initialize(Vector2 pos, bool isMoss, bool isWall);

	void Update();

	void DestroyIfUOB();

	void LoopWall();

	bool GetIsAboveScreen() { return isAboveScreen_; };

	void Draw();

private:

	Vector2 pos_ = {};

	Vector2 scale = { 1.f,1.f };

	uint32_t blockHandle_;

	bool isMoss_ = false;

	bool isWall_ = false;

	float wallMinY = -48.f;

	float wallMaxY = 720.f;

	bool isAboveScreen_ = false;
};

