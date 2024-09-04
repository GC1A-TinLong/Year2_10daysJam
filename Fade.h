#pragma once
#include "MathFunction.h"

enum class Status
{
	None,
	FadeIn,
	FadeOut,
};


class Fade
{

	public:

		void Initialize();

		void Update();

		void Start(Status status, float duration);

		void Stop();

		bool IsFinished();

		void ResetCounter();

		void SetCounter_(float counter) { counter_ = counter; };

		void Draw();

	private:

		Vector2Int pos_ = { 0,0 };
		Vector2Int size_ = { 1080,1080 };
		int textureHandle_ = 0;
		Status status_ = Status::None; //Set this to none
		float duration_ = 0.0f;
		float counter_ = 0.0f;
		int seethrough_;
		int seethroughTimer_;

};

