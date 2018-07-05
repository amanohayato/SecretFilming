#include "Player_Fall.h"
#include"../../../Sound/Sound.h"


Player_Fall::Player_Fall(ActorPtr player) :
	PlayerState(player)
{
}

void Player_Fall::start()
{
	gravity_ = -9.8f * 0.1f;
	prevfloor_ = false;
	state_ = Player_State_ID::Fall;
}

void Player_Fall::update(float deltaTime)
{
	if (prevfloor_) {
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

void Player_Fall::end()
{
	Sound::GetInstance().StopSE(SE_ID::RUN_SE);
}
