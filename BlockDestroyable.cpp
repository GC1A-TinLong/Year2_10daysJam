#include "BlockDestroyable.h"
#include "Novice.h"

BlockDestroyable::~BlockDestroyable()
{
}

void BlockDestroyable::Initialize(Vector2 pos)
{
	pos_ = pos;
	blockHandle_ = Novice::LoadTexture("./Resources/StageAssets/BrokenBlock.png");
}

void BlockDestroyable::Update()
{
}

void BlockDestroyable::Draw()
{
	Novice::DrawSprite((int)pos_.x, (int)pos_.y, blockHandle_, scale.x, scale.y, 0.0f, WHITE);
}
