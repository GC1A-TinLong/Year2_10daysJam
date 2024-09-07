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

	delete background_;
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
		float initPosX = 192.f;
		spike_[i]->Initialize({ initPosX + i * 48,96 });
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

#pragma region Background

	background_ = new Background();
	background_->Initialize();

#pragma endregion
}

void StageScene::Update()
{
	ChangePhase();

	switch (phase_)
	{
	case StageScene::Phase::kFadeIn:
		background_->Update();
		fade_->Update();
		break;

	case StageScene::Phase::kPlay:
		background_->Update();

		// Player
		player_->Update();
		player_->CollisionWithBlock(blocks_);

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
		DeleteBlocks();
		CheckAllCollision();

		break;
	case StageScene::Phase::kDeath:
		background_->Update();

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

		break;
	case StageScene::Phase::kStageClear:
		background_->Update();
		break;

	case StageScene::Phase::kFadeOut:
		background_->Update();
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
		if (player_->IsDead()) 
		{
			phase_ = Phase::kDeath;
		}
		break;

	case StageScene::Phase::kDeath:
			phase_ = Phase::kFadeOut;
		break;
	case StageScene::Phase::kStageClear:
		break;
	case StageScene::Phase::kFadeOut:
		if (fade_->IsFinished() && !player_->IsDead()) {
			sceneNo = CLEAR;
		} 
		else if (fade_->IsFinished() && player_->IsDead()) 
		{
			Initialize();
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
		background_->Draw();
		
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

		//UI
		Novice::DrawBox(0, 0, 144, 1080, 0.0f, BLACK, kFillModeSolid);
		Novice::DrawBox(0, 1032, 1440, 1032, 0.0f, BLACK, kFillModeSolid);
		Novice::DrawBox(0, 0, 1440, 96, 0.0f, BLACK, kFillModeSolid);
		Novice::DrawBox(1440, 0, 1920, 1080, 0.0f, BLACK, kFillModeSolid);

		//UI TEXT
		Novice::DrawSprite(200, 10, stageTextHandle, 1.0f, 1.0f, 0.0f, WHITE); //TEXT
		Novice::DrawSprite(420, 5, stage1Handle, 1.0f, 1.0f, 0.0f, WHITE); //1
		Novice::DrawSprite(1520, 200, controlsHandle, 1.0f, 1.0f, 0.0f, WHITE); //CONROLS
		Novice::DrawSprite(1520, 350, letterDHandle, 1.0f, 1.0f, 0.0f, WHITE); //D
		Novice::DrawSprite(1520, 450, letterAHandle, 1.0f, 1.0f, 0.0f, WHITE); //A
		Novice::DrawSprite(1620, 350, rightPlayer, 1.0f, 1.0f, 0.0f, WHITE); //Player Right
		Novice::DrawSprite(1620, 450, leftPlayer, 1.0f, 1.0f, 0.0f, WHITE); //Player Left
		Novice::DrawSprite(1520, 550, spaceHandle, 1.0f, 1.0f, 0.0f, WHITE); //SPACE

		fade_->Draw();

		break;
	case StageScene::Phase::kPlay:
		// Player
		background_->Draw();

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

		//UI
		Novice::DrawBox(0, 0, 144, 1080, 0.0f, BLACK, kFillModeSolid);
		Novice::DrawBox(0, 1032, 1440, 1032, 0.0f, BLACK, kFillModeSolid);
		Novice::DrawBox(0, 0, 1440, 96, 0.0f, BLACK, kFillModeSolid);
		Novice::DrawBox(1440, 0, 1920, 1080, 0.0f, BLACK, kFillModeSolid);

		//UI TEXT
		Novice::DrawSprite(200, 10, stageTextHandle, 1.0f, 1.0f, 0.0f, WHITE); //TEXT
		Novice::DrawSprite(420, 5, stage1Handle, 1.0f, 1.0f, 0.0f, WHITE); //1
		Novice::DrawSprite(1520, 200, controlsHandle, 1.0f, 1.0f, 0.0f, WHITE); //CONROLS
		Novice::DrawSprite(1520, 350, letterDHandle, 1.0f, 1.0f, 0.0f, WHITE); //D
		Novice::DrawSprite(1520, 450, letterAHandle, 1.0f, 1.0f, 0.0f, WHITE); //A
		Novice::DrawSprite(1620, 350, rightPlayer, 1.0f, 1.0f, 0.0f, WHITE); //Player Right
		Novice::DrawSprite(1620, 450, leftPlayer, 1.0f, 1.0f, 0.0f, WHITE); //Player Left
		Novice::DrawSprite(1520, 550, spaceHandle, 1.0f, 1.0f, 0.0f, WHITE); //SPACE

		break;
	case StageScene::Phase::kDeath:

		background_->Draw();

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

		//UI
		Novice::DrawBox(0, 0, 144, 1080, 0.0f, BLACK, kFillModeSolid);
		Novice::DrawBox(0, 1032, 1440, 1032, 0.0f, BLACK, kFillModeSolid);
		Novice::DrawBox(0, 0, 1440, 96, 0.0f, BLACK, kFillModeSolid);
		Novice::DrawBox(1440, 0, 1920, 1080, 0.0f, BLACK, kFillModeSolid);

		//UI TEXT
		Novice::DrawSprite(200, 10, stageTextHandle, 1.0f, 1.0f, 0.0f, WHITE); //TEXT
		Novice::DrawSprite(420, 5, stage1Handle, 1.0f, 1.0f, 0.0f, WHITE); //1
		Novice::DrawSprite(1520, 200, controlsHandle, 1.0f, 1.0f, 0.0f, WHITE); //CONROLS
		Novice::DrawSprite(1520, 350, letterDHandle, 1.0f, 1.0f, 0.0f, WHITE); //D
		Novice::DrawSprite(1520, 450, letterAHandle, 1.0f, 1.0f, 0.0f, WHITE); //A
		Novice::DrawSprite(1620, 350, rightPlayer, 1.0f, 1.0f, 0.0f, WHITE); //Player Right
		Novice::DrawSprite(1620, 450, leftPlayer, 1.0f, 1.0f, 0.0f, WHITE); //Player Left
		Novice::DrawSprite(1520, 550, spaceHandle, 1.0f, 1.0f, 0.0f, WHITE); //SPACE


		break;
	case StageScene::Phase::kStageClear:

		background_->Draw();

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

		//UI
		Novice::DrawBox(0, 0, 144, 1080, 0.0f, BLACK, kFillModeSolid);
		Novice::DrawBox(0, 1032, 1440, 1032, 0.0f, BLACK, kFillModeSolid);
		Novice::DrawBox(0, 0, 1440, 96, 0.0f, BLACK, kFillModeSolid);
		Novice::DrawBox(1440, 0, 1920, 1080, 0.0f, BLACK, kFillModeSolid);

		//UI TEXT
		Novice::DrawSprite(200, 10, stageTextHandle, 1.0f, 1.0f, 0.0f, WHITE); //TEXT
		Novice::DrawSprite(420, 5, stage1Handle, 1.0f, 1.0f, 0.0f, WHITE); //1
		Novice::DrawSprite(1520, 200, controlsHandle, 1.0f, 1.0f, 0.0f, WHITE); //CONROLS
		Novice::DrawSprite(1520, 350, letterDHandle, 1.0f, 1.0f, 0.0f, WHITE); //D
		Novice::DrawSprite(1520, 450, letterAHandle, 1.0f, 1.0f, 0.0f, WHITE); //A
		Novice::DrawSprite(1620, 350, rightPlayer, 1.0f, 1.0f, 0.0f, WHITE); //Player Right
		Novice::DrawSprite(1620, 450, leftPlayer, 1.0f, 1.0f, 0.0f, WHITE); //Player Left
		Novice::DrawSprite(1520, 550, spaceHandle, 1.0f, 1.0f, 0.0f, WHITE); //SPACE
		break;

	case StageScene::Phase::kFadeOut:

		background_->Draw();

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

		//UI
		Novice::DrawBox(0, 0, 144, 1080, 0.0f, BLACK, kFillModeSolid);
		Novice::DrawBox(0, 1032, 1440, 1032, 0.0f, BLACK, kFillModeSolid);
		Novice::DrawBox(0, 0, 1440, 96, 0.0f, BLACK, kFillModeSolid);
		Novice::DrawBox(1440, 0, 1920, 1080, 0.0f, BLACK, kFillModeSolid);

		//UI TEXT
		Novice::DrawSprite(200, 10, stageTextHandle, 1.0f, 1.0f, 0.0f, WHITE); //TEXT
		Novice::DrawSprite(420, 5, stage1Handle, 1.0f, 1.0f, 0.0f, WHITE); //1
		Novice::DrawSprite(1520, 200, controlsHandle, 1.0f, 1.0f, 0.0f, WHITE); //CONROLS
		Novice::DrawSprite(1520, 350, letterDHandle, 1.0f, 1.0f, 0.0f, WHITE); //D
		Novice::DrawSprite(1520, 450, letterAHandle, 1.0f, 1.0f, 0.0f, WHITE); //A
		Novice::DrawSprite(1620, 350, rightPlayer, 1.0f, 1.0f, 0.0f, WHITE); //Player Right
		Novice::DrawSprite(1620, 450, leftPlayer, 1.0f, 1.0f, 0.0f, WHITE); //Player Left
		Novice::DrawSprite(1520, 550, spaceHandle, 1.0f, 1.0f, 0.0f, WHITE); //SPACE
		fade_->Draw();
		break;
	}

}

void StageScene::DeleteBlocks()
{
	for (int i = 0; i < blocks_.size();)
	{
		if (blocks_[i]->IsDestroyed()) //if block is destroyed
		{
			delete blocks_[i]; //delete block
			blocks_.erase(blocks_.begin() + i); //erase it from the vector
			break;
		}
		else 
		{
			i++;
		}
		
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

#pragma region player & block collision
	Object obj3 = player_->GetDrillPointObject_();	// collision on the drill
	Object obj4;

	for (int i = 0; i < blocks_.size(); ++i) //reset all blocks to not being touched
	{
		blocks_[i]->SetIsTouched(false);
		blocks_[i]->SetStartShake(false);
	}

	for (int i = 0; i < blocks_.size();)
	{
		obj4 = blocks_[i]->GetObject_();
		if (isCollideObject(obj3, obj4) && !blocks_[i]->IsDestroyed())
		{
			blocks_[i]->OnCollision(player_);

			if (player_->GetIsDrilling()) //if we're drilling
			{
				blocks_[i]->SetTakenDamage(5); //damage is 5
				blocks_[i]->SetStartShake(true); //shake
				
			}
			else 
			{
				blocks_[i]->SetTakenDamage(1); //damage is 1
				blocks_[i]->SetStartShake(false); 

			}

			if (blocks_.empty() || blocks_[i] == nullptr) {
				continue;	// If block was destroyed or blocks_ changed, avoid incrementing "i"
			}
			break;
		}
		else 
		{
			blocks_[i]->SetIsTouched(false); //not on top of the block anymore
			blocks_[i]->SetStartShake(false);

		}
		++i; // Increment if no collision or block was not removed
	}



#pragma region player & item collision

#pragma endregion
}
