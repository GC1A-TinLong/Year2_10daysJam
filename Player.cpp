#include "Player.h"
#include "Novice.h"
#include "Input.h"

void Player::Initialize(const Vector2& pos)
{
	pos_ = pos;
	//texture_ = texture;
}

void Player::Update()
{
	MovementInput();
}

void Player::Draw()
{
	Novice::DrawBox((int)pos_.x, (int)pos_.y, width, height, 0, WHITE, kFillModeSolid);
	//Novice::DrawSprite(pos_.x, pos_.y, texture_, 1.f, 1.f, 0, WHITE);

	Novice::ScreenPrintf(0, 0, "player.velocity.x = %f", velocity_.x);
	Novice::ScreenPrintf(0, 20, "player.velocity.y = %f", velocity_.y);
}

void Player::MovementInput()
{
	// LR Movement
	if (Input::GetInstance()->PushKey(DIK_D) || Input::GetInstance()->PushKey(DIK_A)) {
		Vector3 acceleration = {};
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
	pos_ += velocity_;
}

void Player::OnCollision()
{
	isDead = true;
}
