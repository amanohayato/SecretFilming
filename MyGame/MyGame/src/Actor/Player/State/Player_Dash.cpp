#include "Player_Dash.h"
#include"../../../Sound/Sound.h"


Player_Dash::Player_Dash(ActorPtr player) :
	PlayerState(player)
{
}

void Player_Dash::start()
{
	state_ = Player_State_ID::Dash;
	moveSpeed_ *= 2.0f;
}

void Player_Dash::update(float deltaTime)
{
	if (!prevfloor_) {
		nextState_ = Player_State_ID::Fall;
		return;
	}

	/*L2が押された場合実行*/
	if (InputChecker::GetInstance().KeyTriggerDown(Operation_Type::HOLD_CAMERA_BUTTON)) {
		nextState_ = Player_State_ID::SetUp;
		return;
	}
	if (InputChecker::GetInstance().KeyTriggerDown(Operation_Type::SHOW_MAP_BUTTON)) {
		nextState_ = Player_State_ID::MapApp;
		return;
	}
	if (InputChecker::GetInstance().KeyTriggerUp(Operation_Type::DASH_BUTTON) || InputChecker::GetInstance().KeyTriggerUp(Operation_Type::DEBUG_CLEAR_BUTTON)) {
		nextState_ = Player_State_ID::Idle;
		return;
	}
	if (InputChecker::GetInstance().KeyTriggerDown(Operation_Type::RETURN_VIEW_POINT_BUTTON)) {
		fpsCam_.normalReset();
	}
	fpsCam_.update(player_->getPosition());//カメラのアップデート
	 // キー入力によるプレイヤーの移動（関数にまとめました）
	input_to_move(deltaTime);

}

void Player_Dash::end()
{
	Sound::GetInstance().StopSE(SE_ID::RUN_SE);
}
