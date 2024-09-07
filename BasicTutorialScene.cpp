#include "BasicTutorialScene.h"

BasicTutorialScene::~BasicTutorialScene()
{
	delete player_;
}

void BasicTutorialScene::Initialize()
{
	// Player
	player_ = new Player;

	for (int i = 0; i < kBlockNum; i++) {
		blockPos_[i] = { kBlockSize * i,500 };
	}
}

void BasicTutorialScene::Update()
{
}

void BasicTutorialScene::Draw()
{
}

void BasicTutorialScene::CheckAllCollision()
{
}
