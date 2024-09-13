#pragma once
#include "Novice.h"
#include "IScene.h"
#include "Backgroud.h"
#include "Fade.h"
#include "Player.h"
#include "BlockNotDestroyable.h"
#include "BlockDestroyable.h"
#include "BlockSteel.h"
#include "UserInterface.h"
#include "Input.h"
#include <vector>

class StageSelect :public IScene
{
public:
	~StageSelect();
	void Initialize() override;
	void Update() override;
	void Draw() override;
	void ChangePhase();

	void GoToNextScene();

	void DeleteBlocks();
	void CheckAllCollision();
	void SetPlayerStatus();

	void Animation();

private:
	// Scroll
	float scrollSpeed = 0.f;

	enum class Phase
	{
		kFadeIn,
		kPlay,
		kFadeOut,
	};
	Phase phase_;

	//Background
	Background* background_ = nullptr;
	int backgroundHandle_[MAXBACKGROUNDS] =
	{
		{Novice::LoadTexture("./Resources/Background/TwoBg.png")},
		{Novice::LoadTexture("./Resources/Background/TwoBg.png")},
	};
	// UI
	UserInterface* UI = nullptr;

	// Fade
	Fade* fade_ = nullptr;
	float duration_ = 1.0f;

	// Player
	Player* player_ = nullptr;

	// Animation
	Vector2Int animationPos_ = { 0, 0 };
	int animationTimer_ = 0;
	int animeWidth = 96;
	// "W" text
	unsigned int letterW = Novice::LoadTexture("./Resources/StageSelect/keyW.png");
	uint32_t RGB_W = 0xFFFFFF00;
	uint32_t alpha_W = 20;
	int32_t alphaSpeed;
	static inline const int32_t kMaxAlphaSpeed = 4;
	bool isMaxAlpha = false;
	uint32_t color_W;
	// Stage Door
	Size doorSize = { 96,96 };
	unsigned int stageDoor = Novice::LoadTexture("./Resources/StageSelect/stageDoor.png");
	// Tutorial
	unsigned int tutorialText = Novice::LoadTexture("./Resources/StageSelect/tutorialText.png");
	Vector2 tutorialDoorPos = { 288.f,336.f };
	bool isCollideTutorialDoor = false;
	// Stage 1
	unsigned int stage1text = Novice::LoadTexture("./Resources/StageSelect/stage1.png");
	Vector2 stage1DoorPos = { 288.f,336.f * 2 + 48.f };
	bool isCollideStage1Door = false;
	// Stage 2
	unsigned int stage2text = Novice::LoadTexture("./Resources/StageSelect/stage2.png");
	Vector2 stage2DoorPos = { 288.f + 48 * 7,336.f * 2 + 48.f };
	bool isCollideStage2Door = false;
	// Stage 3
	unsigned int stage3text = Novice::LoadTexture("./Resources/StageSelect/stage3.png");
	Vector2 stage3DoorPos = { 288.f + 48 * 7,336.f };
	bool isCollideStage3Door = false;
	// Stage 4
	unsigned int stage4text = Novice::LoadTexture("./Resources/StageSelect/stage4.png");
	Vector2 stage4DoorPos = { 288.f + 48 * 14,336.f };
	bool isCollideStage4Door = false;
	// Stage 5
	unsigned int stage5text = Novice::LoadTexture("./Resources/StageSelect/last.png");
	Vector2 stage5DoorPos = { 288.f + 48 * 14,336.f * 2 + 48.f };
	bool isCollideStage5Door = false;


	enum class BlockType
	{
		None,
		Block,
		SteelBlock,
		BrokenBlock,
	};
	static inline const uint8_t mapCountX = 21;
	static inline const uint8_t mapCountY = 20;
	int map[mapCountY][mapCountX] =
	{
		2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,
		0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
		0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
		0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
		0,0,0,0,0,0,1,0,0,0,0,0,0,1,0,0,0,0,0,0,1,
		0,0,0,0,0,0,1,0,0,0,0,0,0,1,0,0,0,0,0,0,1,
		0,0,0,0,0,0,1,0,0,0,0,0,0,1,0,0,0,0,0,0,1,
		1,1,2,2,1,1,1,1,1,2,2,1,1,1,1,1,2,2,1,1,1,
		0,0,0,0,0,0,1,0,0,0,0,0,0,1,0,0,0,0,0,0,1,
		0,0,0,0,0,0,1,0,0,0,0,0,0,1,0,0,0,0,0,0,1,
		0,0,0,0,0,0,1,0,0,0,0,0,0,1,0,0,0,0,0,0,1,
		3,3,3,3,3,3,1,3,3,3,3,3,3,1,3,3,3,3,3,3,1,
		0,0,0,0,0,0,1,0,0,0,0,0,0,1,0,0,0,0,0,0,1,
		0,0,0,0,0,0,1,0,0,0,0,0,0,1,0,0,0,0,0,0,1,
		0,0,0,0,0,0,1,0,0,0,0,0,0,1,0,0,0,0,0,0,1,
		1,1,2,2,1,1,1,1,1,2,2,1,1,1,1,1,2,2,1,1,1,
		0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,1,
		0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,1,
		0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,1,
		2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,
	};
	//Mapchip
	static inline const uint8_t adjustPosForMapchipX = 192;
	static inline const uint8_t adjustPosForMapchipY = 96;
	static inline const float kSpriteSize = 48.f;
	// Block Size
	static inline const float kBlockSize = 48.f;
	// Normal Block
	static inline const uint8_t kBlockNum = 72;
	static inline const uint8_t kRowBlockNum = 25;
	std::vector<BlockNotDestroyable*>blocks_;
	uint8_t blockIndex = 0;
	// Steel Block
	static inline const uint8_t kSteelBlockNum = 54;
	std::vector<BlockSteel*>steelBlocks_;
	uint8_t steelIndex = 0;
	// BrokenBlock
	static inline const uint8_t kBrokenBlockNum = 18;
	std::vector<BlockDestroyable*>brokenBlocks_;
	uint8_t brokenIndex = 0;
	// Wall
	static inline const uint8_t kWallBlockNum = 22;
	std::vector<BlockSteel*>leftWallBlocks_;
	Vector2 leftWallPos_ = { 144.f,0.f };
	/*std::vector<BlockSteel*>rightWallBlocks_;
	Vector2 rightWallPos_ = { 1392.f,0.f };*/
};

