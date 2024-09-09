#pragma once
#include "MathFunction.h"

class Player;

class Conveyor
{


public:
	void Initialize(Vector2 pos/*, Size size*/, bool isRight, float scrollSpeed);
	void Update();

	void DestroyIfOOB(); // out of bounds

	void Animation();

	void Draw();

	void OnCollisionPlayer(Player* player);

	// Getter
	Object GetObject_();
	Vector2 GetPos() const { return pos_; }
	Size GetSize() const { return size_; }
	bool GetIsAboveScreen() const { return isAboveScreen_; };
	bool GetIsRight() const { return isRight_; };

private:
	
	enum class LRDirection
	{
		left,
		right,
	};

	LRDirection direction_ = LRDirection::left;

	Vector2 pos_;
	Size size_ = { 226,48 };
	Vector2 scale = { 1.f,1.f };

	//Animation
	Vector2 animationPos_ = { 0.f, 0.f };
	float animationFrames = 452.f;
	int animationTimer_ = 0;
	uint32_t texture_;

	bool isAboveScreen_ = false;
	bool isTouched_ = false;
	bool isRight_ = false;

	//Scroll speed
	float scrollSpeed_;
};

