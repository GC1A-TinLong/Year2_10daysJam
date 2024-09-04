#include "BlockNotDestroyable.h"
#include "Novice.h"

BlockNotDestroyable::~BlockNotDestroyable()
{
}

void BlockNotDestroyable::Initialize(Vector2 pos,bool isMoss, bool isWall)
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
	else 
	{
		DestroyIfOOB();
	}
}

void BlockNotDestroyable::DestroyIfOOB()
{
	if (pos_.y <= -48) 
	{
		isAboveScreen_ = true;
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
	if (pos_.y >= -48 && pos_.y <= 720)
	{
		Novice::DrawSprite((int)pos_.x, (int)pos_.y, blockHandle_, scale.x, scale.y, 0.0f, WHITE);
	}
}
