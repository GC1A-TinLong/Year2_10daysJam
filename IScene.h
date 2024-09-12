#pragma once

enum Scene {
	TITLE,
	BASIC_TUTORIAL,
	STAGESELECT,
	STAGE,
	STAGE2,
	STAGE3,
	CLEAR 
};

class IScene
{
protected:
	static int sceneNo;	// Managing scene no.

public:
	virtual void Initialize() = 0;
	virtual void Update() = 0;
	virtual void Draw() = 0;

	virtual ~IScene();

	int GetSceneNo() { return sceneNo; }
};
