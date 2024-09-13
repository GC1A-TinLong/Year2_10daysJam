#pragma once
#include "MathFunction.h"

class Goal
{
public:

	Goal();

	~Goal();

	void Initialize(Vector2 pos);

	void Update(float scrollSpeed);

	void Draw();

	Vector2 GetPos() const { return pos_; };
	Size GetSize() const { return size; };
	const Object GetObject_() const;
	bool GetStopMoving()const { return stopMoving; };

private:

	Vector2 pos_;
	Vector2 scale = { 1.f,1.f };
	Size size = { 1200 , 300};
	uint32_t texture_;
	uint32_t textTexture_;

	//Animation
	Vector2 animationPos_ = { 0.f, 0.f };
	float animationFrames = 9600.f;
	int animationTimer_ = 0;
	bool stopMoving = false;



};

