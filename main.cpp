#include <Novice.h>
#include "GameManager.h"

const char kWindowTitle[] = "6005_タイトル";

// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {

	// ライブラリの初期化
	Novice::Initialize(kWindowTitle, 1280, 720);

	std::unique_ptr<GameManager>gameManager = std::make_unique<GameManager>();

	gameManager->Run();

	// ライブラリの終了
	Novice::Finalize();
	return 0;
}