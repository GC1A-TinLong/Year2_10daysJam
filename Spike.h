#pragma once
#include <iostream>
#include "MathFunction.h"

class Spike
{
private:
	bool isHit = false;
	bool isStart_ = false;

	static inline const uint8_t kSpeed = 5;
	static inline const uint16_t width = 48;
	static inline const uint16_t height = 48;
	Size size = { width,height };

	Vector2 pos_;

	uint32_t plainTexture_;
	uint32_t bloodTexture_;

	bool startFalling = false;

public:
	void Initialize(const Vector2& pos);
	void Update();
	void Draw();

	// Getter
	Vector2 GetPos() const { return pos_; }
	Size GetSize() const { return size; }
	const Object GetObject_() const;
	bool GetIsStart()const { return isStart_; };

	//Setter
	void SetIsStart(bool isStart) { isStart_ = isStart; };
};

