#pragma once
#include "../../../Sound/Sound.h"
#include "../../../Graphic/TextBox.h"
#include "../../../Graphic/Sprite.h"
#include "../../../Input/InputChecker.h"

// �`���[�g���A���ł̎w���ꊇ��̏���
class TutorialCommand
{
public:
	virtual ~TutorialCommand() {}

	virtual void onStart() = 0;
	virtual void onUpdate(float deltaTime) = 0;
	virtual void onDraw()const = 0;
	virtual void onEnd() = 0;
	virtual void setText() = 0;

	void start();
	void update(float deltaTime);
	void draw()const;
	void end();

	bool isCommandEnd() { return isCommandEnd_; }

protected:

	// "A_Push"�̉摜��\������t���O
	bool displayA_Push_{ false };

	// "Y_Push"�̉摜��\������t���O
	bool displayY_Push_{ false };

	// "Y_Push"�̉摜��\������t���O
	bool displayLT_Push_{ false };

	// "Y_Push"�̉摜��\������t���O
	bool displayRT_Push_{ false };

	// �摜�_�ŗp�J�E���g
	int sinCount_{ 0 };

	// �w�����I�������t���O
	bool isCommandEnd_{ false };

	// �e�L�X�g�\���N���X
	TextBox textBox_{};

	// �e�L�X�g�{�b�N�X�̕\���ʒu
	Vector2 textBoxPos_{ 200.0f, 800.0f };

	// �e�L�X�g�{�b�N�X�̑傫��
	Vector2 textBoxSize_{ 1200.0f, 150.0f };

	// "A_Push"�̉摜�̕\���ʒu
	Vector2 A_PushPos_{ 1250.0f, 800.0f };

	// "A_Push"�̉摜�̕\���ʒu
	Vector2 Push_Arrow_Pos_{ 1268.0f, 760.0f };
};