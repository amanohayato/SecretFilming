#include "Player_Launch.h"

Player_Launch::Player_Launch(ActorPtr player) :
	PlayerState(player)
{
}

void Player_Launch::start()
{
	gravity_ = -9.8f * 0.1f;
	prevfloor_ = false;
	state_ = Player_State_ID::Launch;
}

void Player_Launch::update(float deltaTime)
{
	if (prevfloor_) {
		nextState_ = Player_State_ID::Idle;
		return;
	}
	fpsCam_.update(player_->getPosition());
}

void Player_Launch::end()
{
}
