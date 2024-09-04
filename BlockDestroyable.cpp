#include "BlockDestroyable.h"
#include "Novice.h"

BlockDestroyable::BlockDestroyable()
{
}

BlockDestroyable::~BlockDestroyable()
{
}

void BlockDestroyable::Initialize(Vector2Int pos)
{
	pos_ = pos;
}

void BlockDestroyable::Update()
{
}

void BlockDestroyable::Draw()
{
	Novice::DrawBox(pos_.x, pos_.y, size.x, size.y, 0.0f, WHITE, kFillModeSolid);
}
