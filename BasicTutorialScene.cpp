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
	isPage[0] = true;
	A = 0;
	color = (R << 24) | (G << 16) | (B << 8) | A;	// "|" == "or" (for bit calculation)
	// Background
	background_ = new Background;
	background_->Initialize(backgroundHandle_);
	UI = new UserInterface;
	UI->Initialize();
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
	player_->Initialize({ 792.f,500.f - player_->GetSize().height }, scrollSpeed);

	// Normal Block
	blocks_.resize(kBlockNum);
	blockPos_.resize(kBlockNum);
	int j = 0;
	for (int i = 0; i < kBlockNum; i++)
	{
		blocks_[i] = new BlockNotDestroyable;
		if (i < 25) {
			blockPos_[i] = { (kBlockSize * 4) + (kBlockSize * i),500.f };
		}
		else if (i < 30) {
			if (i == 25) { j = 0; }
			else { j++; }
			blockPos_[i] = { (kBlockSize * 14) + (kBlockSize * j),700.f };
		}
		else if (i < 35) {
			if (i == 30) { j = 0; }
			else { j++; }
			blockPos_[i] = { (kBlockSize * 21) + (kBlockSize * j),800.f };
		}
		else if (i < 40) {
			if (i == 35) { j = 0; }
			else { j++; }
			blockPos_[i] = { (kBlockSize * 7) + (kBlockSize * j),1000.f };
		}
		else if (i < 45) {
			if (i == 40) { j = 0; }
			else { j++; }
			blockPos_[i] = { (kBlockSize * 16) + (kBlockSize * j),1100.f };
		}
		blocks_[i]->Initialize(blockPos_[i], false, false, 0.f);
	}
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
}

void BasicTutorialScene::Update()
{
	ChangePhase();

	background_->Update();
	// WallBlocks
	for (auto* wallblock : leftWallBlocks_) { wallblock->Update(); }
	for (auto* wallblock : rightWallBlocks_) { wallblock->Update(); }
	// Spike
	for (auto* spike : spike_) { spike->Update(); }

	switch (phase_)
	{
	case BasicTutorialScene::Phase::kFadeIn:
		fade_->Update();
		break;

	case Phase::kTextExplanation:
#pragma region Tutorial Text
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
					isFinishedMovementTutor = true;
				}
			}
		}
#pragma endregion

		color = (R << 24) | (G << 16) | (B << 8) | A;
		break;

	case BasicTutorialScene::Phase::kPlay:
		// Player
		player_->Update();
		player_->CollisionWithBlock(blocks_);
		// Normal Blocks
		for (int i = 0; i < blocks_.size();)
		{
			blocks_[i]->Update();

			if (blocks_[i]->GetIsAboveScreen())
			{
				delete blocks_[i];
				blocks_.erase(blocks_.begin() + i);
			}
			else { ++i; }
		}

		DeleteBlocks();
		CheckAllCollision();

		break;
	case BasicTutorialScene::Phase::kDeath:
		// Normal Blocks
		for (int i = 0; i < blocks_.size();)
		{
			blocks_[i]->Update();

			if (blocks_[i]->GetIsAboveScreen())
			{
				delete blocks_[i];
				blocks_.erase(blocks_.begin() + i);
			}
			else { ++i; }
		}
		break;

	case BasicTutorialScene::Phase::kStageClear:
		break;

	case BasicTutorialScene::Phase::kFadeOut:
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
	// Spike
	for (auto* spike : spike_) { spike->Draw(); }

	// Player
	player_->Draw();
	//Blocks
	for (auto* block : blocks_) { block->Draw(); }
	//Wall Blocks
	for (auto* wallblock : leftWallBlocks_) { wallblock->Draw(); }
	for (auto* wallblock : rightWallBlocks_) { wallblock->Draw(); }

	UI->Draw();

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
		if (isFinishedMovementTutor) { phase_ = Phase::kPlay; }
		break;

	case Phase::kPlay:
		if (Input::GetInstance()->TriggerKey(DIK_C))
		{
			fade_->Start(Status::FadeOut, duration_);
			phase_ = Phase::kFadeOut;
		}
		if (player_->IsDead()) { phase_ = Phase::kDeath; }
		break;

	case Phase::kDeath:
		phase_ = Phase::kFadeOut;
		break;
	case Phase::kStageClear:
		break;
	case Phase::kFadeOut:
		if (fade_->IsFinished() && !player_->IsDead()) {
			sceneNo = STAGE;
		}
		else if (fade_->IsFinished() && player_->IsDead()) {
			Initialize();
		}
		break;
	}
}

void BasicTutorialScene::DeleteBlocks()
{
	for (int i = 0; i < blocks_.size();)
	{
		if (blocks_[i]->IsDestroyed())
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
}
