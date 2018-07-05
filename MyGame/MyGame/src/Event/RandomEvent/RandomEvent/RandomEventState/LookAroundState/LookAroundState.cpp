#include "LookAroundState.h"

LookAroundState::LookAroundState(IWorld & world){
	world_ = &world;
}

void LookAroundState::Initialize()
{
	isEnd_ = false;
	enemyBase_ = std::dynamic_pointer_cast<EnemyBase>(world_->findActor("Enemy"));
	//イベント中
	enemyBase_.lock()->set_is_event(true);
	// アニメーション再生
	enemyBase_.lock()->get_animation().changeAnimation(AnimLoader::getInstance().getAnimKey(MODEL_ID::MODEL_ENEMY, (int)EnemyBase::EnemyAnimation::Aware), false);
}

void LookAroundState::Update()
{
	//アニメーション終わったかどうか 
	if (enemyBase_.lock()->get_animation().isEnd()) {
		isEnd_ = true;
		// イベント終了
		enemyBase_.lock()->set_is_event(false);
	}
}

void LookAroundState::Draw() const
{
}

bool LookAroundState::IsEnd() const
{
	return isEnd_;
}

void LookAroundState::End()
{
}

RandomEvent LookAroundState::Next() const
{
	return RandomEvent::Null_Eve;
}
