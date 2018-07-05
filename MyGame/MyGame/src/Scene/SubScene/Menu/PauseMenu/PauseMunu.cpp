#include "PauseMunu.h"
#include"../../../../Define.h"
#include"../../../../Input/InputChecker.h"
#include"../../../../Graphic/Sprite.h"
#include"../../../../Math/MathHelper.h"
#include"../../../../Sound/Sound.h"

PauseMunu::PauseMunu()
{
}

void PauseMunu::start()
{
	baseInit();

	menuSize_ = 3;
}

void PauseMunu::update(float deltaTime)
{
	// �_�ŃJ�E���g�̍X�V
	sinCount_ = (sinCount_ + 10) % 360;

	// �X�e�B�b�N����ɌX������
	if (InputChecker::GetInstance().KeyTriggerDown(Operation_Type::STICK_UP)) moveCursor(-1);
	// �X�e�B�b�N�����ɌX������
	if (InputChecker::GetInstance().KeyTriggerDown(Operation_Type::STICK_DOWN)) moveCursor(1);
	// ����{�^������������
	if (InputChecker::GetInstance().KeyTriggerDown(Operation_Type::DECISION_BUTTON)) decisionCheck();
}

void PauseMunu::draw() const
{
	// �w�i���Â�����摜��`��
	//Sprite::GetInstance().Draw(SPRITE_ID::SPRITE_BLIND, Vector2::Zero);

	// �g�|�[�Y�h�����ꂽ�摜��`��
	Sprite::GetInstance().Draw(SPRITE_ID::SPRITE_PAUSE_BG, Vector2::Zero);

	// �g�Q�[���ɖ߂�h�̃��j���[���ڂ̕`��
	Sprite::GetInstance().Draw(SPRITE_ID::SPRITE_RETURN_GAME, Vector2(650.0f, 270.0f));

	// �g�I�v�V�����h�̃��j���[���ڂ̕`��
	Sprite::GetInstance().Draw(SPRITE_ID::SPRITE_GO_TO_OPTION, Vector2(650.0f, 500.0f));

	// �g�^�C�g���ɖ߂�h�̃��j���[���ڂ̕`��
	Sprite::GetInstance().Draw(SPRITE_ID::SPRITE_RETURN_TITLE, Vector2(650.0f, 730.0f));

	// ���j���[�J�[�\���̉摜�̕`��
	Sprite::GetInstance().Draw(SPRITE_ID::SPRITE_MENU_CURSOR, Vector2(500 + (MathHelper::Sin((float)sinCount_) * 30), 270.0f + (cursorPos_ * 230))); // , MathHelper::Abs(MathHelper::Sin((float)sinCount_))
}

void PauseMunu::end()
{
}

void PauseMunu::decisionCheck()
{
	// �J�[�\��SE���Đ�
	Sound::GetInstance().PlaySE(SE_ID::DECISION_SE);

	switch (cursorPos_)
	{
	case 0:

		nextScene_ = SceneType::SCENE_GAMEPLAY;
		isChangeScene_ = true;
		break;

	case 1:

		nextSubScene_ = SubSceneType::OPTION;
		isChangeSubScene_ = true;
		break;

	case 2:

		nextSubScene_ = SubSceneType::DECISION_MENU;
		isChangeSubScene_ = true;
		break;

	default:
		break;
	}
}
