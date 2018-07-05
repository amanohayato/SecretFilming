#pragma once

#include <DxLib.h>

#include "Time.h"
#include "../Input/InputChecker.h"
#include "../Math/Math.h"
#include"../Camera/Camera.h"
#include"../Input/GamePad.h"
#include"../Graphic/EffekseerManager.h"
#include"../Scene/SceneManager.h"
#include"../Input/XInputGamePad.h"
#include"../Sound/Sound.h"
#include"../Graphic/TextBoxPriorityManager.h"

//#include<windows.h>

class MyGame {
public:
	// �R���X�g���N�^
	MyGame(const Vector2& screen_size = Vector2(800, 600), float rate = 1.0f, int window = TRUE, float fps = 60.0f) :
		mWidth(static_cast<int>(screen_size.x)), mHeight(static_cast<int>(screen_size.y)), mRate(rate), mWindow(window), mFps(fps), sceneManager_(){
	}
	~MyGame(){}
public:
	// ���s
	int run() {
		// �T�C�Y�w��
		SetGraphMode(mWidth, mHeight, 32);
		// �`��{��
		SetWindowSizeExtendRate(mRate);
		// �E�C���h�E���[�h�ɂ��邩�ǂ���
//#ifdef _DEBUG
		ChangeWindowMode(mWindow);
//#endif // _DEBUG
		SetUseDirect3DVersion(DX_DIRECT3D_11);
		//DXLib����������
		SetUseLarge3DPositionSupport(TRUE);
		//���C�e�B���O���s�N�Z���P�ʂ�
		SetUsePixelLighting(TRUE);
		if (DxLib_Init() == -1)return -1;//�G���[���N������I��
		SetDrawScreen(DX_SCREEN_BACK);
		SetUseBackCulling(TRUE);
		//SetAlwaysRunFlag(TRUE);//�f�o�b�O�p

		SetUseZBuffer3D(TRUE);
		SetWriteZBuffer3D(TRUE);
		HWND TempHh = GetMainWindowHandle();								//�őO�ʏ���
		SetWindowPos(TempHh, HWND_TOP, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE);
		SetWindowLong(TempHh, GWL_STYLE, WS_POPUP);
		ShowWindow(TempHh, SW_SHOWMAXIMIZED);
		start();

		// �L�[���������܂Ń��[�v���܂�
		while (isRunning()) {
			etceteraUpdate();

			update();
			ScreenFlip();
			ClearDrawScreen();
			draw();
			frameEnd();
			//Time::GetInstance().draw_fps();
			// ����ʂ̓��e��\��ʂɔ��f������
		}

		//end();

		//DXLib�g�p�I������
		//DxLib_End();

		return 0;	//�\�t�g�I��
	}

private:
	// �J�n
	void start() {
		sceneManager_.start();
	}
	// �X�V
	void update() {
		sceneManager_.update(Time::GetInstance().deltaTime());
	}
	// �`��
	void draw() {
		sceneManager_.draw();
	}
	//�t���[���I��������
	void frameEnd() {
		sceneManager_.checkIsEnd();
	}
	// �I��
	void end() {

	}
	// ���s����
	bool isRunning() { return (ProcessMessage() == 0 && !sceneManager_.isGameEnd() && Keyboard::GetInstance().KeyStateUp(KEYCODE::ESC)); }

	void etceteraUpdate() {
		//deltaTime�̍X�V
		Time::GetInstance().update();
		//���͂̍X�V
		InputChecker::GetInstance().Update();

		Sound::GetInstance().Update();
		//���͍X�V
		TextBoxPriorityManager::getInstance().update();
	}
	// �R�s�[�֎~
	MyGame(const MyGame& other) = delete;
	MyGame& operator = (const MyGame& other) = delete;

private:
	// �E�B���h�E�̕�
	int mWidth;
	// �E�B���h�E�̍���
	int mHeight;
	// �E�C���h�E�̕`��䗦
	float mRate;
	// �E�C���h�E���[�h���H
	int mWindow;
	// FPS
	float mFps;
	//�V�[���Ǘ��N���X
	SceneManager sceneManager_;
};