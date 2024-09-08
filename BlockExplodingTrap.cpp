#include "BlockExplodingTrap.h"
#include "Novice.h"

BlockExplodingTrap::~BlockExplodingTrap()
{
	delete shake_;
}

void BlockExplodingTrap::Initialize(Vector2 pos, bool isMoss, float scrollSpeed)
{
	pos_ = pos;
	isMoss_ = isMoss;
	scrollSpeed_ = scrollSpeed;
	if (isMoss_)
	{
		blockHandle_ = Novice::LoadTexture("./Resources/StageAssets/GrassTrapBlock.png");
	}
	else
	{
		blockHandle_ = Novice::LoadTexture("./Resources/StageAssets/TrapBlock.png");
	}
	shake_ = new Shake();
	shake_->Initialize();
}

void BlockExplodingTrap::Update()
{
	pos_.y -= scrollSpeed_;
	DestroyIfOOB();
	shake_->ActivateShake(5, 30);
	HP();
	Shakeing();
}

void BlockExplodingTrap::DestroyIfOOB()
{
	if (pos_.y <= -48.f)
	{
		isAboveScreen_ = true;
	}
}

void BlockExplodingTrap::HP()
{
	if (isTouched_ && hp >= 0 && takenDamage_ > 1) //player is on top of the block
	{
		hp -= takenDamage_;
	}

	//Return to max HP

	if (takenDamage_ == 0 && hp > 0 || !isTouched_ && hp > 0)
	{
		hp = hpMax;
	}

}

void BlockExplodingTrap::Shakeing()
{
	if (startShake_)
	{
		shake_->InfiniteShake(2);
	}
}

void BlockExplodingTrap::OnCollision(Player* player)
{
	(void)player;
	isTouched_ = true;
}

void BlockExplodingTrap::Draw()
{
	if (pos_.y >= -48.f && pos_.y <= 1080.f && hp >= 0)
	{
		Novice::DrawSprite((int)pos_.x + shake_->GetRandX(), (int)pos_.y + shake_->GetRandY(), blockHandle_, scale.x, scale.y, 0.0f, WHITE);
	}
}

const Object BlockExplodingTrap::GetObject_() const
{
	Object result{};
	result.pos = pos_;
	result.size = size;
	return result;

	
}
