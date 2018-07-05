#include "GameClearEvent.h"
#include"../../../Actor/EventActor/Police/EventPolice.h"
#include "../../../Scene/Manager/GameDataManager.h"
#include"../../../Sound/Sound.h"
#include"../../Player/Player.h"


GameClearEvent::GameClearEvent(IWorld * world, float goal_timer, const float goal_time, std::weak_ptr<EnemyBase> enemy):goal_timer_(goal_timer),goal_time_(goal_time),enemy_(enemy)
{
	world_ = world;
}

void GameClearEvent::initialize()
{
	Sound::GetInstance().StopSE(SE_ID::RUN_SE);
	Sound::GetInstance().PlaySE(SE_ID::SIREN_SE, DX_PLAYTYPE_LOOP);
	Sound::GetInstance().StopBGM();
	Sound::GetInstance().PlayBGM(BGM_ID::SOUND_GAMECLEAR, DX_PLAYTYPE_LOOP);
	world_->addActor(ActorGroup::POLICE_ACTOR, std::make_shared<EventPolice>(world_, MODEL_ID::MODEL_POLICE_RUN, 0));
	world_->addActor(ActorGroup::POLICE_ACTOR, std::make_shared<EventPolice>(world_, MODEL_ID::MODEL_POLICE_RUN, 1));
	world_->addActor(ActorGroup::POLICE_ACTOR, std::make_shared<EventPolice>(world_, MODEL_ID::MODEL_POLICE_RUN, 2));
	world_->addActor(ActorGroup::POLICE_ACTOR, std::make_shared<EventPolice>(world_, MODEL_ID::MODEL_POLICE_RUN, 3));
	world_->addActor(ActorGroup::POLICE_ACTOR, std::make_shared<EventPolice>(world_, MODEL_ID::MODEL_POLICE_RUN, 4));
	world_->addActor(ActorGroup::POLICE_ACTOR, std::make_shared<EventPolice>(world_, MODEL_ID::MODEL_POLICE_RUN, 5));

	InputChecker::GetInstance().ChangeActive(Operation_Type::DASH_BUTTON, false);
	InputChecker::GetInstance().ChangeActive(Operation_Type::HIDE_BUTTON, false);
	InputChecker::GetInstance().ChangeActive(Operation_Type::HOLD_CAMERA_BUTTON, false);
	InputChecker::GetInstance().ChangeActive(Operation_Type::PAUSE_BUTTON, false);
	InputChecker::GetInstance().ChangeActive(Operation_Type::PLAYER_MOVE_STICK, false);
	InputChecker::GetInstance().ChangeActive(Operation_Type::RETURN_VIEW_POINT_BUTTON, false);
	InputChecker::GetInstance().ChangeActive(Operation_Type::SHOW_MAP_BUTTON, false);
	InputChecker::GetInstance().ChangeActive(Operation_Type::TAKE_SHUTTER_BUTTON, false);
}

void GameClearEvent::update(float delta_time)
{
	//���͂��󂯕t���Ȃ�����
	//InputChecker::GetInstance().InputStop();


	Sound::GetInstance().SetSEVolume(SE_ID::SIREN_SE, sirenvol_);
	goal_timer_ -= delta_time;
	sirenvol_ = 1.5f - goal_timer_/goal_time_;//�i�XSE�{�����[����傫������

	Matrix result{ Matrix::Identity };
	auto player = std::static_pointer_cast<Player>(world_->findActor("Player"));
	player->getFPSCamera().StartUpdate(camerapos_, Matrix::CreateRotationY(180));
	//playerstate_.getFPSCam().StartUpdate(camerapos_, Matrix::CreateFromAxisAngle(result.Up(), 180));
	
	car_ci_dead();
	if (goal_timer_ <= 3.0f)
	enemy_.lock()->set_awareness(100.0f);//�r�b�N���}�[�N��\��
	//�S�[���^�C����0�ȉ��ɂȂ�����T�C����SE���~�߂�
	if (goal_timer_ <= 0.0f)
	{
		Sound::GetInstance().StopSE();
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

void GameClearEvent::draw() const
{

}

void GameClearEvent::car_ci_dead()
{
	//�s���ƎԂ�ActorPtr���擾
	auto citizenlist = GameDataManager::getInstance().getCitizenList();
	auto carlist = GameDataManager::getInstance().getCarList();
	//�S�ď���
	for (auto& at : citizenlist)
	{
		at.lock()->dead();
		GameDataManager::getInstance().removeCitizenList(at.lock()->shared_from_this());//�����Ă���s���̃|�C���^���i�[���Ă郊�X�g���玩�g���폜
	}
	for (auto& at : carlist)
	{
		at.lock()->dead();
		GameDataManager::getInstance().removeCarList(at.lock()->shared_from_this());//�����Ă���Ԃ̃|�C���^���i�[���Ă郊�X�g���玩�g���폜
	}
}
