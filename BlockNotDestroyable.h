#pragma once
#include "MathFunction.h"

class BlockNotDestroyable
{

public:

	BlockNotDestroyable();

	~BlockNotDestroyable();

	void Initialize(Vector2Int pos);

	void Update();

	void Draw();

private:

	Vector2Int pos_ = {};

	Vector2Int size = { 48,48 };

	int blockHandle_;
};

