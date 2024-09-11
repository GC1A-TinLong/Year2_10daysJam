#pragma once
#include "MathFunction.h"

class BlockSteel
{
public:

	BlockSteel();

	~BlockSteel();

	void Initialize(Vector2 pos);

	void Update(float scrollSpeed);

	void DestroyIfOOB(); // out of bounds

	void Draw();

	//Getter
	bool GetIsAboveScreen() const { return isAboveScreen_; };
	Vector2 GetPos() { return pos_; };
	Size GetSize() { return size; };
	const Object GetObject_() const;

private:

	Vector2 pos_ = {};
	Vector2 scale = { 1.f,1.f };
	Size size = { 48,48 };

	uint32_t blockHandle_;
	bool isAboveScreen_ = false;

};

