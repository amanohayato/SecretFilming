#include "Player_MapApp.h"
#include"../../PhoneApp/SmartPhone.h"

Player_MapApp::Player_MapApp(ActorPtr player):
	PlayerState(player)
{
}

void Player_MapApp::start()
{
	state_ = Player_State_ID::MapApp;
	moveSpeed_ *= 0.5f;
	auto phone = std::static_pointer_cast<SmartPhone>(player_->findCildren("SmartPhone"));
	phone->setActiveMap(true);

}

void Player_MapApp::update(float deltaTime)
{
	/*L2‚ª—£‚³‚ê‚½‚Æ‚«ŽÀs*/
	if (InputChecker::GetInstance().KeyTriggerDown(Operation_Type::SHOW_MAP_BUTTON)) {
		nextState_ = Player_State_ID::Idle;
		return;
	}
	fpsCam_.update(player_->getPosition());
	input_to_move(deltaTime);

}

void Player_MapApp::end()
{
	auto phone = std::static_pointer_cast<SmartPhone>(player_->findCildren("SmartPhone"));
	phone->setActiveMap(false);

}
