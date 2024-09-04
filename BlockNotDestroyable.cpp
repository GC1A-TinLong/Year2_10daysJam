#include "BlockNotDestroyable.h"
#include "Novice.h"

BlockNotDestroyable::BlockNotDestroyable()
{
}

BlockNotDestroyable::~BlockNotDestroyable()
{
}

void BlockNotDestroyable::Initialize(Vector2Int pos)
{
	pos_ = pos;
}

void BlockNotDestroyable::Update()
{
}

void BlockNotDestroyable::Draw()
{
	Novice::DrawBox(pos_.x, pos_.y, size.x, size.y, 0.0f, WHITE, kFillModeSolid);
}
