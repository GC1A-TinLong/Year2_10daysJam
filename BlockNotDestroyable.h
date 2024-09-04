#pragma once
#include "MathFunction.h"

class BlockNotDestroyable
{

public:

	BlockNotDestroyable();

	~BlockNotDestroyable();

	void Initialize(Vector2Int pos, bool isMoss, bool isWall);

	void Update();

	void LoopWall();

	void Draw();

private:

	Vector2Int pos_ = {};

	Vector2Int size = { 1,1 };

	int blockHandle_;

	bool isMoss_ = false;

	bool isWall_ = false;

	int wallMinY = -48;

	int wallMaxY = 720;
};

