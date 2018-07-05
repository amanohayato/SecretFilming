#include "Title.h"
#include"../../../Input/InputChecker.h"
#include"../../../Graphic/Sprite.h"
#include"../../../Math/MathHelper.h"
#include"../../../Sound/Sound.h"

Title::Title()
{
}

void Title::start()
{
	baseInit();
}

void Title::update(float deltaTime)
{
	// �_�ŃJ�E���g�̍X�V
	sinCount_ = (sinCount_ + 10) % 360;

	// �����ꂩ�̓��͂���������
	if (InputChecker::GetInstance().KeyTriggerDown(Operation_Type::ANY_BUTTON)) {

		// �Z���N�gSE���Đ�
		Sound::GetInstance().PlaySE_IsNotPlay(SE_ID::DECISION_SE);

		// ���C�����j���[�֔��
		nextSubScene_ = SubSceneType::MAIN_MENU;
		isChangeSubScene_ = true;
	}
}

void Title::draw() const
{
	// �^�C�g�����S�̕`��
	Sprite::GetInstance().Draw(SPRITE_ID::SPRITE_TITLELOGO, Vector2(220, 30));

	// �^�C�g�����S�̕`��
	Sprite::GetInstance().Draw(SPRITE_ID::SPRITE_SOZAI_TEIKYOU_TEXT, Vector2(1600, 1000));

	// �gPLESS_ANY_BUTTON�h�Ə����ꂽ���S�̕`��
	Sprite::GetInstance().Draw(SPRITE_ID::SPRITE_PRESS_ANY_BUTTON_UI, Vector2(340.0f, 680.0f), MathHelper::Abs(MathHelper::Sin((float)sinCount_)));
}

void Title::end()
{
}
