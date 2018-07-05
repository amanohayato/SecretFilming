#pragma once

#include"../SubScene.h"
#include"../../../Sound/Sound.h"

class Menu : public SubScene
{

protected:

	virtual void moveCursor(int moveWidth)
	{
		// �J�[�\��SE���Đ�
		Sound::GetInstance().PlaySE(SE_ID::CURSOR_MOVE_SE);

		// �J�[�\���̒l��ύX
		cursorPos_ += moveWidth;

		// �J�[�\���ʒu���}�C�i�X�ɂȂ�Ȃ�ő�l�ɂ���
		if (cursorPos_ < 0) cursorPos_ = (menuSize_ - 1);

		// �J�[�\���ʒu���ő�l�𒴂���Ȃ�[���ɂ���
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

	// �������ɂ���ăJ�[�\���������œ��������H
	bool isHighSpeedMove_;

	float longPressTimer_;

	const float longPressTime_{ 0.25f };
};