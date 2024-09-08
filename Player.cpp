#include "Player.h"
#include "Novice.h"
#include "Input.h"

void Player::InitializeFlag()
{
	isMaxSpeed = false;
	isPressingSpace = false;
}

void Player::Initialize(const Vector2& pos)
{
	pos_ = pos;
	playerIdleHandle_ = Novice::LoadTexture("./Resources/Player/digPlayer.png");
	playerMovingRightHandle_ = Novice::LoadTexture("./Resources/Player/digPlayer(R).png");
	playerMovingLeftHandle_ = Novice::LoadTexture("./Resources/Player/digPlayer(L).png");

	jumpAudioHandle = Novice::LoadAudio("./Resources/Audio/jump2.wav");

	shake_ = new Shake();
	shake_->Initialize();
}


void Player::Update()
{
	Audio();
	AnimationHolder();

	Scrolling();
	MovementInput();

	Drilling();
	Shakeing();

	TakingDamage();
}

void Player::Draw()
{
	if (drawCount <= kMaxDrawCount / 2)	// if taking damage, blink the character
	{
		if (!isDead && !isDrilling)
		{
			Novice::DrawSpriteRect((int)(pos_.x) + shake_->GetRandX(), (int)pos_.y + shake_->GetRandY(),
				(int)animationPos_.x, (int)animationPos_.y, 42, 72, playerHandleHolder_, 42.f / currentAnimationFrames, 1.f, 0.0f, WHITE);
		}
		else if (!isDead && isDrilling && onGround)	// go down a little bit
		{
			Novice::DrawSpriteRect((int)(pos_.x) + shake_->GetRandX(), (int)pos_.y + 15 + shake_->GetRandY(),
				(int)animationPos_.x, (int)animationPos_.y, 42, 72, playerHandleHolder_, 42.f / currentAnimationFrames, 1.f, 0.0f, WHITE);
		}
	}
	Novice::ScreenPrintf(0, 0, "player.velocity.x = %f", velocity_.x);
	Novice::ScreenPrintf(0, 20, "player.velocity.y = %f", velocity_.y);
	Novice::ScreenPrintf(0, 40, "player.pos.x = %f", (pos_.x + widthOffset));
	Novice::ScreenPrintf(0, 60, "player.pos.y = %f", pos_.y);
	Novice::ScreenPrintf(0, 80, "onGround = %d", onGround);
	Novice::ScreenPrintf(0, 100, "isTakingDamage = %d", isTakingDamage_);
	Novice::ScreenPrintf(0, 120, "isDrilling = %d", isDrilling);
	Novice::ScreenPrintf(0, 140, "hp = %d", hp);

	Novice::DrawBox((int)(pos_.x + widthOffset), (int)(pos_.y + drillPosOffset.y), drillSize.width, drillSize.height, 0.0f, WHITE, kFillModeWireFrame);
}

void Player::Audio()
{
	if (Input::GetInstance()->TriggerKey(DIK_SPACE) && onGround)
	{
		if (Novice::IsPlayingAudio(jumpPlayHandle) == 0 || jumpPlayHandle == -1) {
			jumpPlayHandle = Novice::PlayAudio(jumpAudioHandle, 0, kJumpAudioVolume);
		}
	}
}

void Player::AnimationHolder()
{
	animationTimer_++;

	if (animationPos_.x >= currentAnimationFrames - 42)
	{
		animationPos_.x = 0;
	}

	if (animationTimer_ >= 4)
	{
		animationPos_.x += 42;
		animationTimer_ = 0;
	}

	SwitchPlayerAnimationState();
}

void Player::SwitchPlayerAnimationState()
{
	previousPlayerAnimation_ = playerAnimation_; // record prev animation

	if (Input::GetInstance()->PushKey(DIK_D))
	{
		playerAnimation_ = PlayerAnimation::Right;
	}
	else if (Input::GetInstance()->PushKey(DIK_A))
	{
		playerAnimation_ = PlayerAnimation::Left;
	}
	else
	{
		playerAnimation_ = PlayerAnimation::Idle;
	}

	if (previousPlayerAnimation_ != playerAnimation_)
	{
		animationPos_.x = 0; // Reset animation position when the animation state changes
	}

	switch (playerAnimation_)
	{
	case Player::PlayerAnimation::Idle:
		playerHandleHolder_ = playerIdleHandle_;
		currentAnimationFrames = 126.f;
		break;
	case Player::PlayerAnimation::Right:
		playerHandleHolder_ = playerMovingRightHandle_;
		currentAnimationFrames = 126.f;
		break;
	case Player::PlayerAnimation::Left:
		playerHandleHolder_ = playerMovingLeftHandle_;
		currentAnimationFrames = 126.f;
		break;
	default:
		break;
	}
}

void Player::Drilling()
{
	if (onGround && Input::GetInstance()->PushKey(DIK_S))
	{
		isDrilling = true;
	}
	else if(!Input::GetInstance()->PushKey(DIK_S) || !onGround) {
		isDrilling = false;
	}

	if (isDrilling)  { kMaxVelocity = 4.5f; }
	else  { kMaxVelocity = 12.5f; }
}

void Player::Scrolling()
{
	pos_.y -= 1.f;
	if (pos_.y >= 1080)
	{
		isDead = true;
	}

}

void Player::MovementInput()
{
	// LR Movement
	if (Input::GetInstance()->PushKey(DIK_D) || Input::GetInstance()->PushKey(DIK_A)) {
		Vector2 acceleration = {};
		if (Input::GetInstance()->PushKey(DIK_D)) {
			if (direction != LRDirection::right) { // player direction
				direction = LRDirection::right;
			}

			if (velocity_.x < 0.0f) { // when pushing opposing input, attenuate velocity
				velocity_.x *= (1.0f - kAttenuation);
			}

			acceleration.x += kLRAcceleration;
		}
		else if (Input::GetInstance()->PushKey(DIK_A)) {
			if (direction != LRDirection::left) { // player direction
				direction = LRDirection::left;
			}

			if (velocity_.x > 0.0f) { // when pushing opposing input, attenuate velocity
				velocity_.x *= (1.0f - kAttenuation);
			}
			acceleration.x -= kLRAcceleration;
		}
		velocity_.x = velocity_.x + acceleration.x;
		velocity_.x = std::clamp(velocity_.x, -kMaxVelocity, kMaxVelocity);
	}
	else {
		velocity_.x *= (1.0f - kAttenuation);
		if (fabsf(velocity_.x) < 0.4f) {
			velocity_.x = 0;
		}
	}
	// Jump
	if (onGround) {
		if (Input::GetInstance()->TriggerKey(DIK_SPACE)) {
			isPressingSpace = true;
			isMaxSpeed = false;
			prevPos_ = pos_;
		}
		if (isPressingSpace) {
			velocity_.y -= kInitJumpAcceleration;
		}

		if (prevPos_.y - pos_.y >= kMinInitHeight) {
			onGround = false;
			isPressingSpace = false;
		}
	}
	else {
		// if pressing SPACE continuously, add jump force
		if (Input::GetInstance()->PushKey(DIK_SPACE) && !isMaxSpeed && isPressingSpace) {
			velocity_.y -= kContinuousJumpAcceleration;
			isPressingSpace = true;
		}
		else if (!Input::GetInstance()->PushKey(DIK_SPACE)) {	// released SPACE key
			isPressingSpace = false;
			if (velocity_.y < 0) {
				velocity_.y = (std::max)(velocity_.y, -8.0f);	// limiting Jump speed, slowing it to X amount (returning the bigger amount)
			}
		}

		if (velocity_.y <= kMaxJumpSpeed) {
			isMaxSpeed = true;
		}
		// Start free fall
		if (!onGround || isMaxSpeed) {
			velocity_.y += kFreeFallAcceleration;
			velocity_.y = (std::min)(velocity_.y, kMaxFallSpeed);
			isOnConveyor = false;
		}
	}
	pos_ += velocity_;
	pos_.x = std::clamp(pos_.x, minXPos, maxXPos);
}

void Player::OnCollision()
{
	//hp--;
	//isDead = true;
	isTakingDamage_ = true;
}

void Player::OnCollision(BlockExplodingTrap* explodingblock)
{
	(void)explodingblock;
	velocity_.y += 5.f;
}

void Player::Shakeing()
{
	shake_->ActivateShake(10, 60);
}

void Player::CollisionWithBlock(std::vector<BlockNotDestroyable*>& nonDesBlocks)
{
	bool tempOnGround = false;		// temp flag, when its confirmed(ended loop), apply it to the origin flag

	for (BlockNotDestroyable* nonDesBlock : nonDesBlocks) {
		float playerLeftPos = pos_.x + widthOffset;
		float playerRightPos = playerLeftPos + size.width;
		float playerBottom = pos_.y + size.height + velocity_.y;
		//float playerTop = pos_.y + velocity_.y;
		float blockTop = nonDesBlock->GetPos().y;
		//float blockBottom = nonDesBlock->GetPos().y + nonDesBlock->GetSize().height;
		float leftPosBlock = nonDesBlock->GetPos().x;
		float rightPosBlock = nonDesBlock->GetPos().x + nonDesBlock->GetSize().width;
		if (velocity_.y < 0) {
			continue;
		}
		// Conditions
		bool isWithinHorizontalBounds = (playerLeftPos <= rightPosBlock) && (playerRightPos >= leftPosBlock);
		bool isCloseEnoughVertically = (blockTop - playerBottom <= kCloseEnoughDistanceWithBlock);	// above block
		// player.bot without velocity && blockTop + small amount to prevent falling through
		bool isPlayerBelowBlock = (playerBottom - velocity_.y >= blockTop + 1.f);

		if (isWithinHorizontalBounds && isCloseEnoughVertically && !isPlayerBelowBlock) {
			if (velocity_.y > 0) {	// only when falling
				pos_.y = blockTop - size.height;
				velocity_.y = 0;
				isPressingSpace = false;
			}
			// within the 3 conditions
			tempOnGround = true;
		}
	}
	onGround = tempOnGround;

}

void Player::CollisionWithExplodingBlock(std::vector<BlockExplodingTrap*>& explodingBlocks)
{
	bool tempOnGround = false;		// temp flag, when its confirmed(ended loop), apply it to the origin flag

	for (BlockExplodingTrap* explBlock : explodingBlocks) {
		float playerLeftPos = pos_.x + widthOffset;
		float playerRightPos = playerLeftPos + size.width;
		float playerBottom = pos_.y + size.height + velocity_.y;
		//float playerTop = pos_.y + velocity_.y;
		float blockTop = explBlock->GetPos().y;
		//float blockBottom = nonDesBlock->GetPos().y + nonDesBlock->GetSize().height;
		float leftPosBlock = explBlock->GetPos().x;
		float rightPosBlock = explBlock->GetPos().x + explBlock->GetSize().width;
		if (velocity_.y < 0) {
			continue;
		}
		// Conditions
		bool isWithinHorizontalBounds = (playerLeftPos <= rightPosBlock) && (playerRightPos >= leftPosBlock);
		bool isCloseEnoughVertically = (blockTop - playerBottom <= kCloseEnoughDistanceWithBlock);	// above block
		// player.bot without velocity && blockTop + small amount to prevent falling through
		bool isPlayerBelowBlock = (playerBottom - velocity_.y >= blockTop + 1.f);

		if (isWithinHorizontalBounds && isCloseEnoughVertically && !isPlayerBelowBlock) {
			if (velocity_.y > 0) {	// only when falling
				pos_.y = blockTop - size.height;
				velocity_.y = 0;
				isPressingSpace = false;
			}
			// within the 3 conditions
			tempOnGround = true;
		}
	}
	//onGround = tempOnGround;

}

void Player::CollisiontWithConveyor(std::vector<Conveyor*>& conveyor)
{
	bool tempOnGround = false;		// temp flag, when its confirmed(ended loop), apply it to the origin flag

	for (auto* convey : conveyor) {
		float playerLeftPos = pos_.x + widthOffset;
		float playerRightPos = playerLeftPos + size.width;
		float playerBottom = pos_.y + size.height + velocity_.y;
		float blockTop = convey->GetPos().y;
		float leftPosBlock = convey->GetPos().x;
		float rightPosBlock = convey->GetPos().x + convey->GetSize().width;
		if (velocity_.y < 0) {
			continue;
		}
		// Conditions
		bool isWithinHorizontalBounds = (playerLeftPos <= rightPosBlock) && (playerRightPos >= leftPosBlock);
		bool isCloseEnoughVertically = (blockTop - playerBottom <= kCloseEnoughDistanceWithBlock);	// above block
		// player.bot without velocity && blockTop + small amount to prevent falling through
		bool isPlayerBelowBlock = (playerBottom - velocity_.y >= blockTop + 1.f);

		if (isWithinHorizontalBounds && isCloseEnoughVertically && !isPlayerBelowBlock) {
			if (velocity_.y > 0) {	// only when falling
				pos_.y = blockTop - size.height;
				velocity_.y = 0;
				isPressingSpace = false;
				isOnConveyor = true;	// conveyor flag
			}
			// within the 3 conditions
			tempOnGround = true;
		}
	}
	onGround = tempOnGround;
}

Vector2 Player::CameraOffset()
{
	Vector2 offset{};
	/*prevPos_ = pos_;

	pos_ += velocity_;
	offset = pos_ - prevPos_;*/

	return offset;
}

Object Player::GetObject_() const
{
	Object result{};
	result.pos.x = pos_.x + widthOffset;
	result.pos.y = pos_.y;
	result.size = size;
	return result;
}

void Player::TakingDamage()
{
	if (isTakingDamage_) 
	{
		iFrames++;
		drawCount++;
		if (drawCount >= kMaxDrawCount) {
			drawCount = 0;
		}
	}

	if (iFrames == 1)
	{
		hp--;
	}

	if (iFrames >= 120) 
	{
		isTakingDamage_ = false;
		iFrames = 0;
		drawCount = 0;
	}

	if (hp <= 0) 
	{
		isDead = true;
	}
}

Object Player::GetDrillPointObject_() const
{
	Object result{};
	Vector2 position = { pos_.x + drillPosOffset.x,pos_.y + drillPosOffset.y };
	result.pos = position;
	result.size = drillSize;
	return result;
}