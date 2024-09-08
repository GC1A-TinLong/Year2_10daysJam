#include "BlockNotDestroyable.h"
#include "Novice.h"

BlockNotDestroyable::~BlockNotDestroyable()
{
	delete shake_;
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
	//pos_.y -= 1.f;
	if (isWall_) 
	{
		
		LoopWall();
	}
	else 
	{
		DestroyIfOOB();
		shake_->ActivateShake(5, 30);
		HP();
		Shakeing();
	}
}

void BlockNotDestroyable::DestroyIfOOB()
{
	if (pos_.y <= -48.f)
	{
		isAboveScreen_ = true;
	}
}

void BlockNotDestroyable::HP()
{
	if (isTouched_ && hp >= 0 && takenDamage_ > 1) //player is on top of the block
	{
		hp -= takenDamage_;
	}

	//Return to max HP
	if (!isTouched_ && hp > 0) 
	{
		hp = hpMax;
	}

	//Return to half HP
	if (!isTouched_ && hp < hpHalf && hp > 0) 
	{
		hp = hpHalf;
	}

	if (hp < hpHalf) 
	{
		if (isMoss_)
		{
			blockHandle_ = Novice::LoadTexture("./Resources/StageAssets/GrassTrapBlock.png"); //ask Kouta to make broken moss block
		}
		else
		{
			blockHandle_ = Novice::LoadTexture("./Resources/StageAssets/BrokenBlock.png");
		}
	}

	if (hp <= 0)
	{
		hp = 0; //Block destroyed animation handle?
	}
}

void BlockNotDestroyable::Shakeing()
{
	if (startShake_) 
	{
		shake_->InfiniteShake(2);
	}
}

void BlockNotDestroyable::OnCollision(Player* player)
{
	(void)player;
	isTouched_ = true;
}

void BlockNotDestroyable::LoopWall()
{
	if (pos_.y <= wallMinY)
	{
		pos_.y = wallMaxY;
	}
}

const Object BlockNotDestroyable::GetObject_() const
{
	Object result{};
	result.pos = pos_;
	result.size = size;
	return result;
}

void BlockNotDestroyable::Draw()
{
	if (pos_.y >= -48.f && pos_.y <= 1080.f && hp != 0)
	{
		Novice::DrawSprite((int)pos_.x + shake_->GetRandX(), (int)pos_.y + shake_->GetRandY(), blockHandle_, scale.x, scale.y, 0.0f, WHITE);
	}
}
