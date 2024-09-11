#include "BlockSteel.h"
#include "novice.h"

BlockSteel::BlockSteel()
{
}

BlockSteel::~BlockSteel()
{
}

void BlockSteel::Initialize(Vector2 pos)
{
	pos_ = pos;
}

void BlockSteel::Update(float scrollSpeed)
{
	pos_.y -= scrollSpeed;
	DestroyIfOOB();
}

void BlockSteel::DestroyIfOOB()
{
	if (pos_.y <= -float(size.height))
	{
		isAboveScreen_ = true;
	}
}

void BlockSteel::Draw()
{
	if (pos_.y >= -float(size.height) && pos_.y <= 720.f)
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
