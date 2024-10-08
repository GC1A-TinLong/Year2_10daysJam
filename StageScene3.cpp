#include "StageScene3.h"

StageScene3::StageScene3()
{
}

StageScene3::~StageScene3()
{
	delete background_;
	delete fade_;
	delete UI;

	delete player_;
	for (auto* spike : spike_) { delete spike; }
	spike_.clear();

	for (BlockDestroyable* blocks : destroyableBlocks_) { delete blocks; }
	destroyableBlocks_.clear();

	/*for (BlockNotDestroyable* blocks : blocks_) { delete blocks; }
	blocks_.clear();*/

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

	for (BlockSteel* steelBlocks : blocksSteel_) { delete steelBlocks; }
	blocksSteel_.clear();
}

void StageScene3::Initialize()
{
	isStageCleared = false;
	// Scroll
	scrollSpeed = 5.f;
	clearTimer = 0;

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
	UI->Initialize(3);

	// Player
	player_ = new Player;
	player_->Initialize({ 440.f,350.f });

	// Spike
	spike_.resize(kSpikeNum);
	for (int i = 0; i < kSpikeNum; i++)
	{
		spike_[i] = new Spike;
		float initPosX = 192.f;
		spike_[i]->Initialize({ initPosX + i * 48,96 });
	}

#pragma region Destroyable Blocks

	brokenBlockIndex = 0;
	destroyableBlocks_.resize(kDestroyableBlockNum);

	for (int i = 0; i < mapCountY; i++)
	{
		for (int j = 0; j < mapCountX; j++)
		{
			if (map[i][j] == BrokenBlock)
			{
				destroyableBlocks_[brokenBlockIndex] = new BlockDestroyable;
				Vector2 blockPos_ = { j * (float)spriteSize + adjustPosForMapchip, i * (float)spriteSize + adjustPosForMapchipY };
				destroyableBlocks_[brokenBlockIndex]->Initialize(blockPos_);
				brokenBlockIndex++; // Move to the next block


			}
		}
	}

#pragma endregion

#pragma region Blocks
	//blockIndex = 0;
	//blocks_.resize(kBlockNum);

	//for (int i = 0; i < mapCountY; i++)
	//{
	//	for (int j = 0; j < mapCountX; j++)
	//	{
	//		if (map[i][j] == Block)
	//		{

	//			blocks_[blockIndex] = new BlockNotDestroyable;
	//			Vector2 blockPos_ = { j * (float)spriteSize + adjustPosForMapchip, i * (float)spriteSize + adjustPosForMapchipY };
	//			blocks_[blockIndex]->Initialize(blockPos_, isMoss[blockIndex], false);
	//			blockIndex++; // Move to the next block


	//		}
	//	}
	//}


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

#pragma region Spike Trap

	spikeIndex = 0;
	spikeTrap_.resize(kSpikeTrapNum);

	for (int i = 0; i < mapCountY; i++)
	{
		for (int j = 0; j < mapCountX; j++)
		{
			if (map[i][j] == TrapSpike)
			{
				//if (blockIndex < kBlockNum) // Ensure we don't exceed the number of blocks
				//{
				spikeTrap_[spikeIndex] = new SpikeTrap;
				Vector2 spikePos_ = { j * (float)spriteSize + adjustPosForMapchip, i * (float)spriteSize + adjustPosForMapchipY };
				spikeTrap_[spikeIndex]->Initialize(spikePos_);
				spikeIndex++; // Move to the next block


			}
		}
	}

#pragma endregion

#pragma region Exploding Block

	explosionIndex = 0;
	explodingBlocks_.resize(kExplodingBlockNum);

	for (int i = 0; i < mapCountY; i++)
	{
		for (int j = 0; j < mapCountX; j++)
		{
			if (map[i][j] == ExplosionBlock)
			{

				explodingBlocks_[explosionIndex] = new BlockExplodingTrap;
				Vector2 explodingBlockPos_ = { j * (float)spriteSize + adjustPosForMapchip, i * (float)spriteSize + adjustPosForMapchipY };
				explodingBlocks_[explosionIndex]->Initialize(explodingBlockPos_, isExplodingBlockMoss[explosionIndex]);
				explosionIndex++; // Move to the next block
			}
		}
	}

#pragma endregion

#pragma region Conveyer

	conveyers_.resize(kConveyorNum);
	for (int i = 0; i < kConveyorNum; i++)
	{
		conveyers_[i] = new Conveyor;
		conveyers_[i]->Initialize(conveyerPos_[i], isConveyorRight[i]);
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
	goal_->Initialize(goalPos_);

#pragma endregion

#pragma region Steel Block

	steelIndex = 0;
	blocksSteel_.resize(kSteelBlockNum);

	for (int i = 0; i < mapCountY; i++)
	{
		for (int j = 0; j < mapCountX; j++)
		{
			if (map[i][j] == SteelBlock)
			{
				blocksSteel_[steelIndex] = new BlockSteel;
				Vector2 blockPos_ = { j * (float)spriteSize + adjustPosForMapchip, i * (float)spriteSize + adjustPosForMapchipY };
				blocksSteel_[steelIndex]->Initialize(blockPos_, false);
				steelIndex++; // Move to the next block
			}
		}
	}

#pragma endregion

}

void StageScene3::Update()
{
	ChangePhase();

	switch (phase_)
	{
	case StageScene3::Phase::kFadeIn:
		fade_->Update();
		SetPlayerStatus();
		UI->Update(true, false);
		break;
#pragma region Play
	case StageScene3::Phase::kPlay:
	

		background_->Update(scrollSpeed);

		UserInterfaceDepthMeter();
		depthMeter_->Update(scrollSpeed);

		// Player
		SetPlayerStatus();

		player_->Update(scrollSpeed, false, goal_->GetPos().y);
		SetPlayerStatus();
		//player_->CollisionWithBlock(blocks_);
		player_->CollisionWithDestroyableBlock(destroyableBlocks_);
		if (!player_->IsOnGround()) {
			player_->CollisionWithExplodingBlock(explodingBlocks_);
		}
		/*if (!player_->IsOnGround())
		{
			player_->CollisiontWithConveyor(conveyers_);
		}*/
		if (!player_->IsOnGround())
		{
			player_->CollisionWithGoal(goal_);
		}
		if (goal_->GetStopMoving())
		{
			scrollSpeed = 0.f;
			for (auto* spike : spike_) {
				spike->SetIsStart(true);
			}
		}
		if (!player_->IsOnGround())
		{
			player_->CollisionWithMetalBlock(blocksSteel_);
		}
		player_->Drilling();

		// Spike
		for (auto* spike : spike_) {
			spike->Update();
		}

		//Destroyable Blocks
		for (int i = 0; i < destroyableBlocks_.size();)
		{
			destroyableBlocks_[i]->Update(scrollSpeed);

			if (destroyableBlocks_[i]->GetIsAboveScreen())
			{
				delete destroyableBlocks_[i];
				destroyableBlocks_.erase(destroyableBlocks_.begin() + i);
			}
			else { ++i; }
		}

		//Blocks
		//for (auto* blocks : blocks_) { blocks->Update(scrollSpeed); }

		// WallBlocks
		for (auto* wallblock : leftWallBlocks_) { wallblock->Update(scrollSpeed); }
		for (auto* wallblock : rightWallBlocks_) { wallblock->Update(scrollSpeed); }

		// Spike Trap
		for (auto* spike : spikeTrap_) {
			spike->Update(scrollSpeed);
		}

		//Exploding Blocks
		for (int i = 0; i < explodingBlocks_.size();)
		{
			explodingBlocks_[i]->Update(scrollSpeed);

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

		/*for (auto* conveyor : conveyers_) {
			conveyor->Update(scrollSpeed);
		}*/

		//Steel Blocks
		for (int i = 0; i < blocksSteel_.size();)
		{
			blocksSteel_[i]->Update(scrollSpeed);

			if (blocksSteel_[i]->GetIsAboveScreen())
			{
				delete blocksSteel_[i];
				blocksSteel_.erase(blocksSteel_.begin() + i);
			}
			else { ++i; }
		}

		UI->Update(true, false);

		if (explosion_->GetIsExploding())
		{
			explosion_->Update();
		}

		goal_->Update(scrollSpeed);

		DeleteBlocks();
		CheckAllCollision();

		break;
#pragma endregion

#pragma region Countdown

case StageScene3::Phase::kCountdown:
	UI->Countdown();
	break;

#pragma endregion

#pragma region kDeath
	case StageScene3::Phase::kDeath:
		background_->Update(scrollSpeed);

		// Spike
		for (auto* spike : spike_) {
			spike->Update();
		}

		//Destroyable Blocks
		for (int i = 0; i < destroyableBlocks_.size();)
		{
			destroyableBlocks_[i]->Update(scrollSpeed);

			if (destroyableBlocks_[i]->GetIsAboveScreen())
			{
				delete destroyableBlocks_[i];
				destroyableBlocks_.erase(destroyableBlocks_.begin() + i);
			}
			else { ++i; }
		}

		//Blocks
		//for (auto* blocks : blocks_) { blocks->Update(scrollSpeed); }

		// WallBlocks
		for (auto* wallblock : leftWallBlocks_) { wallblock->Update(scrollSpeed); }
		for (auto* wallblock : rightWallBlocks_) { wallblock->Update(scrollSpeed); }

		//Exploding Blocks
		for (int i = 0; i < explodingBlocks_.size();)
		{
			explodingBlocks_[i]->Update(scrollSpeed);

			if (explodingBlocks_[i]->GetIsAboveScreen())
			{
				delete explodingBlocks_[i];
				explodingBlocks_.erase(explodingBlocks_.begin() + i);
			}
			else { ++i; }
		}

		break;
#pragma endregion

#pragma region kStageClear
	case StageScene3::Phase::kStageClear:

		scrollSpeed = 0.f;


		background_->Update(scrollSpeed);

		UserInterfaceDepthMeter();
		depthMeter_->Update(scrollSpeed);

		// Player
		SetPlayerStatus();

		player_->Update(scrollSpeed, false, goal_->GetPos().y);
		SetPlayerStatus();
		//player_->CollisionWithBlock(blocks_);
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
		if (clearTimer < 205 && player_->GetHasTouchedGoal())
		{
			clearTimer++;
		}
		if (!player_->IsOnGround())
		{
			player_->CollisionWithDestroyableBlock(destroyableBlocks_);
		}
		if (!player_->IsOnGround())
		{
			player_->CollisionWithMetalBlock(blocksSteel_);
		}
		player_->Drilling();
		CheckAllCollision();
		goal_->Update(scrollSpeed);

		// Spike
		for (auto* spike : spike_) {
			spike->Update();
			spike->SetIsStart(false);
		}

		//Destroyable Blocks
		for (int i = 0; i < destroyableBlocks_.size();)
		{
			destroyableBlocks_[i]->Update(scrollSpeed);

			if (destroyableBlocks_[i]->GetIsAboveScreen())
			{
				delete destroyableBlocks_[i];
				destroyableBlocks_.erase(destroyableBlocks_.begin() + i);
			}
			else { ++i; }
		}

		//Blocks
		//for (auto* blocks : blocks_) { blocks->Update(scrollSpeed); }

		// WallBlocks
		for (auto* wallblock : leftWallBlocks_) { wallblock->Update(scrollSpeed); }
		for (auto* wallblock : rightWallBlocks_) { wallblock->Update(scrollSpeed); }

		// Spike Trap
		for (auto* spike : spikeTrap_) {
			spike->Update(scrollSpeed);
		}

		//Exploding Blocks
		for (int i = 0; i < explodingBlocks_.size();)
		{
			explodingBlocks_[i]->Update(scrollSpeed);

			if (explodingBlocks_[i]->IsDestroyed())
			{
				explosion_->SetIsExploding(true);
				explosion_->Initialize({ explodingBlocks_[i]->GetPos().x, explodingBlocks_[i]->GetPos().y - 15 }); //make the explosion the position of the destroyed block
			}
			if (explodingBlocks_[i]->GetIsAboveScreen())
			{
				delete explodingBlocks_[i];
				explodingBlocks_.erase(explodingBlocks_.begin() + i);
			}
			else { ++i; }
		}

		/*for (auto* conveyor : conveyers_) {
			conveyor->Update(scrollSpeed);
		}*/

		//Steel Blocks
		for (int i = 0; i < blocksSteel_.size();)
		{
			blocksSteel_[i]->Update(scrollSpeed);

			if (blocksSteel_[i]->GetIsAboveScreen())
			{
				delete blocksSteel_[i];
				blocksSteel_.erase(blocksSteel_.begin() + i);
			}
			else { ++i; }
		}

		UI->Update(true, false);

		if (explosion_->GetIsExploding())
		{
			explosion_->Update();
		}


		DeleteBlocks();


		break;
#pragma endregion
	case StageScene3::Phase::kFadeOut:
		fade_->Update();
		break;
	}
}

void StageScene3::ChangePhase()
{
	switch (phase_)
	{
	case StageScene3::Phase::kFadeIn:
		if (fade_->IsFinished() && !UI->GetStartGame())
		{
			phase_ = Phase::kCountdown;
		}
		if (fade_->IsFinished() && UI->GetStartGame())
		{
			phase_ = Phase::kPlay;
		}
		break;

	case StageScene3::Phase::kCountdown:
		if (UI->GetStartGame())
		{
			phase_ = Phase::kPlay;
		}
		break;

	case StageScene3::Phase::kPlay:
		if (isStageCleared && scrollSpeed == 0.f)
		{
			phase_ = Phase::kStageClear;
		}
		if (player_->GetDeathAnimationDone()) { phase_ = Phase::kDeath; }

		break;

	case StageScene3::Phase::kDeath:
		phase_ = Phase::kFadeOut;
		break;
	case StageScene3::Phase::kStageClear:
		if (clearTimer >= 30)
		{
			fade_->Start(Status::FadeOut, duration_);
			phase_ = Phase::kFadeOut;

		}
		break;
	case StageScene3::Phase::kFadeOut:
		if (fade_->IsFinished() && !player_->IsDead()) {
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

void StageScene3::Draw()
{
	// Background
	background_->Draw();

	// Player
	player_->Draw();

	// Destroyable Blocks
	for (auto* destroyableBlock : destroyableBlocks_) { destroyableBlock->Draw(); }

	//Blocks
	//for (auto* block : blocks_) { block->Draw(); }

	//Wall Blocks
	for (auto* wallblock : leftWallBlocks_) { wallblock->Draw(); }
	for (auto* wallblock : rightWallBlocks_) { wallblock->Draw(); }

	for (auto* explodingBlock : explodingBlocks_) { explodingBlock->Draw(); }

	for (auto* steelBlock : blocksSteel_) { steelBlock->Draw(); }


	// Spike
	for (auto* spike : spike_) { spike->Draw(); }
	// Spike Trap
	for (auto* spike : spikeTrap_) { spike->Draw(); }

	/*for (auto* conveyor : conveyers_) {
		conveyor->Draw();
	}*/

	if (explosion_->GetIsExploding())
	{
		explosion_->Draw();
	}

	goal_->Draw();

	UI->Draw();

	depthMeter_->Draw();


	switch (phase_)
	{
	case StageScene3::Phase::kFadeIn:
		// Fade
		fade_->Draw();
		break;
	case StageScene3::Phase::kCountdown:
		//UI->Draw();
		break;
	case StageScene3::Phase::kPlay:
		break;
	case StageScene3::Phase::kDeath:
		break;
	case StageScene3::Phase::kStageClear:
		break;
	case StageScene3::Phase::kFadeOut:

		fade_->Draw();
		break;
	}
}

void StageScene3::DeleteBlocks()
{
	//for (int i = 0; i < blocks_.size();)
	//{
	//	if (blocks_[i]->IsDestroyed() || blocks_[i]->GetIsAboveScreen()) //if block is destroyed
	//	{
	//		delete blocks_[i]; //delete block
	//		blocks_.erase(blocks_.begin() + i); //erase it from the vector
	//		break;
	//	}
	//	else { i++; }
	//}

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

	for (int i = 0; i < destroyableBlocks_.size();)
	{
		if (destroyableBlocks_[i]->IsDestroyed() || destroyableBlocks_[i]->GetIsAboveScreen()) //if block is destroyed
		{
			delete destroyableBlocks_[i]; //delete block
			destroyableBlocks_.erase(destroyableBlocks_.begin() + i); //erase it from the vector
			break;
		}
		else { i++; }
	}
}

void StageScene3::CheckAllCollision()
{
#pragma region player & spike collision
	Object obj1, obj2;
	obj1 = player_->GetObject_();
	for (int i = 0; i < kSpikeNum; i++)
	{
		obj2 = spike_[i]->GetObject_();
		if (isCollideObject(obj1, obj2)) {
			if (!spike_[i]->GetIsStart())
			{
				player_->OnCollision();
			}
			else
			{
				player_->SetIsDead(true);
			}
			break;
		}
	}

#pragma endregion

#pragma region player & block collision
	Object obj3 = player_->GetDrillPointObject_();	// collision on the drill
	//Object obj4;

	//for (int i = 0; i < blocks_.size(); ++i) //reset all blocks to not being touched
	//{
	//	blocks_[i]->SetIsTouched(false);
	//	blocks_[i]->SetStartShake(false);
	//}

	//for (int i = 0; i < blocks_.size();)
	//{
	//	obj4 = blocks_[i]->GetObject_();
	//	if (isCollideObject(obj3, obj4) && !blocks_[i]->IsDestroyed())
	//	{
	//		blocks_[i]->OnCollision(player_);

	//		if (player_->GetIsDrilling()) //if we're drilling
	//		{
	//			blocks_[i]->SetTakenDamage(5); //damage is 5
	//			blocks_[i]->SetStartShake(true); //shake
	//		}
	//		else
	//		{
	//			blocks_[i]->SetTakenDamage(0); //damage is 1
	//			blocks_[i]->SetStartShake(false);
	//		}

	//		if (blocks_.empty() || blocks_[i] == nullptr) {
	//			continue;	// If block was destroyed or blocks_ changed, avoid incrementing "i"
	//		}
	//		//break;
	//	}
	//	else
	//	{
	//		blocks_[i]->SetIsTouched(false); //not on top of the block anymore
	//		blocks_[i]->SetStartShake(false);

	//	}
	//	++i; // Increment if no collision or block was not removed
	//}

#pragma endregion

#pragma region player & destroyable block collision
	Object obj8;

	for (int i = 0; i < destroyableBlocks_.size(); ++i) //reset all blocks to not being touched
	{
		destroyableBlocks_[i]->SetIsTouched(false);
		destroyableBlocks_[i]->SetStartShake(false);
	}

	for (int i = 0; i < destroyableBlocks_.size();)
	{
		obj8 = destroyableBlocks_[i]->GetObject_();
		if (isCollideObject(obj3, obj8) && !destroyableBlocks_[i]->IsDestroyed())
		{
			destroyableBlocks_[i]->OnCollision(player_);
			destroyableBlocks_[i]->SetStartShake(true);

			if (player_->GetIsDrilling()) //if we're drilling
			{
				destroyableBlocks_[i]->SetTakenDamage(5); //damage is 5
			}
			else
			{
				destroyableBlocks_[i]->SetTakenDamage(1); //damage is 1
			}

			if (destroyableBlocks_.empty() || destroyableBlocks_[i] == nullptr) {
				continue;	// If block was destroyed or blocks_ changed, avoid incrementing "i"
			}
			//break;
		}
		else
		{
			destroyableBlocks_[i]->SetIsTouched(false); //not on top of the block anymore
			destroyableBlocks_[i]->SetStartShake(false);

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
		isStageCleared = true;
		//Initialize();
	}

#pragma endregion


#pragma region player & conveyor collision

#pragma endregion


#pragma region player & item collision

#pragma endregion

}

void StageScene3::SetPlayerStatus()
{
	float playerDrillPower = player_->GetDrillPower();
	UI->SetDrillPower(playerDrillPower);

	bool isDrilling = player_->GetIsDrilling();
	UI->SetIsDrilling(isDrilling);

	int playerHP = player_->GetUIHP();
	UI->SetPlayerHP(playerHP);
}

void StageScene3::UserInterfaceDepthMeter()
{
	float playerY = player_->GetPos().y + player_->GetSize().height;

	depthMeter_->SetPlayerYPos(playerY);
}

