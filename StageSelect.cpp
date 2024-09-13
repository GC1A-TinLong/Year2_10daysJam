#include "StageSelect.h"

StageSelect::~StageSelect()
{
	delete background_;
	delete UI;
	delete fade_;
	delete player_;

	for (auto* blocks : blocks_) { delete blocks; }
	blocks_.clear();
	for (auto* blocks : steelBlocks_) { delete blocks; }
	steelBlocks_.clear();
	for (auto* blocks : brokenBlocks_) { delete blocks; }
	brokenBlocks_.clear();
	for (auto* leftBlocks : leftWallBlocks_) { delete leftBlocks; }
	leftWallBlocks_.clear();
	/*for (auto* rightBlocks : rightWallBlocks_) { delete rightBlocks; }
	rightWallBlocks_.clear();*/
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
	UI->Initialize(-1);
	UI->SetStartGame(true);
	alphaSpeed = kMaxAlphaSpeed;

	// Player
	player_ = new Player;
	player_->Initialize({ 96.f,96.f + 48 * 7 - 73.f });

	blocks_.resize(kBlockNum);
	steelBlocks_.resize(kSteelBlockNum);
	brokenBlocks_.resize(kBrokenBlockNum);
	for (int y = 0; y < mapCountY; y++) {
		for (int x = 0; x < mapCountX; x++) {
			if (map[y][x] == (int)BlockType::None) { continue; }

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
			else if (map[y][x] == (int)BlockType::BrokenBlock) {
				Vector2 blockPos_ = { x * kSpriteSize + adjustPosForMapchipX, y * kSpriteSize + adjustPosForMapchipY };
				brokenBlocks_[brokenIndex] = new BlockDestroyable;
				brokenBlocks_[brokenIndex]->Initialize(blockPos_);
				brokenIndex++; // Move to the next block
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
	/*rightWallBlocks_.resize(kWallBlockNum);
	for (int i = 0; i < kWallBlockNum; i++)
	{
		rightWallBlocks_[i] = new BlockSteel;
		rightWallPos_.y = 48.f * i;
		rightWallBlocks_[i]->Initialize(rightWallPos_, true);
	}*/
}

void StageSelect::Update()
{
	ChangePhase();

	background_->Update(scrollSpeed);
	Animation();
	// WallBlocks
	for (auto* wallblock : leftWallBlocks_) { wallblock->Update(scrollSpeed); }
	//for (auto* wallblock : rightWallBlocks_) { wallblock->Update(scrollSpeed); }
	// Normal Blocks
	for (auto* blocks : blocks_) {
		blocks->Update(scrollSpeed);
		blocks->Respawn();
	}
	// Steel Blocks
	for (auto* blocks : steelBlocks_) { blocks->Update(scrollSpeed); }
	// Broken Blocks
	for (auto* blocks : brokenBlocks_) {
		blocks->Update(scrollSpeed);
		blocks->Respawn();
	}

	SetPlayerStatus();
	UI->Update(true, false);
	switch (phase_)
	{
	case Phase::kFadeIn:
		fade_->Update();
		break;

	case Phase::kPlay:
		// Player
		player_->Update(0.f, true, 1300.f);
		//Novice::ScreenPrintf(0, 200, "onground %d", player_->IsOnGround());
		player_->CollisionWithBlock(blocks_);
		if (!player_->IsOnGround()) { player_->CollisionWithMetalBlock(steelBlocks_); }
		if (!player_->IsOnGround()) { player_->CollisionWithDestroyableBlock(brokenBlocks_); }
		player_->Drilling();

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
	// Wall Blocks
	for (auto* wallblock : leftWallBlocks_) { wallblock->Draw(); }
	//for (auto* wallblock : rightWallBlocks_) { wallblock->Draw(); }
#pragma region Door and Text
	/// Tutorial Text ///
	Novice::DrawSprite(int(tutorialDoorPos.x) - 20, int(tutorialDoorPos.y) - 40, tutorialText, 1.f, 1.f, 0, WHITE);
	Novice::DrawSpriteRect(int(tutorialDoorPos.x), int(tutorialDoorPos.y), animationPos_.x, 0, 96, 96, stageDoor, 0.25f, 1.f, 0, WHITE);
	/// Stage 1 Text ///
	Novice::DrawSprite(int(stage1DoorPos.x) - 15, int(stage1DoorPos.y) - 40, stage1text, 1.f, 1.f, 0, WHITE);
	Novice::DrawSpriteRect(int(stage1DoorPos.x), int(stage1DoorPos.y), animationPos_.x, 0, 96, 96, stageDoor, 0.25f, 1.f, 0, WHITE);
	/// Stage 2 Text ///
	Novice::DrawSprite(int(stage2DoorPos.x) - 15, int(stage2DoorPos.y) - 40, stage2text, 1.f, 1.f, 0, WHITE);
	Novice::DrawSpriteRect(int(stage2DoorPos.x), int(stage2DoorPos.y), animationPos_.x, 0, 96, 96, stageDoor, 0.25f, 1.f, 0, WHITE);
	/// Stage 3 Text ///
	Novice::DrawSprite(int(stage3DoorPos.x) - 15, int(stage3DoorPos.y) - 40, stage3text, 1.f, 1.f, 0, WHITE);
	Novice::DrawSpriteRect(int(stage3DoorPos.x), int(stage3DoorPos.y), animationPos_.x, 0, 96, 96, stageDoor, 0.25f, 1.f, 0, WHITE);
	/// Stage 4 Text ///
	Novice::DrawSprite(int(stage4DoorPos.x) - 15, int(stage4DoorPos.y) - 40, stage4text, 1.f, 1.f, 0, WHITE);
	Novice::DrawSpriteRect(int(stage4DoorPos.x), int(stage4DoorPos.y), animationPos_.x, 0, 96, 96, stageDoor, 0.25f, 1.f, 0, WHITE);
	/// Stage 5 Text ///
	Novice::DrawSprite(int(stage5DoorPos.x) - 15, int(stage5DoorPos.y) - 40, stage5text, 1.f, 1.f, 0, WHITE);
	Novice::DrawSpriteRect(int(stage5DoorPos.x), int(stage5DoorPos.y), animationPos_.x, 0, 96, 96, stageDoor, 0.25f, 1.f, 0, WHITE);
#pragma endregion
	// Player
	player_->Draw();
	// Blocks
	for (auto* block : blocks_) { block->Draw(); }
	for (auto* block : steelBlocks_) { block->Draw(); }
	for (auto* block : brokenBlocks_) { block->Draw(); }
	// letter W text
	if (isCollideTutorialDoor || isCollideStage1Door || isCollideStage2Door || isCollideStage3Door || isCollideStage4Door || isCollideStage5Door) {
		Novice::DrawSprite(int(player_->GetPos().x) - 15, int(player_->GetPos().y) - 90, letterW, 1.f, 1.f, 0, color_W);
	}
	// UI
	UI->Draw();

	switch (phase_)
	{
	case Phase::kFadeIn:
		// Fade
		fade_->Draw();
		break;
	case Phase::kFadeOut:
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
		GoToNextScene();
		break;

	case Phase::kFadeOut:
		if (fade_->IsFinished()) {
			if (isCollideTutorialDoor) {
				sceneNo = BASIC_TUTORIAL;
			}
			else if (isCollideStage1Door) {
				sceneNo = STAGE;
			}
			else if (isCollideStage2Door) {
				sceneNo = STAGE2;
			}
			else if (isCollideStage3Door) {
				sceneNo = STAGE3;
			}
			else if (isCollideStage4Door) {
				sceneNo = STAGE4;
			}
			else if (isCollideStage5Door) {
				sceneNo = LAST_STAGE;
			}
		}
		break;
	}
}

void StageSelect::GoToNextScene()
{
	if (Input::GetInstance()->TriggerKey(DIK_W)) {
		if (isCollideTutorialDoor || isCollideStage1Door || isCollideStage2Door || isCollideStage3Door || isCollideStage4Door || isCollideStage5Door) {
			fade_->Start(Status::FadeOut, duration_);
			phase_ = Phase::kFadeOut;
		}
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
	Object playerObj = player_->GetObject_();
	Object doorObj = { tutorialDoorPos,doorSize };
	// Tutorial Door
	if (isCollideObject(playerObj, doorObj)) {
		isCollideTutorialDoor = true;
	}
	else { isCollideTutorialDoor = false; }
	// Stage 1 Door
	doorObj = { stage1DoorPos,doorSize };
	if (isCollideObject(playerObj, doorObj)) {
		isCollideStage1Door = true;
	}
	else { isCollideStage1Door = false; }
	// Stage 2 Door
	doorObj = { stage2DoorPos,doorSize };
	if (isCollideObject(playerObj, doorObj)) {
		isCollideStage2Door = true;
	}
	else { isCollideStage2Door = false; }
	// Stage 3 Door
	doorObj = { stage3DoorPos,doorSize };
	if (isCollideObject(playerObj, doorObj)) {
		isCollideStage3Door = true;
	}
	else { isCollideStage3Door = false; }
	// Stage 4 Door
	doorObj = { stage4DoorPos,doorSize };
	if (isCollideObject(playerObj, doorObj)) {
		isCollideStage4Door = true;
	}
	else { isCollideStage4Door = false; }
	// Stage 5 Door
	doorObj = { stage5DoorPos,doorSize };
	if (isCollideObject(playerObj, doorObj)) {
		isCollideStage5Door = true;
	}
	else { isCollideStage5Door = false; }

	if (isCollideTutorialDoor || isCollideStage1Door || isCollideStage2Door || isCollideStage3Door || isCollideStage4Door || isCollideStage5Door) {
		if (alpha_W < 240) { alphaSpeed = kMaxAlphaSpeed; }
		else if (alpha_W >= 240) { alphaSpeed = 1; }
		alpha_W += alphaSpeed;
		if (alpha_W >= 255) { alpha_W = 20; }
		//Novice::ScreenPrintf(0, 0, "alpha %u", alpha_W);
	}
	else { alpha_W = 20; }

	color_W = RGB_W + alpha_W;
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

#pragma region player & broken block collision
	Object brokenBlockObj;

	for (int i = 0; i < brokenBlocks_.size(); ++i) //reset all blocks to not being touched
	{
		brokenBlocks_[i]->SetIsTouched(false);
		brokenBlocks_[i]->SetStartShake(false);
	}

	for (int i = 0; i < brokenBlocks_.size();)
	{
		brokenBlockObj = brokenBlocks_[i]->GetObject_();
		if (isCollideObject(playerDrillPointObj, brokenBlockObj) && !brokenBlocks_[i]->IsDestroyed())
		{
			brokenBlocks_[i]->OnCollision(player_);
			brokenBlocks_[i]->SetStartShake(true);

			if (player_->GetIsDrilling()) //if we're drilling
			{
				brokenBlocks_[i]->SetTakenDamage(5); //damage is 5
			}
			else
			{
				brokenBlocks_[i]->SetTakenDamage(1); //damage is 1
			}

			if (brokenBlocks_.empty() || brokenBlocks_[i] == nullptr) {
				continue;	// If block was destroyed or blocks_ changed, avoid incrementing "i"
			}
			//break;
		}
		else
		{
			brokenBlocks_[i]->SetIsTouched(false); //not on top of the block anymore
			brokenBlocks_[i]->SetStartShake(false);

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

void StageSelect::Animation()
{
	animationTimer_++;
	if (animationTimer_ >= 10) {
		animationTimer_ = 0;
		animationPos_.x += animeWidth;
	}
	if (animationPos_.x >= float(96 * 3)) {
		animationPos_.x = 0;
		animationTimer_ = 0;
	}
}
