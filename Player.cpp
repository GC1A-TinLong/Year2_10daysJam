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

void Player::Update()
{
	Audio();
	AnimationHolder();
	MovementInput();
}

void Player::Draw()
{
	if (!isDead) {
		Novice::DrawSpriteRect((int)pos_.x, (int)pos_.y, (int)animationPos_.x, (int)animationPos_.y, 42, 72, playerHandleHolder_, 42.f / currentAnimationFrames, 1.f, 0.0f, WHITE);
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
		if (fabsf(velocity_.x) < 0.1f) {
			velocity_.x = 0;
		}
	}
	// Jump
	//bool isLand = false;
	if (onGround) {
		if (Input::GetInstance()->TriggerKey(DIK_SPACE)) {
			velocity_.y -= kInitJumpAcceleration;
			isPressingSpace = true;
			prevPos_ = pos_;
		}

		if (prevPos_.y - pos_.y >= kMinInitHeight) {
			onGround = false;
			isPressingSpace = false;
			//isOnTopOfBlock = false;
		}
	}
	else {
		if (Input::GetInstance()->PushKey(DIK_SPACE) && !isMaxSpeed && !isReleasedSpace) {	// if continuously pressing SPACE, add jump force
			if (!isPressingSpace) {
				velocity_.y -= kContinuousJumpAcceleration;
			}
			isPressingSpace = true;
			velocity_.y -= kContinuousJumpAcceleration;
		}
		else if (!Input::GetInstance()->PushKey(DIK_SPACE)) {	// released SPACE key
			isPressingSpace = false;
			isReleasedSpace = true;
			if (!isFreeFalling && velocity_.y < 0) {
				velocity_.y = -8.f;
			}
			isFreeFalling = true;
		}

		if (velocity_.y <= kMaxJumpSpeed) {
			isMaxSpeed = true;
		}
		if (!isPressingSpace || isMaxSpeed) {
			// Fall speed
			velocity_.y += kFreeFallAcceleration;
			velocity_.y = (std::min)(velocity_.y, kMaxFallSpeed);
		}
	}
	pos_ += velocity_;
}

void Player::OnCollision()
{
	isDead = true;
}

void Player::CollisionWithBlock(BlockNotDestroyable* nonDesBlock)
{
	if (!onGround) {
		isOnTopOfBlock = false;
	}

	if (velocity_.y < 0) {
		return;
	}
	// when playing is falling
	if (velocity_.y > 0 &&
		nonDesBlock->GetPos().y - pos_.y + size.height + velocity_.y <= 5.f) {	// when player.bottom is below block.top
		// when player is within block size
		if (pos_.x <= nonDesBlock->GetPos().x + nonDesBlock->GetSize().width || pos_.x + size.width >= nonDesBlock->GetPos().x) {
			isOnTopOfBlock = true;
			pos_.y = nonDesBlock->GetPos().y - size.height;
			onGround = true;
			velocity_.x *= (1.0f - kAttenuation);
		}
	}
	if (isOnTopOfBlock) {
		velocity_.y = 0.0f; // reseting fall speed
		onGround = true;
		InitializeFlag();
	}
}

void Player::SwitchToAirborne(BlockNotDestroyable* nonDesBlock)
{
	(void)(nonDesBlock);
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