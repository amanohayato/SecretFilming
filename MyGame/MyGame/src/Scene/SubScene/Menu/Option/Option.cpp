#include "Option.h"
#include"../../../../Input/InputChecker.h"
#include"../../../../Graphic/Sprite.h"
#include"../../../../Sound/Sound.h"
#include"../../../Manager/GameDataManager.h"

Option::Option(SubSceneType nextSubScene)
{
	nextSubScene_ = nextSubScene;
}

void Option::start()
{
	baseInit();

	// ���݂̃J�������x���擾
	cameraSens_ = (int)(GameDataManager::getInstance().getCameraSens() * 10.f);

	// ���݂�BGM���ʂ��擾
	bgmVolume_ = (int)(Sound::GetInstance().IsAllBGMVolume() * 10.f);

	// ���݂�SE���ʂ��擾
	seVolume_ = (int)(Sound::GetInstance().IsAllSEVolume() * 10.f);

	menuSize_ = 4;
}

void Option::update(float deltaTime)
{
	// �_�ŃJ�E���g�̍X�V
	sinCount_ = (sinCount_ + 1) % 360;

	bool isLongPress = false;

	// �X�e�B�b�N����ɌX���n�߂���
	if (InputChecker::GetInstance().KeyTriggerDown(Operation_Type::STICK_UP)) moveCursor(-1);
	// �X�e�B�b�N�����ɌX���n�߂���
	if (InputChecker::GetInstance().KeyTriggerDown(Operation_Type::STICK_DOWN)) moveCursor(1);

	// �X�e�B�b�N�����ɌX������
	if (InputChecker::GetInstance().KeyStateDown(Operation_Type::STICK_LEFT))
	{
		isLongPress = true;

		if (isHighSpeedMove_)
		{
			changeParameter(-1);
		}
		else if (InputChecker::GetInstance().KeyTriggerDown(Operation_Type::STICK_LEFT))
		{
			changeParameter(-1);
		}
	}
	// �X�e�B�b�N���E�ɌX������
	if (InputChecker::GetInstance().KeyStateDown(Operation_Type::STICK_RIGHT))
	{
		isLongPress = true;

		if (isHighSpeedMove_)
		{
			changeParameter(1);
		}
		else if (InputChecker::GetInstance().KeyTriggerDown(Operation_Type::STICK_RIGHT))
		{
			changeParameter(1);
		}
	}
	
	// ����{�^������������
	if (InputChecker::GetInstance().KeyTriggerDown(Operation_Type::DECISION_BUTTON)) decisionCheck();

	if (isLongPress)
	{
		longPressTimer_ += deltaTime;

		if (longPressTimer_ > longPressTime_)
		{
			isHighSpeedMove_ = true;
		}
	}
	else
	{
		longPressTimer_ = 0.0f;
		isHighSpeedMove_ = false;
	}
}

void Option::draw() const
{
	// �w�i���Â�����摜��`��
	Sprite::GetInstance().Draw(SPRITE_ID::SPRITE_BLIND, Vector2::Zero);

	// �w�i�摜�̕`��
	Sprite::GetInstance().Draw(SPRITE_ID::SPRITE_GO_TO_OPTION, Vector2(560.f, 100.f));

	// ���j���[���ځg�J�������x�ݒ�h�̉摜�̕`��
	Sprite::GetInstance().Draw(SPRITE_ID::SPRITE_OPTION_CAMERA_SENSITIVITY, Vector2(140.f, 400.f));

	// ���j���[���ځgBGM���ʐݒ�h�̉摜�̕`��
	Sprite::GetInstance().Draw(SPRITE_ID::SPRITE_OPTION_BGM_VOLUME, Vector2(140.f, 570.f));

	// ���j���[���ځgSE���ʐݒ�h�̉摜�̕`��
	Sprite::GetInstance().Draw(SPRITE_ID::SPRITE_OPTION_SE_VOLUME, Vector2(140.f, 740.f));

	// ���j���[���ځg���j���[�֖߂�h�̉摜�̕`��
	Sprite::GetInstance().Draw(SPRITE_ID::SPRITE_EXIT , Vector2(140.f, 910.f));

	for (int i = 0; i < 3; i++)
	{
		Sprite::GetInstance().Draw(SPRITE_ID::SPRITE_OPTION_FLAME, Vector2(740.f, 470.f + ((float)i * 170.f)));
	}
	
	for (int i = 0; i < cameraSens_; i++)
	{
		Sprite::GetInstance().SplitDraw(SPRITE_ID::SPRITE_OPTION_BAR, Vector2(740.f + ((float)i * 100.f), 470.f + (0.f * 170.f)), i);
	}
	Sprite::GetInstance().Draw(SPRITE_ID::SPRITE_OPTION_CURSOR, Vector2(640.f + ((float)cameraSens_ * 100.f), 400.f + (0.f * 170.f)));

	for (int i = 0; i < bgmVolume_; i++)
	{
		Sprite::GetInstance().SplitDraw(SPRITE_ID::SPRITE_OPTION_BAR, Vector2(740.f + ((float)i * 100.f), 470.f + (1.f * 170.f)), i);
	}
	Sprite::GetInstance().Draw(SPRITE_ID::SPRITE_OPTION_CURSOR, Vector2(640.f + ((float)bgmVolume_ * 100.f), 400.f + (1.f * 170.f)));

	for (int i = 0; i < seVolume_; i++)
	{
		Sprite::GetInstance().SplitDraw(SPRITE_ID::SPRITE_OPTION_BAR, Vector2(740.f + ((float)i * 100.f), 470.f + (2.f * 170.f)), i);
	}
	Sprite::GetInstance().Draw(SPRITE_ID::SPRITE_OPTION_CURSOR, Vector2(640.f + ((float)seVolume_ * 100.f), 400.f + (2.f * 170.f)));

	Sprite::GetInstance().Draw(SPRITE_ID::SPRITE_MENU_CURSOR, Vector2(40.f, 400.f + ((float)cursorPos_ * 170.f)));
}

void Option::end()
{
}

void Option::decisionCheck()
{
	if (cursorPos_ == 3)
	{
		// �J�[�\��SE���Đ�
		Sound::GetInstance().PlaySE(SE_ID::DECISION_SE);

		isChangeSubScene_ = true;
	}
}

void Option::changeParameter(int value)
{
	// �Z���N�gSE���Đ�
	Sound::GetInstance().PlaySE(SE_ID::CURSOR_MOVE_SE);

	// �J�[�\���ʒu�ɂ���ĕ���
	switch (cursorPos_)
	{
		// �J�[�\���ʒu���g�J�������x�ݒ�h��������
	case 0:

		// �J�������x��ቺ
		cameraSens_ += value;
		if (cameraSens_ < 1) cameraSens_ = 1;
		if (cameraSens_ > 10) cameraSens_ = 10;

		// ���ۂɃJ�������x��ύX
		GameDataManager::getInstance().setCameraSens((float)cameraSens_ / 10);

		break;

		// �J�[�\���ʒu���gBGM���ʐݒ�h��������
	case 1:

		// BGM���ʂ�ቺ
		bgmVolume_ += value;
		if (bgmVolume_ < 1) bgmVolume_ = 1;
		if (bgmVolume_ > 10) bgmVolume_ = 10;

		// ���ۂ�BGM�̉��ʂ�ύX
		Sound::GetInstance().SetAllBGMVolume((float)bgmVolume_ / 10);

		break;

		// �J�[�\���ʒu���gSE���ʐݒ�h��������
	case 2:

		// SE���ʂ�ቺ
		seVolume_ += value;
		if (seVolume_ < 1) seVolume_ = 1;
		if (seVolume_ > 10) seVolume_ = 10;

		// ���ۂ�SE�̉��ʂ�ύX
		Sound::GetInstance().SetAllSEVolume((float)seVolume_ / 10);

		break;

	default:
		break;
	}
}