#include "StopShineState.h"

StopShineState::StopShineState(IWorld & world){
	world_ = &world;
}

void StopShineState::Initialize()
{
	isEnd_ = false;
	enemyBase_ = std::dynamic_pointer_cast<EnemyBase>(world_->findActor("Enemy"));
	//イベント中
	enemyBase_.lock()->set_is_event(true);
	// アニメーション再生
	enemyBase_.lock()->get_animation().changeAnimation(AnimLoader::getInstance().getAnimKey(MODEL_ID::MODEL_ENEMY, (int)EnemyBase::EnemyAnimation::RisingHat), false);
}

void StopShineState::Update()
{
}

void StopShineState::Draw() const
{
}

bool StopShineState::IsEnd() const
{
	return isEnd_;
}

void StopShineState::End()
{
}

RandomEvent StopShineState::Next() const
{
	return RandomEvent::LookAround_State;
}
