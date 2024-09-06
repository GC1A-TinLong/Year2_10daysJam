#include "Player.h"
#include "Novice.h"
#include "Input.h"

void Player::InitializeFlag()
{
	isMaxSpeed = false;
	isPressingSpace = false;
	isReleasedSpace = false;
	isFreeFalling = false;
	isOnTopOfBlock = true;
}

void Player::Initialize(const Vector2& pos)
{
	pos_ = pos;
	playerIdleHandle_ = Novice::LoadTexture("./Resources/Player/player.png");
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
	MovementInput();
	Shakeing();
}

void Player::Draw()
{
	if (!isDead) {
		Novice::DrawSpriteRect((int)pos_.x + shake_->GetRandX(), (int)pos_.y + shake_->GetRandY(), (int)animationPos_.x, (int)animationPos_.y, 42, 72, playerHandleHolder_, 42.f / currentAnimationFrames, 1.f, 0.0f, WHITE);
	}
	Novice::ScreenPrintf(0, 0, "player.velocity.x = %f", velocity_.x);
	Novice::ScreenPrintf(0, 20, "player.velocity.y = %f", velocity_.y);
	Novice::ScreenPrintf(0, 40, "player.pos.x = %f", pos_.x);
	Novice::ScreenPrintf(0, 60, "player.pos.y = %f", pos_.y);
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
		currentAnimationFrames = 504.f;;

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
		if (fabsf(velocity_.x) < 0.3f) {
			velocity_.x = 0;
		}
	}
	// Jump
	if (onGround) {
		if (Input::GetInstance()->TriggerKey(DIK_SPACE)) {
			velocity_.y -= kInitJumpAcceleration;
			isPressingSpace = true;
			isReleasedSpace = false;
			prevPos_ = pos_;
		}

		if (prevPos_.y - pos_.y >= kMinInitHeight) {
			onGround = false;
			isPressingSpace = false;
		}
	}
	else {
		// if continuously pressing SPACE, add jump force
		if (Input::GetInstance()->PushKey(DIK_SPACE) && !isMaxSpeed && !isReleasedSpace) {	
			velocity_.y -= kContinuousJumpAcceleration;
			isPressingSpace = true;
		}
		else if (!Input::GetInstance()->PushKey(DIK_SPACE)) {	// released SPACE key
			isPressingSpace = false;
			isReleasedSpace = true;
			if (!isFreeFalling && velocity_.y < 0) {
				velocity_.y = -8.f;	// limiting Jump speed, slowing it to X amount
			}
			isFreeFalling = true;
		}

		if (velocity_.y <= kMaxJumpSpeed) {
			isMaxSpeed = true;
		}
		if (!isPressingSpace || isMaxSpeed || isFreeFalling) {
			// Fall speed
			velocity_.y += kFreeFallAcceleration;
			velocity_.y = (std::min)(velocity_.y, kMaxFallSpeed);
		}
	}
	pos_ += velocity_;
}

void Player::OnCollision()
{
	hp--;
	//isDead = true;
}

void Player::Audio()
{
	if (isPressingSpace && onGround)
	{
		if (Novice::IsPlayingAudio(jumpPlayHandle) == 0 || jumpPlayHandle == -1) {

			jumpPlayHandle = Novice::PlayAudio(jumpAudioHandle, 0, kJumpAudioVolume);

		}
	}
}

void Player::Shakeing()
{
	shake_->ActivateShake(10, 60);
}

void Player::CollisionWithBlock(BlockNotDestroyable* nonDesBlock)
{

#pragma region beforeGPT

	//if (!onGround) {
	//	isOnTopOfBlock = false;
	//}

	//if (velocity_.y < 0) {
	//	return;
	//}
	//// when playing is falling
	//if (velocity_.y > 0 &&
	//	nonDesBlock->GetPos().y - pos_.y + size.height + velocity_.y <= 5.f) {	// when player.bottom is below block.top
	//	// when player is within block size
	//	if (pos_.x <= nonDesBlock->GetPos().x + nonDesBlock->GetSize().width || pos_.x + size.width >= nonDesBlock->GetPos().x) {
	//		isOnTopOfBlock = true;
	//		pos_.y = nonDesBlock->GetPos().y - size.height;
	//		onGround = true;
	//		velocity_.x *= (1.0f - kAttenuation);
	//	}
	//}
	//if (isOnTopOfBlock) {
	//	velocity_.y = 0.0f; // reseting fall speed
	//	onGround = true;
	//	InitializeFlag();
	//}

#pragma endregion

	float playerBottom = pos_.y + size.height + velocity_.y;
	float playerTop = pos_.y;
	float playerRightPos = pos_.x + size.width;
	float blockTop = nonDesBlock->GetPos().y;
	float blockBottom = nonDesBlock->GetPos().y + nonDesBlock->GetSize().height;
	float leftPosBlock = nonDesBlock->GetPos().x;
	float rightPosBlock = nonDesBlock->GetPos().x + nonDesBlock->GetSize().width;
	if (velocity_.y < 0) {
		return;
	}

	bool isWithinHorizontalBounds = (pos_.x < rightPosBlock) && (playerRightPos > leftPosBlock);
	bool isCloseEnoughVertically = (blockTop - playerBottom <= 1.f);
	bool isPlayerBelowBlock = (playerTop >= blockBottom);

	if (velocity_.y > 0) {
		if (isWithinHorizontalBounds && isCloseEnoughVertically && !isPlayerBelowBlock) {
			pos_.y = blockTop - size.height;
			velocity_.y = 0;
			isOnTopOfBlock = true;
			onGround = true;
			InitializeFlag();
		}
		else {
			isOnTopOfBlock = false;
			onGround = false;
		}
	}


	if (!isWithinHorizontalBounds || isPlayerBelowBlock) {
		isOnTopOfBlock = false;
		onGround = false;
	}


	if (isOnTopOfBlock) {
		velocity_.y = 0.0f;
		onGround = true;
	}
	else {

		velocity_.y += kFreeFallAcceleration;
		velocity_.y = min(velocity_.y, kMaxFallSpeed);
	}
}

void Player::SwitchToAirborne(BlockNotDestroyable* nonDesBlock)
{
	(void)(nonDesBlock);
	if (!isCloseEnoughToBlock && !isWithinBlockWidth) {
		onGround = false;
	}
}

Vector2 Player::CameraOffset()
{
	Vector2 offset{};
	/*prevPos_ = pos_;

	pos_ += velocity_;
	offset = pos_ - prevPos_;*/

	return offset;
}

const Object Player::GetObject_() const
{
	Object result{};
	result.pos = pos_;
	result.size = size;
	return result;
}