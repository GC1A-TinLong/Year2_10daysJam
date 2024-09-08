#include "BasicTutorialScene.h"

BasicTutorialScene::~BasicTutorialScene()
{
	delete background_;
	delete fade_;
	delete player_;
	delete UI;
}

void BasicTutorialScene::Initialize()
{
#pragma region Fade

	phase_ = Phase::kFadeIn;
	fade_ = new Fade();
	fade_->Initialize();
	fade_->Start(Status::FadeIn, duration_);

#pragma endregion

	// Background
	background_ = new Background;
	UI = new UserInterface;
	// Player
	player_ = new Player;

	// Normal Block
	blocks_.resize(kBlockNum);
	blockPos_.resize(kBlockNum);
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
	fade_->Update();

	if (Input::GetInstance()->TriggerKey(DIK_C)) {
		sceneNo = STAGE;
	}
}

void BasicTutorialScene::Draw()
{
	// Background
	background_->Draw();

	// Player
	player_->Draw();

	switch (phase_)
	{
	case BasicTutorialScene::Phase::kFadeIn:
		// Fade
		fade_->Draw();

		// Destroyable Blocks
		for (auto* destroyableBlock : destroyableBlocks_)
		{
			destroyableBlock->Draw();
		}

		//Blocks
		for (auto* block : blocks_)
		{
			block->Draw();
		}

		//Wall Blocks
		for (auto* wallblock : leftWallBlocks_)
		{
			wallblock->Draw();
		}

		for (auto* wallblock : rightWallBlocks_)
		{
			wallblock->Draw();
		}

		UI->Draw();

		break;
	case BasicTutorialScene::Phase::kPlay:
		break;
	}
}

void BasicTutorialScene::CheckAllCollision()
{
}
