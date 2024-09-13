#include "BlockDestroyable.h"
#include "Novice.h"

BlockDestroyable::~BlockDestroyable()
{
	delete shake_;
}

void BlockDestroyable::Initialize(Vector2 pos)
{
	pos_ = pos;
	blockHandle_ = Novice::LoadTexture("./Resources/StageAssets/BrokenMossBlock.png");
	shake_ = new Shake();
	shake_->Initialize();
}

void BlockDestroyable::Update(float scrollSpeed)
{
	pos_.y -= scrollSpeed;
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
		hp -= takenDamage_;
	}

	if (!isTouched_ && hp > 0)
	{
		hp = kHpMax;
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
		shake_->InfiniteShake(6); //Change amplitude here
	}
}

void BlockDestroyable::OnCollision(Player* player)
{
	(void)player;
	isTouched_ = true;
}

void BlockDestroyable::Respawn()
{
	if (hp <= 0) {
		respawnTimer++;
		if (respawnTimer >= 60) {
			respawnTimer = 0;
			hp = kHpMax;
		}
	}
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
	if (pos_.y >= -float(size.height) && pos_.y <= 1080.f  && hp != 0)
	{
		Novice::DrawSprite((int)pos_.x + shake_->GetRandX(), (int)pos_.y + shake_->GetRandY(), blockHandle_, scale.x, scale.y, 0.0f, WHITE);
	}
}
