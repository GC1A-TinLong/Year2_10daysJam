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
}

void Player::Update()
{
	AnimationHolder();
	MovementInput();
}

void Player::Draw()
{
	if (!isDead) {
		//Novice::DrawBox((int)pos_.x, (int)pos_.y, width, height, 0, WHITE, kFillModeSolid);
		//Novice::DrawSprite(pos_.x, pos_.y, texture_, 1.f, 1.f, 0, WHITE);
		Novice::DrawSpriteRect((int)pos_.x, (int)pos_.y, (int)animationPos_.x, (int)animationPos_.y, 42, 72, playerHandleHolder_, 42.f / 504.f, 1.f, 0.0f, WHITE);
	}
	Novice::ScreenPrintf(0, 0, "player.velocity.x = %f", velocity_.x);
	Novice::ScreenPrintf(0, 20, "player.velocity.y = %f", velocity_.y);
	Novice::ScreenPrintf(0, 40, "player.pos.x = %f", pos_.x);
	Novice::ScreenPrintf(0, 60, "player.pos.y = %f", pos_.y);
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
			acceleration.x += kAcceleration;
		}
		else if (Input::GetInstance()->PushKey(DIK_A)) {
			if (direction != LRDirection::left) { // player direction
				direction = LRDirection::left;
			}

			if (velocity_.x > 0.0f) { // when pushing opposing input, attenuate velocity
				velocity_.x *= (1.0f - kAttenuation);
			}
			acceleration.x -= kAcceleration;
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
		// is falling? Collision with ground
		//if (velocity_.y > 0.0f) {
		//	// if translation Y is lower than the ground, landed
		//	if (pos_.y + velocity_.y >= 400.0f) {
		//		pos_.y = 400.0f; // prevent going underground
		//		isLand = true;
		//	}
		//}

		//if (isLand) {
		//	velocity_.x *= (1.0f - kAttenuation);
		//	velocity_.y = 0.0f; // reseting fall speed
		//	onGround = true;
		//	InitializeFlag();
		//}
	}
	pos_ += velocity_;
}

void Player::AnimationHolder()
{
	animationTimer_++;

	playerHandleHolder_ = playerIdleHandle_;
	if (animationTimer_ >= 4) 
	{
		animationPos_.x += 42;
		animationTimer_ = 0;
	}
	

	if (animationPos_.x >= 504) 
	{
		animationPos_.x = 0;
	}
}

void Player::OnCollision()
{
	isDead = true;
}

void Player::CollisionWithBlock(BlockNotDestroyable* nonDesBlock)
{
	isOnTopOfBlock = false;

	if (velocity_.y < 0) {
		return;
	}
	// when playing is falling
	// when player.bottom is below block.top
	if (velocity_.y > 0 &&
		(pos_.y + size.height + velocity_.y >= nonDesBlock->GetPos().y)) {	
		// when player is within block size
		if (pos_.x <= nonDesBlock->GetPos().x + nonDesBlock->GetSize().width || pos_.x + size.width >= nonDesBlock->GetPos().x) {
			isOnTopOfBlock = true;
			pos_.y = nonDesBlock->GetPos().y - size.height;
			onGround = true;
		}
	}
	if (isOnTopOfBlock) {
		velocity_.x *= (1.0f - kAttenuation);
		velocity_.y = 0.0f; // reseting fall speed
		onGround = true;
		InitializeFlag();
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