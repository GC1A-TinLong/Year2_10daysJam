#include "BlockNotDestroyable.h"
#include "Novice.h"

BlockNotDestroyable::BlockNotDestroyable()
{
}

BlockNotDestroyable::~BlockNotDestroyable()
{
}

void BlockNotDestroyable::Initialize(Vector2Int pos,bool isMoss, bool isWall)
{
	pos_ = pos;
	isMoss_ = isMoss;
	isWall_ = isWall;

	if (isMoss_) 
	{
		blockHandle_ = Novice::LoadTexture("./Resources/StageAssets/MossBlock.png");
	}
	else 
	{
		blockHandle_ = Novice::LoadTexture("./Resources/StageAssets/Block.png");

	}
}

void BlockNotDestroyable::Update()
{
	pos_.y -= 1;
	if (isWall_) 
	{
		LoopWall();
	}
}

void BlockNotDestroyable::LoopWall()
{
	if (pos_.y <= wallMinY) 
	{
		pos_.y = wallMaxY;
	}
}

void BlockNotDestroyable::Draw()
{
	Novice::DrawSprite(pos_.x, pos_.y, blockHandle_, (float)size.x, (float)size.y, 0.0f, WHITE);
}
