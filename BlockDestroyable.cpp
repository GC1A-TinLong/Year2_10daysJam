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
	blockHandle_ = Novice::LoadTexture("./Resources/StageAssets/BrokenBlock.png");
}

void BlockDestroyable::Update()
{
}

void BlockDestroyable::Draw()
{
	Novice::DrawSprite(pos_.x, pos_.y, blockHandle_, (float)size.x, (float)size.y, 0.0f, WHITE);
}
