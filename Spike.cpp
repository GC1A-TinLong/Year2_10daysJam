#include "Spike.h"

void Spike::Initialize(const Vector2Int& pos)
{
	pos_ = pos;
}

void Spike::Update()
{
	if (isStart) {
		pos_.y += kSpeed;
	}
}

void Spike::Draw()
{
}
