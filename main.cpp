#include <Novice.h>
#include "GameManager.h"

const char kWindowTitle[] = "6005_タイトル";

// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {

	// Initialize library
	Novice::Initialize(kWindowTitle, 1920, 1080);
	// Play Screen : width:1296, height:1056 (two side have wall(48))
	// Left blank: 48*3	  Top blank: 48*2

	std::unique_ptr<GameManager>gameManager = std::make_unique<GameManager>();

	gameManager->Run();

	// ライブラリの終了
	Novice::Finalize();
	return 0;
}