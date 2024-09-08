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

	// Background
	background_ = new Background;
	background_->Initialize(backgroundHandle_);
	UI = new UserInterface;
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
	player_->Initialize({ 640.f,500.f - player_->GetSize().height });

	// Normal Block
	blocks_.resize(kBlockNum);
	blockPos_.resize(kBlockNum);
	for (int i = 0; i < kBlockNum; i++) {
		blocks_[i] = new BlockNotDestroyable;
		blockPos_[i] = { (kBlockSize * 4) + (kBlockSize * i),500.f };
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
	case BasicTutorialScene::Phase::kFadeIn:
		// Fade
		fade_->Draw();

		break;
	case BasicTutorialScene::Phase::kPlay:
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
}

void BasicTutorialScene::ChangePhase()
{
	switch (phase_)
	{
	case BasicTutorialScene::Phase::kFadeIn:
		if (fade_->IsFinished()) { phase_ = Phase::kPlay; }
		break;

	case BasicTutorialScene::Phase::kPlay:
		if (Input::GetInstance()->TriggerKey(DIK_C))
		{
			fade_->Start(Status::FadeOut, duration_);
			phase_ = Phase::kFadeOut;
		}
		if (player_->IsDead()) { phase_ = Phase::kDeath; }
		break;

	case BasicTutorialScene::Phase::kDeath:
		phase_ = Phase::kFadeOut;
		break;
	case BasicTutorialScene::Phase::kStageClear:
		break;
	case BasicTutorialScene::Phase::kFadeOut:
		if (fade_->IsFinished() && !player_->IsDead()) {
			sceneNo = STAGE;
		}
		else if (fade_->IsFinished() && player_->IsDead()) {
			Initialize();
		}
		break;
	}
}
