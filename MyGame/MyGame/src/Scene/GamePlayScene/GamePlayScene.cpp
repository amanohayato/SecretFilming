#include "GamePlayScene.h"
#include "../../Actor/Actors.h"
#include "../../Graphic/Model.h"
#include "../../Field/FieldBase.h"
#include "../../Input/InputChecker.h"
#include "../../Define.h"
#include "../../Graphic/Sprite.h"
#include "../../Game/Time.h"
#include "../../UI/UIInclude.h"
#include "../../Sound/Sound.h"
#include "../../Actor/Object/HideObject.h"
#include "../../Actor/Object/Hide_InCamera.h"
#include "../../Camera/CaptureScreen.h"
#include "../Manager/GameDataManager.h"
#include "../../Actor/Enemy/Octopus.h"
#include "../../Actor/Object/Signal.h"
#include "../../Actor/Other/Confirm.h"
#include "../../Actor/Other/BgmChange.h"
#include "../../Actor/Other/IconControl.h"
#include "../../Event/EventManager/EventManager.h"
#include "../../Event/Event/Event.h"

#include "../SubScene/Menu/PauseMenu/PauseMunu.h"
#include "../SubScene/Menu/Option/Option.h"
#include "../SubScene/Menu/DecisionMenu/DecisionMenu.h"

#include "../../Actor/UIActor/MissionStart/MissionStart.h"

GamePlayScene::GamePlayScene():world_(),player_(nullptr)
{
	// �Ԑ����N���X�����[���h��
	cagm_.setWorld(&world_);

	// �ʍs�l�����N���X�����[���h��
	cigm_.setWorld(&world_);

	// �T�u�V�[���̎�ނ̓o�^
	states_[SubSceneType::PAUSE_MENU] = std::make_shared<PauseMunu>();
	states_[SubSceneType::OPTION] = std::make_shared<Option>(SubSceneType::PAUSE_MENU);
	states_[SubSceneType::DECISION_MENU] = std::make_shared<DecisionMenu>(SceneType::SCENE_ENTRANCE, SubSceneType::PAUSE_MENU, SPRITE_ID::SPRITE_ASK_RETURN_TITLE);
}

void GamePlayScene::start()
{
	// ���[���h�N���X������������
	world_.initialize();

	// �Ԑ����N���X������������
	cagm_.initialize();

	// �ʍs�l�����N���X������������
	cigm_.initialize();
	performance_.setWorld(&world_);
	
	// �}�b�v�f�[�^��ǂݍ���
	world_.loadMap("res/Data/map.csv", "res/Data/pathmap.csv");

	
	
	// �v���C���[�����[���h�ƃQ�[�����N���X�ɒǉ�
	player_ = std::make_shared<Player>(&world_, Vector3{ 764,11.5,880 }, Matrix{ Matrix::Identity *  Matrix::CreateRotationX(0) * Matrix::CreateRotationY(90) });
	world_.addActor(ActorGroup::PLAYER_ACTOR, player_);
	GameDataManager::getInstance().addAvoidTarget(player_);

	// �F���l�����[���h�ƃQ�[�����N���X�ɒǉ�
	std::shared_ptr<Octopus> enemy = std::make_shared<Octopus>(&world_, Vector3{ 850,10,880 });
	world_.addActor(ActorGroup::ENEMY_ACTOR, enemy);
	GameDataManager::getInstance().addAvoidTarget(enemy);
	

	world_.addActor(ActorGroup::SIGNAL_ACTOR, std::make_shared<Signal>(&world_));//�M��(��)
	world_.addActor(ActorGroup::UI_ACTOR, std::make_shared<Confirm>(&world_));//�m��x�Q�[�W
	world_.addActor(ActorGroup::UI_ACTOR, std::make_shared<BgmChange>(&world_));//BGM�؂�ւ��N���X
	world_.addActor(ActorGroup::UI_ACTOR, std::make_shared<IconControl>(&world_));//�A�C�R���؂�ւ��N���X
	world_.addActor(ActorGroup::UI_ACTOR, std::make_shared<MissionStart>());//�~�b�V�����X�^�[�g


	auto action = std::make_shared<Action>(&world_, Vector2{ WINDOW_WIDTH*1.0f,WINDOW_HEIGHT*1.0f });
	world_.addUI(action);
	Sound::GetInstance().PlayBGM(BGM_ID::SOUND_GAME,DX_PLAYTYPE_LOOP);
	Sound::GetInstance().SetBGMVolume(BGM_ID::SOUND_GAME, 1.0f);

	// �C�x���g�Ǘ��N���X��ǉ�
	mEventManager_ = new EventManager(world_);

	//mEventManager->AddEvent(EventManager::EventState::ZIHANKI_EVENT, new Event(mEventManager));
	//mEventManager->AddEvent(EventManager::EventState::KAIWA_EVENT, new Event(mEventManager));

	//mEventManager_->ChangeEvent(EventManager::EventState::ZIHANKI_EVENT);

	// ���C�g���̐ݒ�
	SetUseLighting(TRUE);
	SetLightEnable(TRUE);
	ChangeLightTypeDir(Vector3{ 0.0f,-1.0f,-0.5f });
	SetLightDifColor(GetColorF(0.5f, 0.5f, 0.5f, 0.5f));
	SetGlobalAmbientLight(GetColorF(0.2f, 0.2f, 0.2f, 0.2f));

	// �Q�[���̈ꎞ��~�t���O��؂�
	stopGame_ = false;

	Sound::GetInstance().SetEventListenerPos(player_->getPosition(), player_->getRotation().Forward());
	performance_.start();
	

}

void GamePlayScene::update(float deltaTime)
{

	Sound::GetInstance().SetEventListenerPos(player_->getPosition(), player_->getRotation().Forward());

	
	if (GameDataManager::getInstance().getGameStop() == true)
	{
		performance_.update(deltaTime);
		return;
	}

	if (stopGame_)
	{
		if (InputChecker::GetInstance().KeyTriggerDown(Operation_Type::PAUSE_BUTTON))
		{
			stopGame_ = false;
		}

		if (curState_->isChangeScene())
		{
			if (curState_->nextScene() == SceneType::SCENE_GAMEPLAY)
			{
				curState_ = states_[SubSceneType::PAUSE_MENU];
				stopGame_ = false;
			}
			else
			{
				next_ = curState_->nextScene();
				isEnd_ = true;
			}
		}

		if (curState_->isChangeSubScene())
		{
			changeState(curState_->nextSubScene());
		}

		// �G���g�����X�V�[���̏�Ԃ̍X�V
		curState_->update(deltaTime);
		return;
	}

	if (InputChecker::GetInstance().KeyTriggerDown(Operation_Type::PAUSE_BUTTON))
	{
		// �Z���N�gSE���Đ�
		Sound::GetInstance().PlaySE(SE_ID::DECISION_SE);

		changeState(SubSceneType::PAUSE_MENU);

		stopGame_ = true;
	}

	// �X�R�A�̒l���擾���R���\�[���ɉ��o��
	auto score = CaptureScreen::getInstance().getScore();
	GameDataManager::getInstance().setScore(score);
	OutputDebugString(("���v�X�R�A�F" + std::to_string(score) + "\n").c_str());

	// �o�b�N�{�^������͂��邩�A�G���S�[���n�_�ɒH�蒅������
	if (GameDataManager::getInstance().getEnemyGoal()||
		InputChecker::GetInstance().KeyTriggerDown(Operation_Type::DEBUG_CLEAR_BUTTON))
	{
		// �I���������s��
		isEnd_ = true;
		auto score = CaptureScreen::getInstance().getScore();
		GameDataManager::getInstance().setScore(score);
		next_ = SceneType::SCENE_RESULT;
	}

	// �Ԑ����N���X�̍X�V
	cagm_.update(deltaTime);

	// �ʍs�l�����N���X�̍X�V
	cigm_.update(deltaTime);

	// ���[���h�̍X�V
	world_.update(deltaTime);

	// �C�x���g�Ǘ��N���X�̍X�V
	mEventManager_->Update();
}

void GamePlayScene::draw() const
{

	// ���[���h�̕`��
	world_.draw();

	// �C�x���g�}�l�[�W���[�̕`��
	mEventManager_->Draw();

	// �^�C�}�[�N���X��FPS�̕`��֐����Ă�
	Time::GetInstance().draw_fps();
}

void GamePlayScene::lateDraw()
{

	// ���[���h�̌�`��
	world_.lateDraw();

	performance_.draw();

	if (stopGame_)
	{
		// �T�u�V�[���̕`��
		curState_->draw();
	}
	
}

void GamePlayScene::end()
{
	// �C�x���g�Ǘ��N���X�̍폜
	delete mEventManager_;

	// ���[���h�̏I���֐����Ă�
	world_.end();

	// BGM���~�߂�
	Sound::GetInstance().StopBGM();
}

void GamePlayScene::changeState(SubSceneType next)
{
	if (curState_ != nullptr) curState_->end();
	curState_ = states_[next];
	curState_->start();
}
