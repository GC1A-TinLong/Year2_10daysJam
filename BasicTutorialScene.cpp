#include "BasicTutorialScene.h"

BasicTutorialScene::~BasicTutorialScene()
{
	delete background_;
	delete fade_;
	delete UI;
	delete player_;
	for (auto* spike : spike_) { delete spike; }
	spike_.clear();
#pragma region BLOCK
	for (auto* blocks : blocks_) { delete blocks; }
	blocks_.clear();
	for (auto* leftWall : leftWallBlocks_) { delete leftWall; }
	leftWallBlocks_.clear();
	for (auto* rightWall : rightWallBlocks_) { delete rightWall; }
	rightWallBlocks_.clear();
#pragma endregion
}

void BasicTutorialScene::Initialize()
{
#pragma region Fade
	phase_ = Phase::kFadeIn;
	fade_ = new Fade();
	fade_->Initialize();
	fade_->Start(Status::FadeIn, duration_);
#pragma endregion

	// Text
	UI = new UserInterface;
	UI->Initialize(0);
	UI->SetStartGame(true);
	isPage[0] = true;
	A = 0;
	color = (R << 24) | (G << 16) | (B << 8) | A;	// "|" == "or" (for bit calculation)
	// Background
	background_ = new Background;
	background_->Initialize(backgroundHandle_);
	// Spike
	spike_.resize(kSpikeNum);
	for (int i = 0; i < kSpikeNum; i++)
	{
		spike_[i] = new Spike;
		Vector2 initPos = { (kBlockSize * 4) + (i * 48),96.f };
		spike_[i]->Initialize(initPos);
	}
	// Player
	player_ = new Player;
	player_->Initialize({ 780.f,499.f - player_->GetSize().height });

	// Normal Blocks
	blocks_.resize(kBlockNum);
	blockPos_.resize(kBlockNum);
	int j = 0; // blocks pos & initialize
	int rowOfBlock = 2;
	int platformBlockNum = 5;
	for (int i = 0; i < kBlockNum; i++)
	{
		blocks_[i] = new BlockNotDestroyable;
		blockPos_[i] = { (kBlockSize * 4) + (kBlockSize * i),500.f };

		if (i > kRowBlockNum - 1) {
			if (i == kRowBlockNum) { j = 0; }
			blockPos_[i] = { (kBlockSize * 4) + (kBlockSize * j),548.f };
		}
		// row of block // 
		if (i > kRowBlockNum * rowOfBlock - 1) {
			if (i == kRowBlockNum * rowOfBlock) { j = 0; }
			blockPos_[i] = { (kBlockSize * 14) + (kBlockSize * j),800.f };
		}
		if (i > kRowBlockNum * rowOfBlock + platformBlockNum - 1) {
			if (i == kRowBlockNum * rowOfBlock + platformBlockNum) { j = 0; }
			blockPos_[i] = { (kBlockSize * 21) + (kBlockSize * j),900.f };
		}
		if (i > kRowBlockNum * rowOfBlock + platformBlockNum * 2 - 1) {
			if (i == kRowBlockNum * rowOfBlock + platformBlockNum * 2) { j = 0; }
			blockPos_[i] = { (kBlockSize * 7) + (kBlockSize * j),1100.f };
		}
		if (i > kRowBlockNum * rowOfBlock + platformBlockNum * 3 - 1) {
			if (i == kRowBlockNum * rowOfBlock + platformBlockNum * 3) { j = 0; }
			blockPos_[i] = { (kBlockSize * 16) + (kBlockSize * j),1200.f };
		}
		if (i > kRowBlockNum * rowOfBlock + platformBlockNum * 4 - 1) {
			if (i == kRowBlockNum * rowOfBlock + platformBlockNum * 4) { j = 0; }
			blockPos_[i] = { (kBlockSize * 8) + (kBlockSize * j),1500.f };
		}
		if (i > kRowBlockNum * rowOfBlock + platformBlockNum * platformBlockNum - 1) {
			if (i == kRowBlockNum * rowOfBlock + platformBlockNum * 5) { j = 0; }
			blockPos_[i] = { (kBlockSize * 16) + (kBlockSize * j),1700.f };
		}
		if (i > kRowBlockNum * rowOfBlock + platformBlockNum * 6 - 1) {
			if (i == kRowBlockNum * rowOfBlock + platformBlockNum * 6) { j = 0; }
			blockPos_[i] = { (kBlockSize * 7) + (kBlockSize * j),2100.f };
		}
		j++;

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


#pragma region Goal

	goal_ = new Goal;
	goal_->Initialize(goalPos_);

#pragma endregion


#pragma region Depth Meter

	depthMeter_ = new DepthMeter;
	depthMeter_->Initialize((int)goalPos_.y);

#pragma endregion

}

void BasicTutorialScene::Update()
{
	ChangePhase();

	background_->Update(scrollSpeed);
	// WallBlocks
	for (auto* wallblock : leftWallBlocks_) { wallblock->Update(scrollSpeed); }
	for (auto* wallblock : rightWallBlocks_) { wallblock->Update(scrollSpeed); }
	// Spike
	for (auto* spike : spike_) { spike->Update(); }

	SetPlayerStatus();
	if (phase_ != Phase::kPlay) { UI->Update(isShowingDrillUI, true); }	// to hide battery and drill UI
	switch (phase_)
	{
	case BasicTutorialScene::Phase::kFadeIn:
		fade_->Update();
		break;

	case Phase::kTextExplanation:
		TextExplanation();
		break;

	case Phase::kPlay:
		// Player
		player_->Update(scrollSpeed, false, goal_->GetPos().y);
		player_->CollisionWithBlock(blocks_);
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

		goal_->Update(scrollSpeed);
		if (isAbleToDrill) {
			player_->Drilling();
			UI->Update(isShowingDrillUI, false);
			UserInterfaceDepthMeter();
			depthMeter_->Update(scrollSpeed);
		}
		// Normal Blocks
		for (auto* blocks : blocks_) { blocks->Update(scrollSpeed); }

		DeleteBlocks();
		CheckAllCollision();

		break;
	case Phase::kDeath:
		// Normal Blocks
		for (auto* blocks : blocks_) { blocks->Update(scrollSpeed); }

		DeleteBlocks();
		break;

	case Phase::kStageClear:

		scrollSpeed = 0.f;


		background_->Update(scrollSpeed);

		UserInterfaceDepthMeter();
		depthMeter_->Update(scrollSpeed);

		// Player
		SetPlayerStatus();

		player_->Update(scrollSpeed, false, goal_->GetPos().y);
		SetPlayerStatus();
		player_->CollisionWithBlock(blocks_);
		/*if (!player_->IsOnGround()) {
			player_->CollisionWithExplodingBlock(explodingBlocks_);
		}*/
		if (!player_->IsOnGround())
		{
			player_->CollisionWithGoal(goal_);
		}
		if (clearTimer < 205 && player_->GetHasTouchedGoal())
		{
			clearTimer++;
		}
	
		
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

	case Phase::kFadeOut:
		fade_->Update();
		break;
	}

	if (Input::GetInstance()->TriggerKey(DIK_C)) {
		sceneNo = STAGE;
	}
}

void BasicTutorialScene::Draw()
{
	// Background
	background_->Draw();
	//Wall Blocks
	for (auto* wallblock : leftWallBlocks_) { wallblock->Draw(); }
	for (auto* wallblock : rightWallBlocks_) { wallblock->Draw(); }

	// Player
	player_->Draw();
	//Blocks
	for (auto* block : blocks_) { block->Draw(); }

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

	case Phase::kTextExplanation:
		for (int i = 0; i < kPageNum; i++) {
			if (isPage[i]) {
				Novice::DrawSprite(int(kBlockSize * 3), int(kBlockSize * 2), pageHandle[i], 1.f, 1.f, 0, color);
			}
		}
		break;

	case Phase::kPlay:
		break;
	case Phase::kFadeOut:

		fade_->Draw();
		break;
	}
}

void BasicTutorialScene::ChangePhase()
{
	switch (phase_)
	{
	case Phase::kFadeIn:
		if (fade_->IsFinished()) { phase_ = Phase::kTextExplanation; }
		break;

	case Phase::kTextExplanation:
		if (isFinishedMovementText && !isTriedMovement) {
			phase_ = Phase::kPlay;
			isFinishedMovementText = false;
		}
		if (isAbleToDrill) { phase_ = Phase::kPlay; }
		break;

	case Phase::kPlay:
		if (Input::GetInstance()->TriggerKey(DIK_C) || isStageCleared && scrollSpeed == 0.f)
		{
			phase_ = Phase::kStageClear;
		}
		// Let player try basic movement for 5 seconds
		if (Input::GetInstance()->TriggerKey(DIK_SPACE) && !isAbleToDrill) { isStartMovement = true; }
		if (isStartMovement) {
			tryMovementTimer++;
			if (tryMovementTimer >= 30) {
				isStartMovement = false;
				isTriedMovement = true;	// go back to text explanation
				phase_ = Phase::kTextExplanation;
			}
		}

		if (player_->IsDead()) { phase_ = Phase::kDeath; }
		break;

	case Phase::kDeath:
		phase_ = Phase::kFadeOut;
		break;
	case Phase::kStageClear:
		if (clearTimer >= 150)
		{
			fade_->Start(Status::FadeOut, duration_);
			phase_ = Phase::kFadeOut;

		}
		break;
	case Phase::kFadeOut:
		if (fade_->IsFinished() && !player_->IsDead()) {
			player_->SetIsDrilling(false);
			sceneNo = STAGE;
		}
		else if (fade_->IsFinished() && player_->IsDead()) {
			Initialize();
		}
		break;
	}
}

void BasicTutorialScene::TextExplanation()
{
#pragma region Basic movement guide (Page1, 2)
	if (isPage[0]) {
		if (A < 255 && !isStartDecreaseAlpha) {
			A += 6;
			if (A >= 255) { A = 255; }
		}
		if (Input::GetInstance()->TriggerKey(DIK_SPACE)) {
			isStartDecreaseAlpha = true;
		}
		if (isStartDecreaseAlpha) {
			if (A > 0) { A -= 6; }
			if (A <= 0 || A > 255) {
				A = 0;
				isStartDecreaseAlpha = false;
				isPage[0] = false;
				isPage[1] = true;
			}
		}
	}
	else if (isPage[1]) {
		if (A < 255 && !isStartDecreaseAlpha) {
			A += 6;
			if (A >= 255) { A = 255; }
		}
		if (Input::GetInstance()->TriggerKey(DIK_SPACE)) {
			isStartDecreaseAlpha = true;
		}
		if (isStartDecreaseAlpha) {
			if (A > 0) { A -= 6; }
			if (A <= 0 || A > 255) {
				A = 0;
				isStartDecreaseAlpha = false;
				isPage[1] = false;
				isFinishedMovementText = true;
			}
		}
	}
#pragma endregion
#pragma region Drill Guide
	if (isTriedMovement) {
		isPage[2] = true;
	}
	if (isPage[2]) {
		if (A < 255 && !isStartDecreaseAlpha) {
			A += 6;
			if (A >= 255) { A = 255; }
		}
		if (Input::GetInstance()->TriggerKey(DIK_SPACE)) {
			isStartDecreaseAlpha = true;
		}
		if (isStartDecreaseAlpha) {
			if (A > 0) { A -= 6; }
			if (A <= 0 || A > 255) {
				A = 0;
				isStartDecreaseAlpha = false;
				isPage[2] = false;
				isPage[3] = true;		// go to page 4
				isTriedMovement = false;
				isShowingDrillUI = true;
			}
		}
	}
	else if (isPage[3]) {
		if (A < 255 && !isStartDecreaseAlpha) {
			A += 6;
			if (A >= 255) { A = 255; }
		}
		if (Input::GetInstance()->TriggerKey(DIK_SPACE)) {
			isStartDecreaseAlpha = true;
		}
		if (isStartDecreaseAlpha) {
			if (A > 0) { A -= 6; }
			if (A <= 0 || A > 255) {
				A = 0;
				isStartDecreaseAlpha = false;
				isPage[3] = false;
				isAbleToDrill = true;	// can drill from now
				scrollSpeed = 2.f;
			}
		}
	}
#pragma endregion

	color = (R << 24) | (G << 16) | (B << 8) | A;
}

void BasicTutorialScene::SetPlayerStatus()
{
	float playerDrillPower = player_->GetDrillPower();
	UI->SetDrillPower(playerDrillPower);

	bool isDrilling = player_->GetIsDrilling();
	UI->SetIsDrilling(isDrilling);

	int playerHP = player_->GetUIHP();
	UI->SetPlayerHP(playerHP);
}

void BasicTutorialScene::UserInterfaceDepthMeter()
{
	float playerY = player_->GetPos().y + player_->GetSize().height;

	depthMeter_->SetPlayerYPos(playerY);
}

void BasicTutorialScene::DeleteBlocks()
{
	for (int i = 0; i < blocks_.size();)
	{
		if (blocks_[i]->IsDestroyed() || blocks_[i]->GetIsAboveScreen())
		{
			delete blocks_[i]; //delete block
			blocks_.erase(blocks_.begin() + i); //erase it from the vector
			break;
		}
		else { i++; }
	}
}

void BasicTutorialScene::CheckAllCollision()
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

#pragma region player & goal

	Object obj7 = goal_->GetObject_();

	if (isCollideObject(obj3, obj7))
	{
		isStageCleared = true;
		goal_->CollisionPlayer(player_);
	}

#pragma endregion
}

