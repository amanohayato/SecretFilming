#include "EntranceScene.h"
#include "../../Sound/Sound.h"
#include "../../Graphic/Sprite.h"
#include "../../Define.h"
#include <DxLib.h>
#include "../../Actor/Actors.h"
#include "../../Actor/TitleCamera/TitleCamera.h"
#include "../../Actor/TitleActor/TitleUfo/TitleUfoFactory.h"

#include"../SubScene/Title/Title.h"
#include"../SubScene/Menu/MainMenu/MainMenu.h"
#include"../SubScene/Menu/Option/Option.h"

EntranceScene::EntranceScene()
{
	// �Ԑ����N���X�����[���h��
	cagm_.setWorld(&world_);

	// �ʍs�l�����N���X�����[���h��
	cigm_.setWorld(&world_);

	subScenes_[SubSceneType::TITLE] = std::make_shared<Title>();
	subScenes_[SubSceneType::MAIN_MENU] = std::make_shared<MainMenu>();
	subScenes_[SubSceneType::OPTION] = std::make_shared<Option>(SubSceneType::MAIN_MENU);
}

void EntranceScene::start()
{
	// �o�ߎ��Ԃ��N���A
	elapsedTime_ = 0;

	// ���[���h�N���X������������
	world_.initialize();

	// �}�b�v�f�[�^��ǂݍ���
	world_.loadMap("res/Data/map.csv", "res/Data/pathmap.csv");

	// �E�F�C�|�C���g��ǂݍ���
	world_.addWalkPoint("res/Data/waypoint.csv", "res/Data/enemywalkedge.csv");

	// �^�C�g���p��]�J���������[���h�ɒǉ�
	titleCamera_ = std::make_shared<TitleCamera>(&world_, Vector3::Zero);
	world_.addActor(ActorGroup::UI_ACTOR, titleCamera_);

	// �^�C�g���pUFO�쐬�N���X��ǉ�
	titleUfoFactory_ = std::make_shared<TitleUfoFactory>(&world_);
	world_.addActor(ActorGroup::UI_ACTOR, titleUfoFactory_);

	// ��{�̏������֐����Ă�
	baseInit();

	// ���̃V�[�����Q�[���v���C���ɕς���
	next_ = SceneType::SCENE_GAMEPLAY;

	// �G���g�����X�V�[����BGM��炷
	Sound::GetInstance().PlayBGM(BGM_ID::SOUND_TITLE, DX_PLAYTYPE_LOOP);

	// ���݂̏�Ԃ��^�C�g���ɂ���
	changeState(SubSceneType::TITLE);

	transitionsAnimeType_ = TransitionsAnimeType::FadeAnimation;
}

void EntranceScene::update(float deltaTime)
{
	// �o�ߎ��Ԃ̍X�V
	elapsedTime_ += deltaTime;

	// ��������̃L�[���͂����邩�I�v�V�����V�[����������A�o�ߎ��Ԃ��[���ɂ���
	if (InputChecker::GetInstance().KeyStateDown(Operation_Type::ANY_BUTTON) || curSubScene_ == subScenes_[SubSceneType::OPTION])
	{
		elapsedTime_ = 0;
	}

	// ���[���h�̍X�V
	world_.update(deltaTime);

	// �f�����[�r�[�V�[���ւ̈ڍs�����������Ă�����
	if (elapsedTime_ > goDemoSceneTime_)
	{
		// ���̃V�[�����g�f�����[�r�[�V�[���h�ɃZ�b�g����
		//next_ = SceneType::SCENE_DEMOMOVIE;

		// ���̃V�[���̏I��������On�ɂ���
		//isEnd_ = true;
	}

	// 
	if (curSubScene_->isChangeScene())
	{
		 
		next_ = curSubScene_->nextScene();

		// ���̃V�[���̏I��������On�ɂ���
		isEnd_ = true;
	}

	// 
	if (curSubScene_->isChangeSubScene())
	{
		changeState(curSubScene_->nextSubScene());
	}

	isGameEnd_ = curSubScene_->isGameEnd();

	// �G���g�����X�V�[���̏�Ԃ̍X�V
	curSubScene_->update(deltaTime);
}

void EntranceScene::draw() const
{
	// ���[���h�̕`��
	world_.draw();

	// �G���g�����X�V�[���̏�Ԃ̕`��
	curSubScene_->draw();
}

void EntranceScene::lateDraw()
{
	// ���[���h�̌�`��
	world_.lateDraw();
}

void EntranceScene::end()
{
	// ���[���h�̏I���֐����Ă�
	world_.end();

	Sound::GetInstance().StopBGM();
}

void EntranceScene::changeState(SubSceneType next)
{
	if (curSubScene_ != nullptr) curSubScene_->end();
	curSubScene_ = subScenes_[next];
	curSubScene_->start();
}
