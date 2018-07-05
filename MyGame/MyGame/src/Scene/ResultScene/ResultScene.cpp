#include "ResultScene.h"
#include"../../Graphic/DebugDraw.h"
#include"../../Graphic/Sprite.h"
#include"../../Define.h"
#include"../../Input/InputChecker.h"
#include"../../Sound/Sound.h"
#include"../../Math/MathHelper.h"
#include"../Manager/GameDataManager.h"
#include"../../Camera/CaptureScreen.h"
#include"../../Graphic/DrawNumber.h"


ResultScene::ResultScene()
{
	displayPhoto_ = std::make_shared<DisplayPhoto>();
	scoreSheet_ = std::make_shared<ScoreSheet>();
	decisionMenu_ = std::make_shared<DecisionMenu>(SceneType::SCENE_GAMEPLAY, SubSceneType::NONE, SPRITE_ID::Game_over_retry_UI);
}

void ResultScene::start()
{
	// ��{�̏������֐����Ă�
	baseInit();

	// �Q�[�����N���A�������̏����擾����
	isClear_ = (GameDataManager::getInstance().getScore() >= 100);

	// ���j���[�\���t���O��؂�
	displayMenu_ = false;

	isStamp_ = false;

	// ���̃V�[�����g�G���g�����X�V�[���h�ɃZ�b�g����
	next_ = SceneType::SCENE_ENTRANCE;

	// ���U���gBGM���Đ�
	Sound::GetInstance().PlayBGM(BGM_ID::SOUND_RESULT, DX_PLAYTYPE_LOOP);

	displayPhoto_->start();
	scoreSheet_->start();
	decisionMenu_->start();
}

void ResultScene::update(float deltaTime)
{
	// �_�ŃJ�E���g�̍X�V
	sinCount_ = (sinCount_ + 10) % 360;

	displayPhoto_->update(deltaTime);
	scoreSheet_->update(deltaTime);

	if (displayMenu_)
	{
		decisionMenu_->update(deltaTime);

		if (decisionMenu_->isChangeScene())
		{
			next_ = decisionMenu_->nextScene();
			isEnd_ = true;
		}

		if (decisionMenu_->isChangeSubScene())
		{
			next_ = SceneType::SCENE_ENTRANCE;
			isEnd_ = true;
		}
	}

	if (isStamp_)
	{
		if (InputChecker::GetInstance().KeyTriggerDown(Operation_Type::ANY_BUTTON))
		{
			if (isClear_)
			{
				// ���̃V�[�����g�G���g�����X�V�[���h�ɃZ�b�g����
				next_ = SceneType::SCENE_ENTRANCE;
				isEnd_ = true;
			}
			else
			{
				displayMenu_ = true;
			}
		}
	}
	else
	{
		if (displayPhoto_->isEndAnimation())
		{
			displayPhoto_->stampStart();
			scoreSheet_->stampStart();

			isStamp_ = true;
		}
	}

	
}

void ResultScene::draw() const
{
	Sprite::GetInstance().Draw(SPRITE_ID::SPRITE_RESULT_BG, Vector2::Zero);
	

	if (isClear_)
	{
		// �Q�[���N���A�̃��S�̕`��
		Sprite::GetInstance().Draw(SPRITE_ID::SPRITE_GAME_CLEAR_UI , Vector2(100.0f, 110.0f));
		Sprite::GetInstance().Draw(SPRITE_ID::A_Lot_Of_Coin_ , Vector2(1280.0f, 70.0f));
	}
	else
	{
		// �Q�[���I�[�o�[�̃��S�̕`��
		Sprite::GetInstance().Draw(SPRITE_ID::SPRITE_GAME_OVER_UI, Vector2(100.0f, 110.0f));
		Sprite::GetInstance().Draw(SPRITE_ID::Less_Coin_, Vector2(1380.0f, 20.0f));
	}
	displayPhoto_->draw();
	scoreSheet_->draw();

	if (displayMenu_)
	{
		// �gPLESS_ANY_BUTTON�h�Ə����ꂽ���S�̕`��
		Sprite::GetInstance().Draw(SPRITE_ID::SPRITE_PRESS_ANY_BUTTON_UI, Vector2(670.0f, 750.0f), MathHelper::Abs(MathHelper::Sin((float)sinCount_)));

		decisionMenu_->draw();
	}

	//// �g���g���C�h�Ə����ꂽ���S + �w�i���Â�����摜�̕`��
	//Sprite::GetInstance().Draw(SPRITE_ID::Game_over_retry_UI, Vector2::Zero);

	//// �g�͂��h�Ə����ꂽ���S�̕`��
	//Sprite::GetInstance().Draw(SPRITE_ID::SPRITE_YES_UI, Vector2(450.0f, 640.0f));

	//// �g�������h�Ə����ꂽ���S�̕`��
	//Sprite::GetInstance().Draw(SPRITE_ID::SPRITE_NO_UI, Vector2(1240.0f, 640.0f));

	//// ���j���[�J�[�\���̕`��
	//Sprite::GetInstance().Draw(SPRITE_ID::SPRITE_MENU_CURSOR, Vector2(330.0f + (cursorPos_ * 790), 650.0f), MathHelper::Abs(MathHelper::Sin((float)sinCount_)));
}

void ResultScene::end()
{
	displayPhoto_->end();
	scoreSheet_->end();
	decisionMenu_->end();

	// ���C�����j���[��BGM���~����
	Sound::GetInstance().StopBGM();
}
