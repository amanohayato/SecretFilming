#include "Player_Event_After.h"

Player_Event_After::Player_Event_After(ActorPtr player) :
	PlayerState(player)
{
}

void Player_Event_After::start()
{
	state_ = Player_State_ID::Event_After;
}

void Player_Event_After::update(float deltaTime)
{
	timer_ += deltaTime;
	if(timer_ > 0.5f) nextState_ = Player_State_ID::Idle;
	if (InputChecker::GetInstance().KeyTriggerDown(Operation_Type::RETURN_VIEW_POINT_BUTTON)) {
		fpsCam_.eventReset();
	}
	//カメラのアップデート
	fpsCam_.update(player_->getPosition());
	input_to_move(deltaTime);
}

void Player_Event_After::end()
{
}
