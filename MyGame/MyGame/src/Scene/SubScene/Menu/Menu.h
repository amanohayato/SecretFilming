#pragma once

#include"../SubScene.h"
#include"../../../Sound/Sound.h"

class Menu : public SubScene
{

protected:

	virtual void moveCursor(int moveWidth)
	{
		// カーソルSEを再生
		Sound::GetInstance().PlaySE(SE_ID::CURSOR_MOVE_SE);

		// カーソルの値を変更
		cursorPos_ += moveWidth;

		// カーソル位置がマイナスになるなら最大値にする
		if (cursorPos_ < 0) cursorPos_ = (menuSize_ - 1);

		// カーソル位置が最大値を超えるならゼロにする
		if (cursorPos_ >(menuSize_ - 1)) cursorPos_ = 0;
	}

	virtual void decisionCheck() = 0;

	virtual void baseInit() override
	{
		isChangeScene_ = false;
		isChangeSubScene_ = false;
		isGameEnd_ = false;

		cursorPos_ = 0;
		isHighSpeedMove_ = false;
		longPressTimer_ = 0.0f;
	}

protected:

	int cursorPos_{ 0 };

	int menuSize_;

	// 長押しによってカーソルを高速で動かすか？
	bool isHighSpeedMove_;

	float longPressTimer_;

	const float longPressTime_{ 0.25f };
};