#pragma once
#include "MathFunction.h"

class BlockSteel
{
public:

	BlockSteel();

	~BlockSteel();

	void Initialize(Vector2 pos, bool isWall);

	void Update(float scrollSpeed);
	void Draw() const;
	void DestroyIfOOB(); // out of bounds
	void LoopWall();

	//Getter
	bool GetIsAboveScreen() const { return isAboveScreen_; };
	Vector2 GetPos() const { return pos_; };
	Size GetSize() const { return size; };
	const Object GetObject_() const;

private:

	Vector2 pos_ = {};
	Vector2 scale = { 1.f,1.f };
	Size size = { 48,48 };

	bool isWall_ = false;
	float wallMinY = float(size.height * 1);
	float wallMaxY = float(size.height * 22);

	uint32_t blockHandle_;
	bool isAboveScreen_ = false;

};

