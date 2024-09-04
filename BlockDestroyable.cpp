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
	pos_.y -= 1;
	DestroyIfOOB();
}

void BlockDestroyable::DestroyIfOOB()
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
		Novice::DrawSprite((int)pos_.x, (int)pos_.y, blockHandle_, scale.x, scale.y, 0.0f, WHITE);
	}
}
