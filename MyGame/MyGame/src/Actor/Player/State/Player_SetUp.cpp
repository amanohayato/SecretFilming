#include "Player_SetUp.h"
#include"../../PhoneApp/SmartPhone.h"

Player_SetUp::Player_SetUp(ActorPtr player) :
	PlayerState(player)
{
}

void Player_SetUp::start()
{
	state_ = Player_State_ID::SetUp;
	moveSpeed_ *= 0.2f;
	player_->setCamera(true);
	auto phone = std::static_pointer_cast<SmartPhone>(player_->findCildren("SmartPhone"));
	phone->setActiveCamera(true);
}

void Player_SetUp::update(float deltaTime)
{
	/*L2‚ª—£‚³‚ê‚½‚Æ‚«ŽÀs*/
	if (InputChecker::GetInstance().KeyStateUp(Operation_Type::HOLD_CAMERA_BUTTON)) {
		nextState_ = Player_State_ID::Idle;
		return;
	}
	if (InputChecker::GetInstance().KeyTriggerDown(Operation_Type::RETURN_VIEW_POINT_BUTTON)) {
		fpsCam_.normalReset();
	}
	fpsCam_.update(player_->getPosition());
	input_to_move(deltaTime);
}

void Player_SetUp::end()
{
	player_->setCamera(false);
	auto phone = std::static_pointer_cast<SmartPhone>(player_->findCildren("SmartPhone"));
	phone->setActiveCamera(false);

}
