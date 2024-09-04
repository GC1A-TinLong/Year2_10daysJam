#include "StageScene.h"

StageScene::~StageScene()
{
	delete player_;
	delete fade_;
	
	for (Spike* spike : spike_) 
	{
		delete spike;
	}
	spike_.clear();

	for (BlockDestroyable* blocks : destroyableBlocks_) 
	{
		delete blocks;
	}
	destroyableBlocks_.clear();

	for (BlockNotDestroyable* blocks : blocks_) 
	{
		delete blocks;
	}
	blocks_.clear();

	for (BlockNotDestroyable* leftBlocks : leftWallBlocks_)
	{
		delete leftBlocks;
	}
	leftWallBlocks_.clear();

	for (BlockNotDestroyable* rightBlocks : rightWallBlocks_)
	{
		delete rightBlocks;
	}
	rightWallBlocks_.clear();
}

void StageScene::Initialize()
{
	// Player
	player_ = new Player;
	player_->Initialize({ 640,400 });

	// Spike
	spike_.resize(kSpikeNum);
	for (int i = 0; i < kSpikeNum; i++)
	{
		spike_[i] = new Spike;
		int initPosX = 300;
		spike_[i]->Initialize({ initPosX + i * 48,0 });
	}

#pragma region Destroyable Blocks

	destroyableBlocks_.resize(kDestroyableBlockNum);
	for (int i = 0; i < kDestroyableBlockNum; i++)
	{
		destroyableBlocks_[i] = new BlockDestroyable;
		Vector2Int desBlockPos = desBlockPos_[i];
		destroyableBlocks_[i]->Initialize(desBlockPos);
	}

#pragma endregion


#pragma region Blocks

	blocks_.resize(kBlockNum);
	for (int i = 0; i < kBlockNum; i++)
	{	
		blocks_[i] = new BlockNotDestroyable;
		Vector2Int blockPos = BlockPos_[i];
		blocks_[i]->Initialize(BlockPos_[i], isMoss[i], false);
	}
#pragma endregion

#pragma region LeftWall

	leftWallBlocks_.resize(kWallBlockNum);
	for (int i = 0; i < kWallBlockNum; i++)
	{
		leftWallBlocks_[i] = new BlockNotDestroyable;
		Vector2Int leftWallPos_ = { 0,0 };
		leftWallBlocks_[i]->Initialize({ leftWallPos_.x, leftWallPos_.y + 48 * i  }, false, true);
	}

#pragma endregion

#pragma region RightWall

	rightWallBlocks_.resize(kWallBlockNum);
	for (int i = 0; i < kWallBlockNum; i++)
	{
		rightWallBlocks_[i] = new BlockNotDestroyable;
		Vector2Int rightWallPos_ = { 1232,0 };
		rightWallBlocks_[i]->Initialize({ rightWallPos_.x, rightWallPos_.y + 48 * i }, false, true);
	}

#pragma endregion

#pragma region Fade

	phase_ = Phase::kFadeIn;
	fade_ = new Fade();
	fade_->Initialize();
	fade_->Start(Status::FadeIn, duration_);

#pragma endregion

}

void StageScene::Update()
{
	ChangePhase();
	switch (phase_)
	{
	case StageScene::Phase::kFadeIn:
		fade_->Update();
		break;

	case StageScene::Phase::kPlay:
		// Player
		player_->Update();

		// Spike
		for (auto* spike : spike_) {
			spike->Update();
		}

		//Destroyable Blocks
		for (auto* destroyableBlock : destroyableBlocks_) 
		{
			destroyableBlock->Update();
		}

		//Blocks
		for (auto* block : blocks_) 
		{
			block->Update();
		}

		//WallBlocks
		for (auto* wallblock : leftWallBlocks_) 
		{
			wallblock->Update();
		}

		for (auto* wallblock : rightWallBlocks_)
		{
			wallblock->Update();
		}
		
		break;
	case StageScene::Phase::kDeath:
		break;
	case StageScene::Phase::kStageClear:
		break;

	case StageScene::Phase::kFadeOut:
		fade_->Update();
		break;
	}

	
}

void StageScene::ChangePhase()
{
	switch (phase_)
	{
	case StageScene::Phase::kFadeIn:
		if (fade_->IsFinished())
		{
			phase_ = Phase::kPlay;
		}
		break;

	case StageScene::Phase::kPlay:
		if (Input::GetInstance()->TriggerKey(DIK_SPACE))
		{
			fade_->Start(Status::FadeOut, duration_);
			phase_ = Phase::kFadeOut;
		}
		break;

	case StageScene::Phase::kDeath:
		break;
	case StageScene::Phase::kStageClear:
		break;
	case StageScene::Phase::kFadeOut:
		if (fade_->IsFinished()) {
			sceneNo = CLEAR;
		}
		break;
	}
}

void StageScene::Draw()
{
	switch (phase_)
	{
	case StageScene::Phase::kFadeIn:
		// Player
		player_->Draw();
		// Fade
		fade_->Draw();
		break;
	case StageScene::Phase::kPlay:
		// Player
		player_->Draw();

		//Destroyable Blocks
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


		// Spike
		for (auto* spike : spike_) {
			spike->Draw();
		}

		break;
	case StageScene::Phase::kDeath:
		break;
	case StageScene::Phase::kStageClear:
		break;

	case StageScene::Phase::kFadeOut:
		fade_->Draw();
		break;
	}
	
}

void StageScene::CheckAllCollision()
{
#pragma region player & spike collision
	/*for (int i = 0; i < kSpikeNum; i++)
	{
		if(isCollideBox()
	}*/

#pragma endregion

#pragma region player & item collision

#pragma endregion
}
