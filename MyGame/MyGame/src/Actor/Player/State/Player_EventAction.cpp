#include "Player_EventAction.h"
#include"../.../../../../Sound/Sound.h"
Player_EventAction::Player_EventAction(IWorld* world,ActorPtr player) :
	PlayerState(world,player)
{
}

void Player_EventAction::start()
{
	state_ = Player_State_ID::EventAction;
	player_->setAction(true);
	enemy_ = world_->findActor("Enemy");
}

void Player_EventAction::update(float deltaTime)
{
	if (InputChecker::GetInstance().KeyTriggerDown(Operation_Type::HIDE_BUTTON)) {
		nextState_ = Player_State_ID::Event_After;
	}
	if (InputChecker::GetInstance().KeyTriggerDown(Operation_Type::RETURN_VIEW_POINT_BUTTON)) {
		fpsCam_.eventReset();
	}
	fpsCam_.EventUpdate(player_->getPosition());//カメラのアップデート
}

void Player_EventAction::end()
{
	player_->setAction(false);
}
