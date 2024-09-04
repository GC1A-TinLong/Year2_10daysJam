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
	pos_.y -= 1;
	DestroyIfUOB();
}

void BlockDestroyable::DestroyIfUOB()
{
	if (pos_.y <= -48)
	{
		isAboveScreen_ = true;
	}
}

void BlockDestroyable::Draw()
{
	
	if (pos_.y >= -48 && pos_.y <= 720)
	{
		Novice::DrawSprite(pos_.x, pos_.y, blockHandle_, (float)size.x, (float)size.y, 0.0f, WHITE);
	}
}
