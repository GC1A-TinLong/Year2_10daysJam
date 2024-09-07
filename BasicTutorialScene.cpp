#include "BasicTutorialScene.h"

BasicTutorialScene::~BasicTutorialScene()
{
	delete player_;
	delete fade_;
}

void BasicTutorialScene::Initialize()
{
#pragma region Fade

	phase_ = Phase::kFadeIn;
	fade_ = new Fade();
	fade_->Initialize();
	fade_->Start(Status::FadeIn, duration_);

#pragma endregion

	// Player
	player_ = new Player;

	// Normal Block
	for (int i = 0; i < kBlockNum; i++) {
		blocks_[i] = new BlockNotDestroyable;
		blockPos_[i] = { kBlockSize * i,500 };
		blocks_[i]->Initialize(blockPos_[i], false, false);
	}
#pragma region LeftWall

	leftWallBlocks_.resize(kWallBlockNum);
	for (int i = 0; i < kWallBlockNum; i++)
	{
		leftWallBlocks_[i] = new BlockNotDestroyable;
		leftWallPos_.y = 48.f * i;
		leftWallBlocks_[i]->Initialize(leftWallPos_, false, true);
	}

#pragma endregion
#pragma region RightWall

	rightWallBlocks_.resize(kWallBlockNum);
	for (int i = 0; i < kWallBlockNum; i++)
	{
		rightWallBlocks_[i] = new BlockNotDestroyable;
		rightWallPos_.y = 48.f * i;
		rightWallBlocks_[i]->Initialize(rightWallPos_, false, true);
	}

#pragma endregion
}

void BasicTutorialScene::Update()
{
}

void BasicTutorialScene::Draw()
{
}

void BasicTutorialScene::CheckAllCollision()
{
}
