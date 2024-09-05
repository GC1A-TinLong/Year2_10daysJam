#include "Pause.h"
#include "Novice.h"
#include "Input.h"

void Pause::Initialize()
{
	pause1Handle_ = Novice::LoadTexture("./Resources/Pause/pauseText1.png");
	pause2Handle_ = Novice::LoadTexture("./Resources/Pause/pauseText2.png");
	pauseTextOnlyHandle_ = Novice::LoadTexture("./Resources/Pause/pauseTextOnly1.png");
}

void Pause::Update()
{
	if (isPaused_) 
	{
		if (!isOnMeny2) 
		{
			pauseStatus_ = PauseStatus::PauseMenu1;
		}
		else 
		{
			pauseStatus_ = PauseStatus::PauseMenu2;
		}
		if (pressTimer <= 7) 
		{
			pressTimer++;
		}
		if (Input::GetInstance()->TriggerKey(DIK_ESCAPE))
		{
			isPaused_ = false;
			isOnMeny2 = false;
			hasPressedDown = false;
		}
	}
	else 
	{
		pressTimer = 0;
	}
	switch (pauseStatus_)
	{
	case PauseStatus::None:
		break;
	case PauseStatus::PauseMenu1:

		PauseAnimation();

		PauseMenu1Menuing();

		break;
	case PauseStatus::PauseMenu2:

		PauseAnimation();
		
		PauseMenu2Menuing();

		break;
	default:
		break;
	}
	

	
}

void Pause::PauseAnimation()
{
	animationTimer++;

	if (animationTimer > maxFrames)
	{
		animationTimer = 0;
	}
	if (!hasPressedDown)
	{
		if (animationTimer < 30)
		{
			pos_.x = 0;

		}
		else if (animationTimer < 60)
		{
			pos_.x = 1920;

		}
	}
	else
	{
		if (animationTimer < 30)
		{
			pos_.x = 3840;

		}
		else if (animationTimer < 60)
		{
			pos_.x = 5760;

		}
	}

}

void Pause::PauseMenu1Menuing()
{
	if ((Input::GetInstance()->TriggerKey(DIK_DOWN) || Input::GetInstance()->TriggerKey(DIK_S) || Input::GetInstance()->TriggerKey(DIK_UP) || Input::GetInstance()->TriggerKey(DIK_W)) && !hasPressedDown && pressTimer >= 5)
	{
		hasPressedDown = true;
		pressTimer = 0;
	}

	if ((Input::GetInstance()->TriggerKey(DIK_DOWN) || Input::GetInstance()->TriggerKey(DIK_S) || Input::GetInstance()->TriggerKey(DIK_UP) || Input::GetInstance()->TriggerKey(DIK_W)) && hasPressedDown && pressTimer >= 5)
	{
		hasPressedDown = false;
		pressTimer = 0;
	}


	if (Input::GetInstance()->TriggerKey(DIK_SPACE) && pressTimer >= 5 && !hasPressedDown)
	{
		pauseStatus_ = PauseStatus::None;
		isPaused_ = false;

	}

	if (Input::GetInstance()->TriggerKey(DIK_SPACE) && hasPressedDown)
	{
		isOnMeny2 = true;
		hasPressedDown = false;
	}
}

void Pause::PauseMenu2Menuing()
{
	if ((Input::GetInstance()->TriggerKey(DIK_DOWN) || Input::GetInstance()->TriggerKey(DIK_S) || Input::GetInstance()->TriggerKey(DIK_UP) || Input::GetInstance()->TriggerKey(DIK_W)) && !hasPressedDown && pressTimer >= 5)
	{
		hasPressedDown = true;
		pressTimer = 0;
	}

	if ((Input::GetInstance()->TriggerKey(DIK_DOWN) || Input::GetInstance()->TriggerKey(DIK_S) || Input::GetInstance()->TriggerKey(DIK_UP) || Input::GetInstance()->TriggerKey(DIK_W)) && hasPressedDown && pressTimer >= 5)
	{
		hasPressedDown = false;
		pressTimer = 0;
	}
	if (Input::GetInstance()->TriggerKey(DIK_SPACE) && !hasPressedDown)
	{
		isOnMeny2 = false;
		hasPressedDown = false;
	}
	if (Input::GetInstance()->TriggerKey(DIK_SPACE) && hasPressedDown)
	{
		closeGame = true;
	}

}

void Pause::Draw()
{
	switch (pauseStatus_)
	{
	case PauseStatus::None:
		break;
	case PauseStatus::PauseMenu1:
		Novice::DrawSpriteRect(0, 0, (int)pos_.x, (int)pos_.y, 1920, 1080, pause1Handle_, scale.x, scale.y, 0.0f, WHITE);
		break;
	case PauseStatus::PauseMenu2:
		Novice::DrawSpriteRect(0, 0, (int)pos_.x, (int)pos_.y, 1920, 1080, pause2Handle_, scale.x, scale.y, 0.0f, WHITE);

		break;
	default:
		break;
	}
	//Novice::DrawQuad()
	//Novice::DrawSprite((int)pos_.x, (int)pos_.y, pause1Handle_, scale.x, scale.y, 0.0f, WHITE);
}
