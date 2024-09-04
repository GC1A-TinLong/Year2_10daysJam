#pragma once
#include "MathFunction.h"

class BlockNotDestroyable
{

public:

	BlockNotDestroyable();

	~BlockNotDestroyable();

	void Initialize(Vector2Int pos, bool isMoss, bool isWall);

	void Update();

	void DestroyIfUOB();

	void LoopWall();

	bool GetIsAboveScreen() { return isAboveScreen_; };

	void Draw();

private:

	Vector2Int pos_ = {};

	Vector2Int size = { 1,1 };

	int blockHandle_;

	bool isMoss_ = false;

	bool isWall_ = false;

	int wallMinY = -48;

	int wallMaxY = 720;

	bool isAboveScreen_ = false;
};

