#include <Novice.h>
#include "GameManager.h"

const char kWindowTitle[] = "6005_タイトル";

// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {

	// Initialize library
	Novice::Initialize(kWindowTitle, 1920, 1080);

	std::unique_ptr<GameManager>gameManager = std::make_unique<GameManager>();

	gameManager->Run();

	// ライブラリの終了
	Novice::Finalize();
	return 0;
}