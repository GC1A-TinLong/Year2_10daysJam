#pragma once
#include "MathFunction.h"

class SpikeTrap
{
public:

	void Initialize(const Vector2& pos);
	void Update(float scrollSpeed);
	void Draw();

	// Getter
	Vector2 GetPos() const { return pos_; }
	Size GetSize() const { return size; }
	const Object GetObject_() const;

private:

	bool isHit = false;
	static inline const uint16_t width = 48;
	static inline const uint16_t height = 40;
	static inline const uint16_t heightHitboxOffset = 8;
	Size size = { width,height };
	Vector2 pos_;
	int texture_;

};

