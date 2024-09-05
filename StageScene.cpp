#include "StageScene.h"

StageScene::~StageScene()
{
	delete player_;
	delete fade_;
	for (auto* spike : spike_) {
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
	player_->Initialize({ 640.f,400.f });

	// Spike
	spike_.resize(kSpikeNum);
	for (int i = 0; i < kSpikeNum; i++)
	{
		spike_[i] = new Spike;
		float initPosX = 300.f;
		spike_[i]->Initialize({ initPosX + i * 48,48 });
	}

#pragma region Destroyable Blocks

	destroyableBlocks_.resize(kDestroyableBlockNum);
	for (int i = 0; i < kDestroyableBlockNum; i++)
	{
		destroyableBlocks_[i] = new BlockDestroyable;
		Vector2 desBlockPos = desBlockPos_[i];
		destroyableBlocks_[i]->Initialize(desBlockPos);
	}

#pragma endregion

#pragma region Blocks

	blocks_.resize(kBlockNum);
	for (int i = 0; i < kBlockNum; i++)
	{
		blocks_[i] = new BlockNotDestroyable;
		//Vector2 blockPos = BlockPos_[i];
		blocks_[i]->Initialize(BlockPos_[i], isMoss[i], false);
	}
#pragma endregion

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
		for (auto* nonDesBlock : blocks_) {
			player_->CollisionWithBlock(nonDesBlock);

			Novice::ScreenPrintf(300, 0, "block.pos.x = %f", nonDesBlock->GetPos().x);
			Novice::ScreenPrintf(300, 20, "block.pos.y = %f", nonDesBlock->GetPos().y);
		}

		// Spike
		for (auto* spike : spike_) {
			spike->Update();
		}

		//Destroyable Blocks
		for (int i = 0; i < destroyableBlocks_.size();)
		{
			destroyableBlocks_[i]->Update();

			if (destroyableBlocks_[i]->GetIsAboveScreen())
			{
				delete destroyableBlocks_[i];
				destroyableBlocks_.erase(destroyableBlocks_.begin() + i);
			}
			else
			{
				++i;
			}
		}

		//Blocks
		for (int i = 0; i < blocks_.size();)
		{
			blocks_[i]->Update();

			if (blocks_[i]->GetIsAboveScreen())
			{
				delete blocks_[i];
				blocks_.erase(blocks_.begin() + i);
			}
			else
			{
				++i;
			}
		}

		// WallBlocks
		for (auto* wallblock : leftWallBlocks_)
		{
			wallblock->Update();
		}

		for (auto* wallblock : rightWallBlocks_)
		{
			wallblock->Update();
		}

		CheckAllCollision();

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
		if (Input::GetInstance()->TriggerKey(DIK_C))
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
		// Fade
		fade_->Draw();
		// Player
		player_->Draw();
		// Spike
		for (auto* spike : spike_) {
			spike->Draw();
		}
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
		Novice::DrawBox(0, 0, 144, 1080, 0.0f, BLACK, kFillModeSolid);
		Novice::DrawBox(0, 1032, 1440, 1032, 0.0f, BLACK, kFillModeSolid);
		Novice::DrawBox(0, 0, 1440, 96, 0.0f, BLACK, kFillModeSolid);
		Novice::DrawBox(1440, 0, 1920, 1080, 0.0f, BLACK, kFillModeSolid);

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
	Object obj1, obj2;
	obj1 = player_->GetObject_();
	for (int i = 0; i < kSpikeNum; i++)
	{
		obj2 = spike_[i]->GetObject_();
		if (isCollideObject(obj1, obj2)) {
			player_->OnCollision();
			break;
		}
	}

#pragma endregion

#pragma region player & item collision

#pragma endregion
}
