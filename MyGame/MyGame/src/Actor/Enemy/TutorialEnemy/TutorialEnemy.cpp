#include "TutorialEnemy.h"
#include "../../../World/World.h"

TutorialEnemy::TutorialEnemy(IWorld * world, const Vector3 & position, const IBodyPtr & body)
	: EnemyBase(world, position, body)
{
	activeStopTimer_ = false;
	inactiveAwareness_ = false;

	stopTimer_ = 0.0f;

	displayWarningText_ = false;
}

void TutorialEnemy::update(float delta_time_)
{
	stopTimer_ -= delta_time_;

	if (stopTimer_ < 0.0f) stopTimer_ = 0.0f;

	if (activeStopTimer_ && stopTimer_ <= 0.0f) 
	{
		is_event_ = true;
		activeStopTimer_ = false;
	}

	EnemyBase::update(delta_time_);

	if (inactiveAwareness_)
	{
		awareness_ = 0;
	}
}

void TutorialEnemy::onCollide(Actor & other)
{
	if (other.isAction()) return;
	if (other.getName() == "Player" || other.getName() == "Car")
	{
		// 自分からプレーヤーへの方向ベクトル
		Vector3 direction_to_player = other.getPosition() - position_;

		other.receiveMessage(EventMessage::Hit_Enemy, (void*)&direction_to_player);

		on_Barrier(world_->findActor(other.getName()), world_->findActor("Enemy"));
	}
	if (other.getName() == "Player") {
		change_state(EnemyState::DiscoveryStart);
	}
}



void TutorialEnemy::changeSpeed(float normal_speed, float escape_speed)
{
	normal_speed_ = normal_speed;
	escape_speed_ = escape_speed;
}

void TutorialEnemy::changeTimer(float timer)
{
	awareness_timer_ = timer;
}

void TutorialEnemy::changeRandomEventFlag(bool flag)
{
	randomEventFlag_ = flag;
}

void TutorialEnemy::setTutorialMovePoint()
{
	EventPoint temp;

	for each (EventPoint eventPoint in event_points_)
	{
		if (eventPoint.block_ == 1)
		{
			temp = eventPoint;
		}
	}

	event_points_.clear();

	event_points_.push_back(temp);
	
	//マンホール用のやつ
	if (event_points_.front().building_.lock()->getEvent() == EventType::EVENT_MANHORU) {
		auto path1 = world_->getWalkMap().find_path(0, position_, event_points_.front().position_);
		auto path2 = world_->getWalkMap().find_path(0, position_, event_points_.front().position2_);
		path_ = GetNearPath(path1, path2);
	}
	else
		path_ = world_->getWalkMap().find_path(0, position_, event_points_.front().position_);

}

void TutorialEnemy::setStopTimer(float value)
{
	activeStopTimer_ = true;
	stopTimer_ = value;
}

void TutorialEnemy::InactiveStopTimer()
{
	activeStopTimer_ = false;
	stopTimer_ = 0.0f;
}

void TutorialEnemy::SetInactiveAwareness(bool flag)
{
	inactiveAwareness_ = flag;
}
