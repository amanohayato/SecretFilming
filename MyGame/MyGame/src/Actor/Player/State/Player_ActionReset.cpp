#include "Player_ActionReset.h"
#include"../../../Game/Time.h"


Player_ActionReset::Player_ActionReset(ActorPtr player):
	PlayerState(player)
{
}

void Player_ActionReset::start()
{
	player_->setAction(true);
	state_ = Player_State_ID::ActionReset;
}

void Player_ActionReset::update(float deltaTime)
{
	t_ += Time::GetInstance().deltaTime();
	fpsCam_.ResetUpdate(player_->getPosition());
	if (t_ > 0.3f) {
		nextState_ = Player_State_ID::EventAction;
	}
}

void Player_ActionReset::end()
{
	player_->setAction(false);
}
