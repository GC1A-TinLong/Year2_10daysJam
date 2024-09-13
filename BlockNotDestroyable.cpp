#include "BlockNotDestroyable.h"
#include "Novice.h"

BlockNotDestroyable::~BlockNotDestroyable()
{
	delete shake_;
}

void BlockNotDestroyable::Initialize(Vector2 pos, bool isMoss, bool isWall)
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

void BlockNotDestroyable::Update(float scrollSpeed)
{
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

	pos_.y -= scrollSpeed;
}

void BlockNotDestroyable::DestroyIfOOB()
{
	if (pos_.y <= -48.f)
	{
		isAboveScreen_ = true;
		hp = 0;
	}
}

void BlockNotDestroyable::HP()
{
	if (hp >= 0 && takenDamage_ > 0) //player is on top of the block
	{
		hp -= takenDamage_;
	}

	//Return to respective HP
	if (takenDamage_ == 0 || !isTouched_) {
		if (hp > hp70percent) { hp = kHpMax; }
		else if (hp <= hp70percent && hp > hpHalf) { hp = hp70percent; }
		else if (hp <= hpHalf && hp > hp30percent) { hp = hpHalf; }
		else if (hp <= hp30percent && hp > 0) { hp = hp30percent; }
	}

	if (hp > hpHalf) {
		if (isMoss_) {
			blockHandle_ = Novice::LoadTexture("./Resources/StageAssets/MossBlock.png");
		}
		else if (!isMoss_) {
			blockHandle_ = Novice::LoadTexture("./Resources/StageAssets/Block.png");
		}
	}
	else if (hp <= hpHalf) {
		if (isMoss_) {
			blockHandle_ = Novice::LoadTexture("./Resources/StageAssets/GrassTrapBlock.png");
		}
		else if (!isMoss_) {
			blockHandle_ = Novice::LoadTexture("./Resources/StageAssets/BrokenBlock.png");
		}
	}

	if (hp <= 0) { hp = 0; /*Block destroyed animation handle?*/ }
}

void BlockNotDestroyable::Shakeing()
{
	if (startShake_)
	{
		shake_->InfiniteShake(6); //Change amplitude here
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

void BlockNotDestroyable::Respawn()
{
	if (hp <= 0) {
		respawnTimer++;
		if (respawnTimer >= 90) {
			respawnTimer = 0;
			hp = kHpMax;
		}
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
