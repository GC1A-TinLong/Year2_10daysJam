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
	shake_ = new Shake();
	shake_->Initialize();
}

void BlockNotDestroyable::Update()
{
	if (isWall_) 
	{
		pos_.y -= 1.f;
		LoopWall();
	}
	else 
	{
		DestroyIfOOB();
		shake_->ActivateShake(5, 30);
	}
}

void BlockNotDestroyable::DestroyIfOOB()
{
	if (pos_.y <= -48.f)
	{
		isAboveScreen_ = true;
	}
}

void BlockNotDestroyable::OnCollision(Player* player)
{
	(void)player;
	isTouched = true;
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
	if (pos_.y >= -48.f && pos_.y <= 1080.f)
	{
		Novice::DrawSprite((int)pos_.x + shake_->GetRandX(), (int)pos_.y + shake_->GetRandY(), blockHandle_, scale.x, scale.y, 0.0f, WHITE);
	}
}
