#pragma once
#include "MathFunction.h"

class Explosion
{
public:

	~Explosion();
	void Initialize(Vector2 pos);
	void Update();
	void Draw();

	//Setter
	void SetIsExploding(bool isExploding) {isExploding_ = isExploding; };

	//Getter
	bool GetIsExploding() { return isExploding_; };

private:

	Vector2 pos_;
	Size size_ = { 48,48 };
	Vector2 scale = { 1.f,1.f };

	//Animation
	Vector2 animationPos_ = { 0.f, 0.f };
	float animationFrames = 432.f;
	int animationTimer_ = 0;
	uint32_t texture_;

	bool isExploding_ = false;
};

