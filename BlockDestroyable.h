#pragma once
#include "MathFunction.h"

class BlockDestroyable
{

public:

	~BlockDestroyable();

	void Initialize(Vector2 pos);

	void Update();

	void Draw();


private:

	Vector2 pos_ = {};

	Vector2 scale = { 1.f,1.f };

	uint32_t blockHandle_;

	bool isDestroyed = false;

};

