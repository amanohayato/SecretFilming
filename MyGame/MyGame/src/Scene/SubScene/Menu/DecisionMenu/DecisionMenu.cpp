#include "DecisionMenu.h"
#include "../../../../Input/InputChecker.h"
#include "../../../../Graphic/Sprite.h"
#include "../../../../Sound/Sound.h"
#include "../../../../Math/MathHelper.h"


DecisionMenu::DecisionMenu(SceneType afterScene, SubSceneType beforeSubScene, SPRITE_ID mainLabel)
{
	afterScene_ = afterScene;
	beforeSubScene_ = beforeSubScene;
	mainLabelType_ = mainLabel;
}

void DecisionMenu::start()
{
	baseInit();

	menuSize_ = 2;
}

void DecisionMenu::update(float deltaTime)
{
	// �_�ŃJ�E���g�̍X�V
	sinCount_ = (sinCount_ + 10) % 360;

	// �X�e�B�b�N�����ɌX������
	if (InputChecker::GetInstance().KeyTriggerDown(Operation_Type::STICK_LEFT)) moveCursor(-1);
	// �X�e�B�b�N���E�ɌX������
	if (InputChecker::GetInstance().KeyTriggerDown(Operation_Type::STICK_RIGHT)) moveCursor(1);
	// ����{�^������������
	if (InputChecker::GetInstance().KeyTriggerDown(Operation_Type::DECISION_BUTTON)) decisionCheck();
}

void DecisionMenu::draw() const
{
	// �N�\�����i��ŕ␳�j
	if (mainLabelType_ == SPRITE_ID::Game_over_retry_UI)
	{
		// �m�F���j���[�̔w�i�̕\��
		Sprite::GetInstance().Draw(mainLabelType_, Vector2(0, 0));
	}
	else
	{
		// �w�i���Â�����摜��`��
		Sprite::GetInstance().Draw(SPRITE_ID::SPRITE_BLIND, Vector2::Zero);

		// �m�F���j���[�̔w�i�̕\��
		Sprite::GetInstance().Draw(mainLabelType_, Vector2(560, 200));
	}

	// �g�͂��h�Ə����ꂽ���S�̕`��
	Sprite::GetInstance().Draw(SPRITE_ID::SPRITE_YES_UI, Vector2(450.0f, 640.0f));

	// �g�������h�Ə����ꂽ���S�̕`��
	Sprite::GetInstance().Draw(SPRITE_ID::SPRITE_NO_UI, Vector2(1240.0f, 640.0f));

	// ���j���[�J�[�\���̕`��
	Sprite::GetInstance().Draw(SPRITE_ID::SPRITE_MENU_CURSOR, Vector2(330.0f + (cursorPos_ * 790), 650.0f), MathHelper::Abs(MathHelper::Sin((float)sinCount_)));
}

void DecisionMenu::end()
{
}

void DecisionMenu::decisionCheck()
{
	// �J�[�\��SE���Đ�
	Sound::GetInstance().PlaySE(SE_ID::DECISION_SE);

	switch (cursorPos_)
	{
	case 0:
		nextScene_ = afterScene_;
		isChangeScene_ = true;
		break;

	case 1:

		nextSubScene_ = beforeSubScene_;
		isChangeSubScene_ = true;
		break;
	}
}
