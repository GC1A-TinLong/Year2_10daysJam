#include "StageScene.h"

StageScene::~StageScene()
{
	delete background_;
	delete fade_;
	delete UI;

	delete player_;
	for (auto* spike : spike_) { delete spike; }
	spike_.clear();

	for (BlockDestroyable* blocks : destroyableBlocks_) { delete blocks; }
	destroyableBlocks_.clear();

	for (BlockNotDestroyable* blocks : blocks_) { delete blocks; }
	blocks_.clear();

	for (BlockNotDestroyable* leftBlocks : leftWallBlocks_) { delete leftBlocks; }
	leftWallBlocks_.clear();
	for (BlockNotDestroyable* rightBlocks : rightWallBlocks_) { delete rightBlocks; }
	rightWallBlocks_.clear();

	for (auto* spike : spikeTrap_) { delete spike; }
	spikeTrap_.clear();

	for (auto* explodingBlock : explodingBlocks_) { delete explodingBlock; }
	explodingBlocks_.clear();

	for (auto* conveyer : conveyers_) { delete conveyer; }
	conveyers_.clear();

	delete depthMeter_;
	delete explosion_;
	delete goal_;
}

void StageScene::Initialize()
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
	UI->Initialize();

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
		destroyableBlocks_[i]->Initialize(desBlockPos, scrollSpeed);
	}

#pragma endregion

#pragma region Blocks

	blocks_.resize(kBlockNum);
	for (int i = 0; i < kBlockNum; i++)
	{
		blocks_[i] = new BlockNotDestroyable;
		//Vector2 blockPos = BlockPos_[i];
		blocks_[i]->Initialize(BlockPos_[i], isMoss[i], false, scrollSpeed);
	}
#pragma endregion

#pragma region LeftWall

	leftWallBlocks_.resize(kWallBlockNum);
	for (int i = 0; i < kWallBlockNum; i++)
	{
		leftWallBlocks_[i] = new BlockNotDestroyable;
		leftWallPos_.y = 48.f * i;
		leftWallBlocks_[i]->Initialize(leftWallPos_, false, true, scrollSpeed);
	}

#pragma endregion

#pragma region RightWall

	rightWallBlocks_.resize(kWallBlockNum);
	for (int i = 0; i < kWallBlockNum; i++)
	{
		rightWallBlocks_[i] = new BlockNotDestroyable;
		rightWallPos_.y = 48.f * i;
		rightWallBlocks_[i]->Initialize(rightWallPos_, false, true, scrollSpeed);
	}
#pragma endregion

#pragma region Spike Trap

	spikeTrap_.resize(kSpikeTrapNum);
	for (int i = 0; i < kSpikeTrapNum; i++)
	{
		spikeTrap_[i] = new SpikeTrap;
		spikeTrap_[i]->Initialize(spikeTrapPos_[i], scrollSpeed);
	}

#pragma endregion

#pragma region Exploding Block

	explodingBlocks_.resize(kExplodingBlockNum);
	for (int i = 0; i < kExplodingBlockNum; i++)
	{
		explodingBlocks_[i] = new BlockExplodingTrap;
		//Vector2 blockPos = BlockPos_[i];
		explodingBlocks_[i]->Initialize(explodingBlockPos_[i], isExplodingBlockMoss[i], scrollSpeed);
	}

#pragma endregion

#pragma region Conveyer

	conveyers_.resize(kConveyorNum);
	for (int i = 0; i < kConveyorNum; i++)
	{
		conveyers_[i] = new Conveyor;
		conveyers_[i]->Initialize(conveyerPos_[i], isConveyorRight[i],scrollSpeed);
	}

#pragma endregion

#pragma region Depth Meter

	depthMeter_ = new DepthMeter;
	depthMeter_->Initialize((int)goalPos_.y);

#pragma endregion


#pragma region Explosion

	explosion_ = new Explosion;
	explosion_->Initialize({ -100,100 });

#pragma endregion

#pragma region Goal

	goal_ = new Goal;
	goal_->Initialize(goalPos_, scrollSpeed);

#pragma endregion

}

void StageScene::Update()
{
	ChangePhase();
	background_->Update();

	switch (phase_)
	{
	case StageScene::Phase::kFadeIn:
		fade_->Update();
		break;

	case StageScene::Phase::kPlay:

		UserInterfaceDepthMeter();
		depthMeter_->Update();
		// Player
		SetPlayerStatus();

		player_->Update(scrollSpeed);
		player_->CollisionWithBlock(blocks_);
		if (!player_->IsOnGround()) {
			player_->CollisionWithExplodingBlock(explodingBlocks_);
		}
		if (!player_->IsOnGround()) 
		{
			player_->CollisiontWithConveyor(conveyers_);
		}
		if (!player_->IsOnGround())
		{
			player_->CollisionWithGoal(goal_);
		}
		player_->Drilling();

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
			else { ++i; }
		}

		//Blocks
		for (auto* blocks : blocks_) { blocks->Update(); }

		// WallBlocks
		for (auto* wallblock : leftWallBlocks_) { wallblock->Update(); }
		for (auto* wallblock : rightWallBlocks_) { wallblock->Update(); }

		// Spike Trap
		for (auto* spike : spikeTrap_) {
			spike->Update();
		}

		//Exploding Blocks
		for (int i = 0; i < explodingBlocks_.size();)
		{
			explodingBlocks_[i]->Update();

			if (explodingBlocks_[i]->IsDestroyed()) 
			{
				explosion_->SetIsExploding(true); 
				explosion_->Initialize({ explodingBlocks_[i]->GetPos().x, explodingBlocks_[i]->GetPos().y -15}); //make the explosion the position of the destroyed block
			}
			if (explodingBlocks_[i]->GetIsAboveScreen())
			{
				delete explodingBlocks_[i];
				explodingBlocks_.erase(explodingBlocks_.begin() + i);
			}
			else { ++i; }
		}

		for (auto* conveyor : conveyers_) {
			conveyor->Update();
		}

		UI->Update(true, false);

		if (explosion_->GetIsExploding()) 
		{
			explosion_->Update();
		}

		goal_->Update();

		DeleteBlocks();
		CheckAllCollision();
		
		break;
	case StageScene::Phase::kDeath:

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
			else { ++i; }
		}

		//Blocks
		for (auto* blocks : blocks_) { blocks->Update(); }

		// WallBlocks
		for (auto* wallblock : leftWallBlocks_) { wallblock->Update(); }
		for (auto* wallblock : rightWallBlocks_) { wallblock->Update(); }

		//Exploding Blocks
		for (int i = 0; i < explodingBlocks_.size();)
		{
			explodingBlocks_[i]->Update();

			if (explodingBlocks_[i]->GetIsAboveScreen())
			{
				delete explodingBlocks_[i];
				explodingBlocks_.erase(explodingBlocks_.begin() + i);
			}
			else { ++i; }
		}

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
		if (player_->IsDead()) { phase_ = Phase::kDeath; }

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
	// Background
	background_->Draw();

	// Player
	player_->Draw();

	// Destroyable Blocks
	for (auto* destroyableBlock : destroyableBlocks_) { destroyableBlock->Draw(); }

	//Blocks
	for (auto* block : blocks_) { block->Draw(); }

	//Wall Blocks
	for (auto* wallblock : leftWallBlocks_) { wallblock->Draw(); }
	for (auto* wallblock : rightWallBlocks_) { wallblock->Draw(); }

	for (auto* explodingBlock : explodingBlocks_) { explodingBlock->Draw(); }

	// Spike
	for (auto* spike : spike_) { spike->Draw(); }
	// Spike Trap
	for (auto* spike : spikeTrap_) { spike->Draw(); }

	for (auto* conveyor : conveyers_) {
		conveyor->Draw();
	}

	if (explosion_->GetIsExploding()) 
	{
		explosion_->Draw();
	}

	goal_->Draw();

	UI->Draw();

	depthMeter_->Draw();


	switch (phase_)
	{
	case StageScene::Phase::kFadeIn:
		// Fade
		fade_->Draw();
		break;

	case StageScene::Phase::kPlay:
		break;
	case StageScene::Phase::kDeath:
		break;
	case StageScene::Phase::kStageClear:
		Novice::ScreenPrintf(50, 0, "CLEAR");
		break;
	case StageScene::Phase::kFadeOut:

		fade_->Draw();
		break;
	}
}

void StageScene::DeleteBlocks()
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

	for (int i = 0; i < explodingBlocks_.size();)
	{
		if (explodingBlocks_[i]->IsDestroyed() && player_->GetHasExploded()) //if block is destroyed
		{
			delete explodingBlocks_[i]; //delete block
			explodingBlocks_.erase(explodingBlocks_.begin() + i); //erase it from the vector
			break;
		}
		else { i++; }
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
				blocks_[i]->SetTakenDamage(0); //damage is 1
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

#pragma region player & spike trap collision

	Object obj5;

	for (int i = 0; i < spikeTrap_.size(); i++)
	{
		obj5 = spikeTrap_[i]->GetObject_();
		if (isCollideObject(obj1, obj5) && !player_->GetIsTakingDamage())
		{
			player_->OnCollision();
		}
	}

#pragma endregion

#pragma region  player & exploding block

	Object obj6;

	for (int i = 0; i < explodingBlocks_.size(); ++i) //reset all blocks to not being touched
	{
		explodingBlocks_[i]->SetIsTouched(false);
		explodingBlocks_[i]->SetStartShake(false);
	}

	for (int i = 0; i < explodingBlocks_.size();)
	{
		obj6 = explodingBlocks_[i]->GetObject_();
		if (isCollideObject(obj3, obj6))
		{
			explodingBlocks_[i]->OnCollision(player_);

			if (player_->GetIsDrilling()) //if we're drilling
			{
				explodingBlocks_[i]->SetTakenDamage(5); //damage is 5
				explodingBlocks_[i]->SetStartShake(true); //shake
			}
			else
			{
				explodingBlocks_[i]->SetTakenDamage(0); //damage is 1
				explodingBlocks_[i]->SetStartShake(false);
			}

			if (explodingBlocks_.empty() || explodingBlocks_[i] == nullptr) {
				continue;	// If block was destroyed or blocks_ changed, avoid incrementing "i"
			}

			if (explodingBlocks_[i]->IsDestroyed())
			{
				player_->OnCollision(explodingBlocks_[i]);
				player_->SetHasExploded(true);
			}
			break;
		}
		else
		{
			explodingBlocks_[i]->SetIsTouched(false); //not on top of the block anymore
			explodingBlocks_[i]->SetStartShake(false);

		}
		++i; // Increment if no collision or block was not removed
	}

#pragma endregion

#pragma region player & goal

	Object obj7 = goal_->GetObject_();

	if (isCollideObject(obj3, obj7))
	{
		phase_ = Phase::kStageClear;
	}

#pragma endregion


#pragma region player & conveyor collision

#pragma endregion


#pragma region player & item collision

#pragma endregion
	
}

void StageScene::SetPlayerStatus()
{
	float playerDrillPower = player_->GetDrillPower();
	UI->SetDrillPower(playerDrillPower);

	bool isDrilling = player_->GetIsDrilling();
	UI->SetIsDrilling(isDrilling);

	int playerHP = player_->GetUIHP();
	UI->SetPlayerHP(playerHP);
}

void StageScene::UserInterfaceDepthMeter()
{
	float playerY = player_->GetPos().y;

	depthMeter_->SetPlayerYPos(playerY);
}
