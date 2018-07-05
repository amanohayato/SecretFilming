#include "Player_Event_Before.h"


Player_Event_Before::Player_Event_Before(ActorPtr player) :
	PlayerState(player)
{
}

void Player_Event_Before::start()
{
	playerPositionStr_ = player_->getPosition();
	amount = 0.0f;
	state_ = Player_State_ID::Event_Before;
}

void Player_Event_Before::update(float deltaTime)
{
	amount += 0.04f;
	player_->getPosition() = Vector3::Lerp(playerPositionStr_, objPositionStr_, MathHelper::Smoothstep(0.0f, 1.0f, amount));
	if (amount > 1.0f) {
		nextState_ = Player_State_ID::ActionReset;
		return;
	}
	if (InputChecker::GetInstance().KeyTriggerDown(Operation_Type::RETURN_VIEW_POINT_BUTTON)) {
		fpsCam_.eventReset();
	}
	fpsCam_.ResetUpdate(player_->getPosition());//カメラのアップデート
}

void Player_Event_Before::end()
{
	fpsCam_.eventReset();
}
