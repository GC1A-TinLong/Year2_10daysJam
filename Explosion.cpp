#include "Explosion.h"
#include "Novice.h"

Explosion::~Explosion()
{
}

void Explosion::Initialize(Vector2 pos)
{
	pos_ = pos;
	texture_ = Novice::LoadTexture("./Resources/Explosion/Bomb.png");
	audioHandle = Novice::LoadAudio("./Resources/Audio/explodingBlock.mp3");
}

void Explosion::Update()
{
	if (isExploding_) //This is set in gamescene
	{
		if (Novice::IsPlayingAudio(playHandle) == 0 || playHandle == -1) {
			playHandle = Novice::PlayAudio(audioHandle, 0, kAudioVolume);
		}
		animationTimer_++;

		if (animationPos_.x >= animationFrames - size_.width && animationTimer_ >= 2)
		{
			animationPos_.x = 0;
			animationTimer_ = 0;
			isExploding_ = false;
		}

		if (animationTimer_ >= 2)
		{
			animationPos_.x += size_.width;
			animationTimer_ = 0;
		}
	}
	else 
	{
		animationPos_.x = 0;
		animationTimer_ = 0;
	}
}

void Explosion::Audio()
{

}

void Explosion::Draw()
{
	if (isExploding_) 
	{
		Novice::DrawSpriteRect((int)(pos_.x) - 24, (int)pos_.y - 24, (int)animationPos_.x, (int)animationPos_.y, size_.width, size_.height, texture_,
			(size_.width / animationFrames) * 2.f, 2.f, 0.0f, WHITE);
	}
}
