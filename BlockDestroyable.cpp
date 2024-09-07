#include "BlockDestroyable.h"
#include "Novice.h"

BlockDestroyable::~BlockDestroyable()
{
	delete shake_;
}

void BlockDestroyable::Initialize(Vector2 pos)
{
	pos_ = pos;
	blockHandle_ = Novice::LoadTexture("./Resources/StageAssets/BrokenBlock.png");
	shake_ = new Shake();
	shake_->Initialize();
}

void BlockDestroyable::Update()
{
	//pos_.y -= 1.f;
	DestroyIfOOB();
	shake_->ActivateShake(5, 30);
	HP();
	Shakeing();
}

void BlockDestroyable::DestroyIfOOB()
{
	if (pos_.y <= -float(size.height))
	{
		isAboveScreen_ = true;
	}
}

void BlockDestroyable::HP()
{
	if (isTouched_ && hp >= 0) //player is on top of the block
	{
		hp--;
	}

	if (!isTouched_ && hp > 0)
	{
		hp = hpMax;
	}

	if (hp <= 0)
	{
		//Block destroyed animation handle?
		hp = 0;
	}
}

void BlockDestroyable::Shakeing()
{
	if (startShake_)
	{
		shake_->InfiniteShake(2);
	}
}

void BlockDestroyable::OnCollision(Player* player)
{
	(void)player;
	isTouched_ = true;
}

const Object BlockDestroyable::GetObject_() const
{
	Object result{};
	result.pos = pos_;
	result.size = size;
	return result;
}

void BlockDestroyable::Draw()
{
	if (pos_.y >= -float(size.height) && pos_.y <= 720.f  && hp != 0)
	{
		Novice::DrawSprite((int)pos_.x, (int)pos_.y, blockHandle_, scale.x, scale.y, 0.0f, WHITE);
	}
}
