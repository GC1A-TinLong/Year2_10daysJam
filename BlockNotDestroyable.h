#pragma once
#include "struct.h"

class BlockNotDestroyable
{

public:

	BlockNotDestroyable();

	~BlockNotDestroyable();

	void Initialize(Vector2 pos);

	void Update();

	void Draw();

private:

	Vector2 pos_ = {};

	Vector2 size = { 48,48 };

	int blockHandle_;
};

