#include "Player.h"
#include "Novice.h"
#include "Input.h"
#include "time.h"
#include <BasicTutorialScene.h>

Player::~Player()
{
	delete shake_;
}

void Player::Initialize(const Vector2& pos)
{
	pos_ = pos;
	playerIdleHandle_ = Novice::LoadTexture("./Resources/Player/digPlayer.png");
	playerMovingRightHandle_ = Novice::LoadTexture("./Resources/Player/digPlayer(R).png");
	playerMovingLeftHandle_ = Novice::LoadTexture("./Resources/Player/digPlayer(L).png");

	jumpAudioHandle = Novice::LoadAudio("./Resources/Audio/jump2.wav");

	sparkHandle_ = Novice::LoadTexture("./Resources/Player/spark1.png");

	seed = (unsigned int)time(nullptr);
	srand(seed);

	shake_ = new Shake();
	shake_->Initialize();
}


void Player::Update(float scrollSpeed)
{
	Audio();
	AnimationHolder();

	Scrolling(scrollSpeed);
	MovementInput();

	//Drilling();
	Shakeing();
	Exploded();

	TakingDamage();

	OnConveyor();

	pos_ += velocity_;
	pos_.x = std::clamp(pos_.x, minXPos, maxXPos);
}

void Player::Draw()
{
	if (!isTakingDamage_) {
		if (!isDead && !isDrilling || !isDead && !onGround)
		{
			Novice::DrawSpriteRect((int)(pos_.x) + shake_->GetRandX(), (int)pos_.y + shake_->GetRandY(),
				(int)animationPos_.x, (int)animationPos_.y, 42, 72, playerHandleHolder_, 42.f / currentAnimationFrames, 1.f, 0.0f, color);
		}
		else if (!isDead && isDrilling && onGround)	// go down a little bit
		{
			Novice::DrawSpriteRect((int)(pos_.x) + shake_->GetRandX(), (int)pos_.y + 15 + shake_->GetRandY(),
				(int)animationPos_.x, (int)animationPos_.y, 42, 72, playerHandleHolder_, 42.f / currentAnimationFrames, 1.f, 0.0f, color);
		}
	}
	else {
		if (!isDead && !isDrilling || !isDead && !onGround)
		{
			Novice::DrawSpriteRect((int)(pos_.x) + shake_->GetRandX(), (int)pos_.y + shake_->GetRandY(),
				(int)animationPos_.x, (int)animationPos_.y, 42, 72, playerHandleHolder_, 42.f / currentAnimationFrames, 1.f, 0.0f, color);
		}
		else if (!isDead && isDrilling && onGround)	// go down a little bit
		{
			Novice::DrawSpriteRect((int)(pos_.x) + shake_->GetRandX(), (int)pos_.y + 15 + shake_->GetRandY(),
				(int)animationPos_.x, (int)animationPos_.y, 42, 72, playerHandleHolder_, 42.f / currentAnimationFrames, 1.f, 0.0f, color);
		}
	}

	//Spark animation
	if (!isDead && isDrilling) 
	{
		Novice::DrawSpriteRect((int)(pos_.x) + shake_->GetRandX(), (int)pos_.y + 55 + shake_->GetRandY(),
			(int)sparkAnimationPos_.x, (int)sparkAnimationPos_.y, (int)sparkSize, 16, sparkHandle_, sparkSize / sparkAnimationFrames, 1.f, 0.0f, color);
	}

	//Novice::ScreenPrintf(0, 0, "player.velocity.x = %f", velocity_.x);
	//Novice::ScreenPrintf(0, 20, "player.velocity.y = %f", velocity_.y);

	//Novice::DrawBox((int)(pos_.x + widthOffset), (int)(pos_.y + drillPosOffset.y), drillSize.width, drillSize.height, 0.0f, WHITE, kFillModeWireFrame);
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
	DrillingSparks();

	if (Input::GetInstance()->PushKey(DIK_S) && onGround && !drillFatigue)
	{
		isDrilling = true;
	}
	else { isDrilling = false; }
	
	if (isDrilling)  
	{
		kMaxVelocity = 4.5f;
		if (onGround && drillPower > 0) 
		{
			drillPower -= drillEnergyReductionSpeed;
		}
	}
	else  
	{ 
		kMaxVelocity = 12.5f; 
		if (drillPower < maxDrillPower) 
		{
			drillPower += drillEnergyRestorationSpeed;
		}
	}

	if (drillPower <= 0.f) { drillFatigue = true; }
	if (drillPower >= 30 && drillFatigue) { drillFatigue = false; }

}

void Player::DrillingSparks()
{
	if (isDrilling) 
	{
		sparkAnimationTimer_++;

		if (sparkAnimationPos_.x >= sparkAnimationFrames - sparkSize && sparkAnimationTimer_ >= 4)
		{
			sparkAnimationPos_.x = 0;
			sparkAnimationTimer_ = 0;
		}

		if (sparkAnimationTimer_ >= 4)
		{
			sparkAnimationPos_.x += sparkSize;
			sparkAnimationTimer_ = 0;
		}
	}
}

void Player::Scrolling(float scrollSpeed)
{
	pos_.y -= scrollSpeed;
	if (pos_.y >= 1080 || pos_.y <= 0)
	{
		isDead = true;
	}

}

void Player::Exploded()
{
	if (isExploding_)
	{
		isTakingDamage_ = true;
		if(explodedTimer < 9)
		{
			velocity_.x += explosionVelocityX;
		}
		explodedTimer++;
		maxFallSpeed = 10.f;
	}  

	if (explodedTimer >= 1 && explodedTimer <= 3)
	{
		pos_.y -= 30.f;
	}

	if (explodedTimer >= 3 && explodedTimer <= 6)
	{
		pos_.y -= 26.f;
	}

	if (explodedTimer >= 6 && explodedTimer <= 15)
	{
		pos_.y -= 16.f;
	}

	if (explodedTimer >= 15 && explodedTimer <= 30)
	{
		pos_.y -= 12.f;
	}

	if (onGround) 
	{
		maxFallSpeed = 14.f;
	}

	if (explodedTimer == 1)
	{
		randX = (rand() % amplitude) - (amplitude / 2);
	}

	if (randX >= 0)
	{
		explosionVelocityX = 2;
	}
	else
	{
		explosionVelocityX =  -2;
	}

	if (explodedTimer > 30) 
	{
		isExploding_ = false;
		explodedTimer = 0;
	}
}

void Player::MovementInput()
{
	// LR Movement
	if (Input::GetInstance()->PushKey(DIK_D) || Input::GetInstance()->PushKey(DIK_A)) {
		kLRAcceleration = 0.8f;
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
			velocity_.y = (std::min)(velocity_.y, maxFallSpeed);
			isOnConveyor = false;
		}
	}
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
		float blockBottom = nonDesBlock->GetPos().y + nonDesBlock->GetSize().height;
		float leftPosBlock = nonDesBlock->GetPos().x;
		float rightPosBlock = nonDesBlock->GetPos().x + nonDesBlock->GetSize().width;
		
		bool isLeftCollision = (playerRightPos > leftPosBlock) && (playerLeftPos < leftPosBlock) &&
			(playerBottom > blockTop) && (pos_.y < blockBottom);
		bool isRightCollision = (playerLeftPos < rightPosBlock) && (playerRightPos > rightPosBlock) && (playerBottom > blockTop) && (pos_.y < blockBottom);
		
		if (isLeftCollision) {
			//pos_.x = leftPosBlock - spriteWidth;
			if (!isOnConveyor) 
			{
				pos_.x = leftPosBlock - size.width - 12;  // Stop at the block's left edge
			}
			else 
			{
				pos_.x = leftPosBlock - size.width - 16;
			}
			velocity_.x = 0;  // Stop horizontal movement
			kLRAcceleration = 0;

		}
		if (isRightCollision) {
			if (!isOnConveyor) 
			{
				pos_.x = rightPosBlock - 10;  // Stop at the block's right edge
			}
			else 
			{
				pos_.x = rightPosBlock - 6;  // Stop at the block's right edge

			}
			velocity_.x = 0;  // Stop horizontal movement
			kLRAcceleration = 0;
		}

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

void Player::OnConveyor()
{
	if (isRightConveyor) 
	{
		pos_.x+= conveyerSpeed;
	} 

	if (isLeftConveyor) 
	{
		pos_.x-= conveyerSpeed;
	}
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
	onGround = tempOnGround;

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
				if (convey->GetIsRight()) 
				{
					isRightConveyor = true;
				}
				else 
				{
					isLeftConveyor = true;
				}
			}
			// within the 3 conditions
			tempOnGround = true;
		}
		else 
		{
			isLeftConveyor = false;
			isRightConveyor = false;
		}
	}
	onGround = tempOnGround;
}

void Player::CollisionWithGoal(Goal* goal) 
{
	bool tempOnGround = false;		// temp flag, when its confirmed(ended loop), apply it to the origin flag

		float playerLeftPos = pos_.x + widthOffset;
		float playerRightPos = playerLeftPos + size.width;
		float playerBottom = pos_.y + size.height + velocity_.y;
		//float playerTop = pos_.y + velocity_.y;
		float blockTop = goal->GetPos().y;
		//float blockBottom = nonDesBlock->GetPos().y + nonDesBlock->GetSize().height;
		float leftPosBlock = goal->GetPos().x;
		float rightPosBlock = goal->GetPos().x + goal->GetSize().width;
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
				hasTouchedGoal = true;
			}
			// within the 3 conditions
			tempOnGround = true;
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
		if (drawCount <= kMaxDrawCount / 2) {
			color = halfAlphaWhite;
		}
		else { color = WHITE; }
	}

	if (iFrames == 1) { hp--; }

	if (iFrames >= 120)
	{
		isTakingDamage_ = false;
		iFrames = 0;
	}
	if (!isTakingDamage_) { color = WHITE; }

	/*if (drawCount <= kMaxDrawCount / 2) {
		color = halfAlphaWhite;
	}
	else { color = WHITE; }*/

	if (hp <= 0) { isDead = true; }
}

Object Player::GetDrillPointObject_() const
{
	Object result{};
	Vector2 position = { pos_.x + drillPosOffset.x,pos_.y + drillPosOffset.y };
	result.pos = position;
	result.size = drillSize;
	return result;
}