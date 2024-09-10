#pragma once
#include "MathFunction.h"

class Goal
{
public:

	Goal();

	~Goal();

	void Initialize(Vector2 pos, float scrollSpeed);

	void Update();

	void Draw();

	Vector2 GetPos() const { return pos_; };
	Size GetSize() const { return size; };
	const Object GetObject_() const;

private:

	Vector2 pos_;
	Vector2 scale = { 1.f,1.f };
	Size size = { 1200 , 300};
	float scrollSpeed_ = 0.f;
	uint32_t texture_;

};

