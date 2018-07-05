#include "TutorialScene.h"
#include "../../Sound/Sound.h"
#include "../../Camera/CaptureScreen.h"
#include "../../Graphic/Sprite.h"
#include "../../Game/Time.h"
#include "../../UI/UIInclude.h"
#include "../../Define.h"
#include "../../Actor/Actors.h"
#include "../../Actor/Enemy/TutorialEnemy/TutorialEnemy.h"
#include "../../Actor/TitleCamera/TitleCamera.h"
#include "../../Actor/TitleActor/TitleUfo/TitleUfoFactory.h"
#include "../../Actor/Other/Confirm.h"
#include "../../Actor/Other/IconControl.h"
#include "../Manager/GameDataManager.h"
#include "TutorialCommand/TutorialCommand.h"
#include "TutorialCommand/TutorialCommands.h"
#include <DxLib.h>

TutorialScene::TutorialScene()
{
	// �Ԑ����N���X�����[���h��
	cagm_.setWorld(&world_);

	// �ʍs�l�����N���X�����[���h��
	cigm_.setWorld(&world_);
}

void TutorialScene::start()
{
	// ��ʎB�e�N���X������������
	CaptureScreen::getInstance().clear();

	// ���[���h�N���X������������
	world_.initialize();

	// �Ԑ����N���X������������
	cagm_.initialize();

	// �ʍs�l�����N���X������������
	cigm_.initialize();

	// �}�b�v�f�[�^��ǂݍ���
	world_.loadMap("res/Data/map.csv", "res/Data/pathmap.csv");


	player_ = std::make_shared<Player>(&world_, Vector3{ (16.5f * 44), 11.5f, (16.5f * 57) }, Matrix{ Matrix::Identity *  Matrix::CreateRotationX(0) * Matrix::CreateRotationY(180) });
	world_.addActor(ActorGroup::PLAYER_ACTOR, player_);
	GameDataManager::getInstance().addAvoidTarget(player_);

	// �F���l�����[���h�ƃQ�[�����N���X�ɒǉ�
	enemy_ = std::make_shared<TutorialEnemy>(&world_, Vector3{ (16.5f * 44), 10, (16.5f * 55) });
	world_.addActor(ActorGroup::ENEMY_ACTOR, enemy_);
	GameDataManager::getInstance().addAvoidTarget(enemy_);

	world_.addActor(ActorGroup::UI_ACTOR, std::make_shared<Confirm>(&world_));//�m��x�Q�[�W
	world_.addActor(ActorGroup::UI_ACTOR, std::make_shared<IconControl>(&world_));//�A�C�R���؂�ւ��N���X

	auto action = std::make_shared<Action>(&world_, Vector2{ WINDOW_WIDTH*1.0f,WINDOW_HEIGHT*1.0f });
	world_.addUI(action);

	// ���C�g���̐ݒ�
	SetUseLighting(TRUE);
	SetLightEnable(TRUE);
	ChangeLightTypeDir(Vector3{ 0.0f,-1.0f,-0.5f });
	SetLightDifColor(GetColorF(0.5f, 0.5f, 0.5f, 0.5f));
	SetGlobalAmbientLight(GetColorF(0.2f, 0.2f, 0.2f, 0.2f));

	// ���݂̃R�}���h�ԍ���������
	curIndex_ = 0;

	// 
	setTutorialCommand();

	// �ŏ��̃R�}���h�̊J�n�֐�
	commandList_[curIndex_]->start();

	transitionsAnimeType_ = TransitionsAnimeType::FadeAnimation;

	Sound::GetInstance().PlayBGM(BGM_ID::SOUND_TUTORIAL, DX_PLAYTYPE_LOOP);
}

void TutorialScene::update(float deltaTime)
{
	// �_�ŃJ�E���g�̍X�V
	sinCount_ = (sinCount_ + 2) % 360;

	auto score = CaptureScreen::getInstance().getScore();
	GameDataManager::getInstance().setScore(score);

	//// �Ԑ����N���X�̍X�V
	//cagm_.update(deltaTime);

	//// �ʍs�l�����N���X�̍X�V
	//cigm_.update(deltaTime);

	// ���[���h�̍X�V
	world_.update(deltaTime);

	// �S�ẴR�}���h���I��������Q�[���v���C�V�[���ֈڍs
	if (InputChecker::GetInstance().KeyTriggerDown(Operation_Type::PAUSE_BUTTON) || curIndex_ >= commandList_.size())
	{
		InputChecker::GetInstance().ChangeActive(Operation_Type::PLAYER_MOVE_STICK, true);
		InputChecker::GetInstance().ChangeActive(Operation_Type::CHANGE_VIEW_POINT_STICK, true);
		InputChecker::GetInstance().ChangeActive(Operation_Type::HOLD_CAMERA_BUTTON, true);
		InputChecker::GetInstance().ChangeActive(Operation_Type::TAKE_SHUTTER_BUTTON, true);
		InputChecker::GetInstance().ChangeActive(Operation_Type::SHOW_MAP_BUTTON, true);
		InputChecker::GetInstance().ChangeActive(Operation_Type::DASH_BUTTON, true);
		InputChecker::GetInstance().ChangeActive(Operation_Type::HIDE_BUTTON, true);
		InputChecker::GetInstance().ChangeActive(Operation_Type::RETURN_VIEW_POINT_BUTTON, true);

		next_ = SceneType::SCENE_GAMEPLAY;
		isEnd_ = true;
	}
	else
	{
		// ���݂̃R�}���h�̍X�V
		commandList_[curIndex_]->update(deltaTime);

		// �I���t���O�������Ă����玟�̃R�}���h��
		if (commandList_[curIndex_]->isCommandEnd()) changeTutorialCommand();
	}
}

void TutorialScene::draw() const
{
	// ���[���h�̕`��
	world_.draw();

	// �^�C�}�[�N���X��FPS�̕`��֐����Ă�
	Time::GetInstance().draw_fps();
}

void TutorialScene::lateDraw()
{
	// ���[���h�̌�`��
	world_.lateDraw();

	// �S�ẴR�}���h���I�����Ă����炱�̊֐����I��
	if (curIndex_ >= commandList_.size()) return;

	// ���݂̃R�}���h�̕`��
	commandList_[curIndex_]->draw();

	Vector2 origin = Sprite::GetInstance().GetSize(SPRITE_ID::SPRITE_START_SKIP);
	origin *= 0.5f;

	constexpr float rate = 0.3f;
	Sprite::GetInstance().Draw(SPRITE_ID::SPRITE_START_SKIP, Vector2{ (float)WINDOW_WIDTH * 0.5f  ,origin.y*rate }, origin, MathHelper::Abs(MathHelper::Sin((float)sinCount_)), Vector2{ rate,rate },0.0f , true, false);
}

void TutorialScene::end()
{
	// ���[���h�̏I���֐����Ă�
	world_.end();

	// BGM���~�߂�
	Sound::GetInstance().StopBGM();
	Sound::GetInstance().StopSE();
}

void TutorialScene::setTutorialCommand()
{
	commandList_.clear();

	commandList_.push_back(std::make_shared<TutorialStart>(enemy_));
	commandList_.push_back(std::make_shared<DeterminationDescription>());
	commandList_.push_back(std::make_shared<LookAlien>());
	commandList_.push_back(std::make_shared<LookCameraIcon>(player_, enemy_));
	commandList_.push_back(std::make_shared<TakaShutter>(enemy_));
	commandList_.push_back(std::make_shared<ShootingSuccess>(player_, enemy_));
	commandList_.push_back(std::make_shared<AlienWarning>(enemy_));
	commandList_.push_back(std::make_shared<StartHide>(player_, enemy_));
	commandList_.push_back(std::make_shared<Hiding>(enemy_));
	commandList_.push_back(std::make_shared<LookAlertnessIcon>());
	commandList_.push_back(std::make_shared<EndHide>(player_, enemy_));
	commandList_.push_back(std::make_shared<ReturnViewPoint>(player_));
	commandList_.push_back(std::make_shared<ShowMap>(player_));
	commandList_.push_back(std::make_shared<LookMap>(enemy_));
	commandList_.push_back(std::make_shared<LookMapIconDescription>(enemy_));
	commandList_.push_back(std::make_shared<LookMapEnemyIcon>(enemy_));
	commandList_.push_back(std::make_shared<CloseMap>(player_, enemy_));
	commandList_.push_back(std::make_shared<Running>(player_, enemy_));
	commandList_.push_back(std::make_shared<SpecifiedPoint>());
	commandList_.push_back(std::make_shared<ReShowMap>(player_));
	commandList_.push_back(std::make_shared<LookSpecifiedPointIcon>());
	commandList_.push_back(std::make_shared<ReCloseMap>(player_));
	commandList_.push_back(std::make_shared<TutorialEnd>());
}

void TutorialScene::changeTutorialCommand()
{
	commandList_[curIndex_]->end();

	curIndex_++;

	// �S�ẴR�}���h���I�����Ă����炱�̊֐����I��
	if (curIndex_ >= commandList_.size()) return;

	commandList_[curIndex_]->start();
}
