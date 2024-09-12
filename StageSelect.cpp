#include "StageSelect.h"

StageSelect::~StageSelect()
{
	delete background_;
	delete UI;
	delete fade_;
	delete player_;

	for (BlockNotDestroyable* blocks : blocks_) { delete blocks; }
	blocks_.clear();
	for (auto* leftBlocks : leftWallBlocks_) { delete leftBlocks; }
	leftWallBlocks_.clear();
	for (auto* rightBlocks : rightWallBlocks_) { delete rightBlocks; }
	rightWallBlocks_.clear();
}

void StageSelect::Initialize()
{
	// Fade
	phase_ = Phase::kFadeIn;
	fade_ = new Fade();
	fade_->Initialize();
	fade_->Start(Status::FadeIn, duration_);
	// Background
	background_ = new Background();
	background_->Initialize(backgroundHandle_);
	// UI
	UI = new UserInterface;
	UI->Initialize(1);

	// Player
	player_ = new Player;
	player_->Initialize({ 96.f,72.f });

	blocks_.resize(kBlockNum);
	steelBlocks_.resize(kSteelBlockNum);
	for (int y = 0; y < mapCountY; y++) {
		for (int x = 0; x < mapCountX; x++) {
			if (map[y][x] == (int)BlockType::None || map[y][x] == (int)BlockType::BrokenBlock) { continue; }

			if (map[y][x] == (int)BlockType::Block)
			{
				blocks_[blockIndex] = new BlockNotDestroyable;
				Vector2 blockPos_ = { x * kSpriteSize + adjustPosForMapchipX, y * kSpriteSize + adjustPosForMapchipY };
				blocks_[blockIndex]->Initialize(blockPos_, false, false);
				blockIndex++; // Move to the next block
			}
			else if (map[y][x] == (int)BlockType::SteelBlock)
			{
				Vector2 blockPos_ = { x * kSpriteSize + adjustPosForMapchipX, y * kSpriteSize + adjustPosForMapchipY };
				steelBlocks_[steelIndex] = new BlockSteel;
				steelBlocks_[steelIndex]->Initialize(blockPos_, false);
				steelIndex++; // Move to the next block
			}
		}
	}
	// Wall
	leftWallBlocks_.resize(kWallBlockNum);
	for (int i = 0; i < kWallBlockNum; i++)
	{
		leftWallBlocks_[i] = new BlockSteel;
		leftWallPos_.y = 48.f * i;
		leftWallBlocks_[i]->Initialize(leftWallPos_, true);
	}
	rightWallBlocks_.resize(kWallBlockNum);
	for (int i = 0; i < kWallBlockNum; i++)
	{
		rightWallBlocks_[i] = new BlockSteel;
		rightWallPos_.y = 48.f * i;
		rightWallBlocks_[i]->Initialize(rightWallPos_, true);
	}
}

void StageSelect::Update()
{
	ChangePhase();

	background_->Update(scrollSpeed);
	// WallBlocks
	for (auto* wallblock : leftWallBlocks_) { wallblock->Update(scrollSpeed); }
	for (auto* wallblock : rightWallBlocks_) { wallblock->Update(scrollSpeed); }
	// Normal Blocks
	for (auto* blocks : blocks_) { blocks->Update(scrollSpeed); }
	// Steel Blocks
	for (auto* blocks : steelBlocks_) { blocks->Update(scrollSpeed); }

	SetPlayerStatus();
	UI->Update(true, false);
	switch (phase_)
	{
	case Phase::kFadeIn:
		fade_->Update();
		break;

	case Phase::kPlay:
		// Player
		player_->Update(0.f, true);
		player_->CollisionWithBlock(blocks_);
		Novice::ScreenPrintf(0, 200, "onground %d", player_->IsOnGround());
		if (!player_->IsOnGround()) { player_->CollisionWithMetalBlock(steelBlocks_); }
		player_->Drilling();

		DeleteBlocks();
		CheckAllCollision();
		break;

	case Phase::kFadeOut:
		fade_->Update();
		break;
	}
}

void StageSelect::Draw()
{
	// Background
	background_->Draw();
	//Wall Blocks
	for (auto* wallblock : leftWallBlocks_) { wallblock->Draw(); }
	for (auto* wallblock : rightWallBlocks_) { wallblock->Draw(); }

	// Player
	player_->Draw();
	// Blocks
	for (auto* block : blocks_) { block->Draw(); }
	for (auto* block : steelBlocks_) { block->Draw(); }
	// UI
	UI->Draw();

	switch (phase_)
	{
	case Phase::kFadeIn:
		// Fade
		fade_->Draw();
		break;
	}
}

void StageSelect::ChangePhase()
{
	switch (phase_)
	{
	case Phase::kFadeIn:
		if (fade_->IsFinished()) { phase_ = Phase::kPlay; }
		break;

	case Phase::kPlay:
		if (Input::GetInstance()->TriggerKey(DIK_C)) // DEBUG
		{
			fade_->Start(Status::FadeOut, duration_);
			phase_ = Phase::kFadeOut;
		}
		break;

	case Phase::kFadeOut:
		if (fade_->IsFinished() && !player_->IsDead()) {
			sceneNo = BASIC_TUTORIAL;
		}
		else if (fade_->IsFinished() && player_->IsDead()) {
			Initialize();
		}
		break;
	}
}

void StageSelect::DeleteBlocks()
{
	for (int i = 0; i < blocks_.size();)
	{
		if (blocks_[i]->IsDestroyed() || blocks_[i]->GetIsAboveScreen()) //if block is destroyed
		{
			delete blocks_[i]; //delete block
			blocks_.erase(blocks_.begin() + i); //erase it from the vector
			break;
		}
		else { i++; }
	}
	for (int i = 0; i < steelBlocks_.size();)
	{
		steelBlocks_[i]->Update(scrollSpeed);

		if (steelBlocks_[i]->GetIsAboveScreen())
		{
			delete steelBlocks_[i];
			steelBlocks_.erase(steelBlocks_.begin() + i);
		}
		else { ++i; }
	}
}

void StageSelect::CheckAllCollision()
{
#pragma region player & stage door collision

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
				blocks_[i]->SetTakenDamage(0); //damage is 0
				blocks_[i]->SetStartShake(false);
			}

			if (blocks_.empty() || blocks_[i] == nullptr) {
				continue;	// If block was destroyed or blocks_ changed, avoid incrementing "i"
			}
			//break;
		}
		else
		{
			blocks_[i]->SetIsTouched(false); //not on top of the block anymore
			blocks_[i]->SetStartShake(false);
		}
		++i; // Increment if no collision or block was not removed
	}

#pragma endregion
}

void StageSelect::SetPlayerStatus()
{
	float playerDrillPower = player_->GetDrillPower();
	UI->SetDrillPower(playerDrillPower);

	bool isDrilling = player_->GetIsDrilling();
	UI->SetIsDrilling(isDrilling);

	int playerHP = player_->GetUIHP();
	UI->SetPlayerHP(playerHP);
}
