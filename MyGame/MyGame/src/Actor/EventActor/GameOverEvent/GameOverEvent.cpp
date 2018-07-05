#include "GameOverEvent.h"
#include "GameOverUfo.h"
#include "GameOverUfo.h"
#include"../../../Scene/Manager/GameDataManager.h"

#include"../../../Sound/Sound.h"
#include"../../Player/Player.h"

// �Q�[���I�[�o�[�C�x���g�N���X
// �S���FHo Siu Ki�i�����Q�j
// �Q�l�FActor/EventActor/GameClearEvent.cpp

// �R���X�g���N�^
GameOverEvent::GameOverEvent(IWorld* world, float goal_timer, const float goal_time, std::weak_ptr<EnemyBase> enemy) :
	goal_timer_(goal_timer), goal_time_(goal_time), enemy_(enemy)
{
	world_ = world;
}

// ������
void GameOverEvent::initialize()
{
	createUFOfunc_ = [&] {
		std::shared_ptr<GameOverUfo> ufo = std::make_shared<GameOverUfo>(world_, Vector3::Zero, Vector3{ world_->findActor("Enemy")->getPosition() });
		world_->addActor(ActorGroup::EVENT_ACTOR, ufo);
		ufo->setTarget(world_->findActor("Enemy"));
		ufo->begin();
	};
	Sound::GetInstance().StopBGM();
	Sound::GetInstance().StopSE(SE_ID::RUN_SE);
	Sound::GetInstance().PlayBGM(BGM_ID::SOUND_GAMEOVER, DX_PLAYTYPE_LOOP);

	InputChecker::GetInstance().ChangeActive(Operation_Type::DASH_BUTTON, false);
	InputChecker::GetInstance().ChangeActive(Operation_Type::HIDE_BUTTON, false);
	InputChecker::GetInstance().ChangeActive(Operation_Type::HOLD_CAMERA_BUTTON, false);
	InputChecker::GetInstance().ChangeActive(Operation_Type::PAUSE_BUTTON, false);
	InputChecker::GetInstance().ChangeActive(Operation_Type::PLAYER_MOVE_STICK, false);
	InputChecker::GetInstance().ChangeActive(Operation_Type::RETURN_VIEW_POINT_BUTTON, false);
	InputChecker::GetInstance().ChangeActive(Operation_Type::SHOW_MAP_BUTTON, false);
	InputChecker::GetInstance().ChangeActive(Operation_Type::TAKE_SHUTTER_BUTTON, false);
}

// �X�V
void GameOverEvent::update(float delta_time)
{
	//InputChecker::GetInstance().InputStop();


	auto player=std::static_pointer_cast<Player>(world_->findActor("Player"));
	player->getFPSCamera().StartUpdate(camerapos_, Matrix::CreateRotationY(180));
	// ��񂾂��C�x���g�p�̃A�N�^�[�𐶐�
	if (goal_timer_ <= goal_time_)
	{
		createUFOfunc_();
		createUFOfunc_ = [] {};
	}

	// �C�x���g�Ɋ֌W�Ȃ��A�N�^�[���폜
	auto citizenlist = GameDataManager::getInstance().getCitizenList();	// �ʍs�l
	auto carlist = GameDataManager::getInstance().getCarList();			// ��
	for (auto& at : citizenlist)
	{
		at.lock()->dead();
		GameDataManager::getInstance().removeCitizenList(at.lock()->shared_from_this());	// �����Ă���s���̃|�C���^���i�[���Ă郊�X�g���玩�g���폜
	}
	for (auto& at : carlist)
	{
		at.lock()->dead();
		GameDataManager::getInstance().removeCarList(at.lock()->shared_from_this());		// �����Ă���Ԃ̃|�C���^���i�[���Ă郊�X�g���玩�g���폜
	}

	// �C�x���g�̏���
	

	// �C�x���g�^�C�}�[�����Z
	goal_timer_ -= delta_time;


	if (goal_timer_ <= 0.0f)
	{
		// BGM���~�߂�
		Sound::GetInstance().StopBGM();

		InputChecker::GetInstance().ChangeActive(Operation_Type::DASH_BUTTON, true);
		InputChecker::GetInstance().ChangeActive(Operation_Type::HIDE_BUTTON, true);
		InputChecker::GetInstance().ChangeActive(Operation_Type::HOLD_CAMERA_BUTTON, true);
		InputChecker::GetInstance().ChangeActive(Operation_Type::PAUSE_BUTTON, true);
		InputChecker::GetInstance().ChangeActive(Operation_Type::PLAYER_MOVE_STICK, true);
		InputChecker::GetInstance().ChangeActive(Operation_Type::RETURN_VIEW_POINT_BUTTON, true);
		InputChecker::GetInstance().ChangeActive(Operation_Type::SHOW_MAP_BUTTON, true);
		InputChecker::GetInstance().ChangeActive(Operation_Type::TAKE_SHUTTER_BUTTON, true);
	}
}

// �`��
void GameOverEvent::draw() const
{

}
