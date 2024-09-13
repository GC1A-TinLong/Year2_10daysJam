#include "LastStage.h"

LastStage::~LastStage()
{
	delete background_;
	delete fade_;
	delete UI;

	delete player_;
	for (auto* spike : spike_) { delete spike; }
	spike_.clear();

	for (auto* blocks : blocks_) { delete blocks; }
	blocks_.clear();
	for (auto* leftBlocks : leftWallBlocks_) { delete leftBlocks; }
	leftWallBlocks_.clear();
	for (auto* rightBlocks : rightWallBlocks_) { delete rightBlocks; }
	rightWallBlocks_.clear();

	delete depthMeter_;
	delete goal_;
}

void LastStage::Initialize()
{
#pragma region Fade
	phase_ = Phase::kFadeIn;
	fade_ = new Fade();
	fade_->Initialize();
	fade_->Start(Status::FadeIn, duration_);
#pragma endregion

#pragma region Background
	background_ = new Background();
	background_->Initialize(backgroundHandle_);
#pragma endregion
	// UI
	UI = new UserInterface;
	UI->Initialize(1);
	// Goal
	goal_ = new Goal;
	goal_->Initialize(goalPos_);

#pragma region Depth Meter
	depthMeter_ = new DepthMeter;
	depthMeter_->Initialize((int)goalPos_.y);
#pragma endregion

	// Player
	player_ = new Player;
	player_->Initialize({ 640.f,350.f });

	// Spike
	spike_.resize(kSpikeNum);
	for (int i = 0; i < kSpikeNum; i++)
	{
		spike_[i] = new Spike;
		float initPosX = 192.f;
		spike_[i]->Initialize({ initPosX + i * 48,96 });
	}

	blocks_.resize(kBlockNum);
	for (int y = 0; y < mapCountY; y++) {
		for (int x = 0; x < mapCountX; x++) {
			if (map[y][x] == (int)BlockType::None) { continue; }

			if (map[y][x] == (int)BlockType::Block)
			{
				blocks_[blockIndex] = new BlockDestroyable;
				Vector2 blockPos_ = { x * kSpriteSize + adjustPosForMapchipX, y * kSpriteSize + adjustPosForMapchipY };
				blocks_[blockIndex]->Initialize(blockPos_);
				blockIndex++; // Move to the next block
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

void LastStage::Update()
{
	ChangePhase();

	switch (phase_)
	{
	case Phase::kFadeIn:
		fade_->Update();
		SetPlayerStatus();
		UI->Update(true, false);
		break;
#pragma region Play
	case Phase::kPlay:

		background_->Update(scrollSpeed);
		// Depth meter
		UserInterfaceDepthMeter();
		depthMeter_->Update(scrollSpeed);

		// Player
		SetPlayerStatus();

		player_->Update(scrollSpeed, false, goal_->GetPos().y);
		SetPlayerStatus();
		player_->CollisionWithDestroyableBlock(blocks_);
		if (goal_->GetStopMoving())
		{
			scrollSpeed = 0.f;
			for (auto* spike : spike_) {
				spike->SetIsStart(true);
			}
		}
		player_->Drilling();

		// Spike
		for (auto* spike : spike_) {
			spike->Update();
		}

		//Blocks
		for (auto* blocks : blocks_) { blocks->Update(scrollSpeed); }
		// WallBlocks
		for (auto* wallblock : leftWallBlocks_) { wallblock->Update(scrollSpeed); }
		for (auto* wallblock : rightWallBlocks_) { wallblock->Update(scrollSpeed); }

		UI->Update(true, false);

		goal_->Update(scrollSpeed);

		DeleteBlocks();
		CheckAllCollision();

		break;
#pragma endregion

#pragma region Countdown
	case Phase::kCountdown:
		UI->Countdown();
		break;
#pragma endregion

#pragma region kDeath
	case Phase::kDeath:
		SetPlayerStatus();

		player_->Update(scrollSpeed, false, goal_->GetPos().y);
		player_->DeathAnimation();
		background_->Update(scrollSpeed);
		CheckAllCollision();
		break;
#pragma endregion

#pragma region kStageClear
	case Phase::kStageClear:

		scrollSpeed = 0.f;
		background_->Update(scrollSpeed);

		UserInterfaceDepthMeter();
		depthMeter_->Update(scrollSpeed);

		// Player
		SetPlayerStatus();

		player_->Update(scrollSpeed, false, goal_->GetPos().y);
		SetPlayerStatus();
		player_->CollisionWithDestroyableBlock(blocks_);
		player_->Drilling();

		CheckAllCollision();
		goal_->Update(scrollSpeed);

		// Spike
		for (auto* spike : spike_) {
			spike->Update();
			spike->SetIsStart(false);
		}
		//Blocks
		for (auto* blocks : blocks_) { blocks->Update(scrollSpeed); }
		// WallBlocks
		for (auto* wallblock : leftWallBlocks_) { wallblock->Update(scrollSpeed); }
		for (auto* wallblock : rightWallBlocks_) { wallblock->Update(scrollSpeed); }

		UI->Update(true, false);

		DeleteBlocks();
		break;
#pragma endregion

	case Phase::kFadeOut:
		fade_->Update();
		break;
	}
}

void LastStage::Draw()
{// Background
	background_->Draw();

	// Player
	player_->Draw();

	//Blocks
	for (auto* block : blocks_) { block->Draw(); }

	//Wall Blocks
	for (auto* wallblock : leftWallBlocks_) { wallblock->Draw(); }
	for (auto* wallblock : rightWallBlocks_) { wallblock->Draw(); }
	// Spike
	for (auto* spike : spike_) { spike->Draw(); }

	goal_->Draw();

	UI->Draw();

	depthMeter_->Draw();

	switch (phase_)
	{
	case Phase::kFadeIn:
		// Fade
		fade_->Draw();
		break;

	case Phase::kPlay:
		break;
	case Phase::kCountdown:
		break;
	case Phase::kDeath:
		break;
	case Phase::kStageClear:
		break;

	case Phase::kFadeOut:
		fade_->Draw();
		break;
	}
}

void LastStage::ChangePhase()
{
	switch (phase_)
	{
	case Phase::kFadeIn:
		if (fade_->IsFinished() && !UI->GetStartGame())
		{
			phase_ = Phase::kCountdown;
		}
		if (fade_->IsFinished() && UI->GetStartGame())
		{
			phase_ = Phase::kPlay;
		}
		break;

	case Phase::kCountdown:
		if (UI->GetStartGame())
		{
			phase_ = Phase::kPlay;
		}
		break;

	case Phase::kPlay:
		if (Input::GetInstance()->TriggerKey(DIK_C) || isStageCleared && scrollSpeed == 0.f)
		{
			phase_ = Phase::kStageClear;
		}
		if (player_->GetDeathAnimationDone()) { phase_ = Phase::kDeath; }
		break;

	case Phase::kDeath:
		phase_ = Phase::kFadeOut;
		break;
	case Phase::kStageClear:
		if (clearTimer >= 30)
		{
			fade_->Start(Status::FadeOut, duration_);
			phase_ = Phase::kFadeOut;
		}
		break;
	case Phase::kFadeOut:
		if (fade_->IsFinished() && isStageCleared) {
			player_->SetIsDrilling(false);
			sceneNo = STAGESELECT;
		}
		else if (fade_->IsFinished() && player_->GetDeathAnimationDone())
		{
			Initialize();
			UI->SetStartGame(true);
		}
		break;
	}
}

void LastStage::DeleteBlocks()
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
}

void LastStage::CheckAllCollision()
{
#pragma region player & spike collision
	Object playerObj, spikeObj;
	playerObj = player_->GetObject_();
	for (int i = 0; i < kSpikeNum; i++)
	{
		spikeObj = spike_[i]->GetObject_();
		if (isCollideObject(playerObj, spikeObj)) {
			if (!spike_[i]->GetIsStart()) { player_->OnCollision(); }
			else { player_->SetIsDead(true); }

			break;
		}
	}
#pragma endregion

#pragma region player & block collision
	Object playerDrillPointObj = player_->GetDrillPointObject_();	// collision on the drill
	Object blockObj;

	for (int i = 0; i < blocks_.size(); ++i) //reset all blocks to not being touched
	{
		blocks_[i]->SetIsTouched(false);
		blocks_[i]->SetStartShake(false);
	}

	for (int i = 0; i < blocks_.size();)
	{
		blockObj = blocks_[i]->GetObject_();
		if (isCollideObject(playerDrillPointObj, blockObj) && !blocks_[i]->IsDestroyed())
		{
			blocks_[i]->OnCollision(player_);

			if (player_->GetIsDrilling()) //if we're drilling
			{
				blocks_[i]->SetTakenDamage(5); //damage is 5
				blocks_[i]->SetStartShake(true); //shake
			}
			else
			{
				blocks_[i]->SetTakenDamage(0); //damage is 1
				blocks_[i]->SetStartShake(false);
			}

			if (blocks_.empty() || blocks_[i] == nullptr) {
				continue;	// If block was destroyed or blocks_ changed, avoid incrementing "i"
			}
		}
		else
		{
			blocks_[i]->SetIsTouched(false); //not on top of the block anymore
			blocks_[i]->SetStartShake(false);
		}
		++i; // Increment if no collision or block was not removed
	}
#pragma endregion

#pragma region player & goal
	Object goalObj = goal_->GetObject_();

	if (isCollideObject(playerDrillPointObj, goalObj))
	{
		isStageCleared = true;
		goal_->CollisionPlayer(player_);
		//Initialize();
	}
#pragma endregion
}

void LastStage::SetPlayerStatus()
{
	float playerDrillPower = player_->GetDrillPower();
	UI->SetDrillPower(playerDrillPower);

	bool isDrilling = player_->GetIsDrilling();
	UI->SetIsDrilling(isDrilling);

	int playerHP = player_->GetUIHP();
	UI->SetPlayerHP(playerHP);
}

void LastStage::UserInterfaceDepthMeter()
{
	float playerY = player_->GetPos().y + player_->GetSize().height;
	depthMeter_->SetPlayerYPos(playerY);
}
