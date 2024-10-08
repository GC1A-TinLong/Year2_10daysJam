#include "BlockSteel.h"
#include "novice.h"

BlockSteel::BlockSteel()
{
}

BlockSteel::~BlockSteel()
{
}

void BlockSteel::Initialize(Vector2 pos, bool isWall)
{
	pos_ = pos;
	blockHandle_ = Novice::LoadTexture("./Resources/StageAssets/SteelBlock.png");

	isWall_ = isWall;
}

void BlockSteel::Update(float scrollSpeed)
{
	pos_.y -= scrollSpeed;
	DestroyIfOOB();
	if (isWall_) { LoopWall(); }
}

void BlockSteel::DestroyIfOOB()
{
	if (pos_.y <= -float(size.height))
	{
		isAboveScreen_ = true;
	}
}

void BlockSteel::LoopWall()
{
	if (pos_.y <= wallMinY)
	{
		pos_.y = wallMaxY;
	}
}

void BlockSteel::Draw() const
{
	if (pos_.y >= -float(size.height) && pos_.y <= 1080.f)
	{
		Novice::DrawSprite((int)pos_.x, (int)pos_.y, blockHandle_, scale.x, scale.y, 0.0f, WHITE);
	}
}

const Object BlockSteel::GetObject_() const
{
	Object result{};
	result.pos = pos_;
	result.size = size;
	return result;
}
