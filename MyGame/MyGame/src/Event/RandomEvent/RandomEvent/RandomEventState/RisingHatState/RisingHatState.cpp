#include "RisingHatState.h"
#include"../../../../../Sound/Sound.h"

RisingHatState::RisingHatState(IWorld & world) {
	world_ = &world;
}

void RisingHatState::Initialize()
{
	isEnd_ = false;
	enemyBase_ = std::dynamic_pointer_cast<EnemyBase>(world_->findActor("Enemy"));
	//イベント中
	enemyBase_.lock()->set_is_event(true);
	// アニメーション再生
	enemyBase_.lock()->get_animation().changeAnimation(AnimLoader::getInstance().getAnimKey(MODEL_ID::MODEL_ENEMY, (int)EnemyBase::EnemyAnimation::RisingHat), false);

	_seFunc = [&] {
		Sound::GetInstance().Play3DSE(SE_ID::FALL_PICK_SE, (VECTOR*)&enemyBase_.lock()->getPosition());
	};
	//帽子を取るための関数です
	_pickupFunc = [&] {
		enemyBase_.lock()->pickcap();
		//ついでに帽子をかぶる時の処理も設定します
		_wearFunc = [&] {
			enemyBase_.lock()->wearcap();
			enemyBase_.lock()->setBaseScore(0);
		};
	};


}

void RisingHatState::Update()
{

	if (enemyBase_.lock()->get_animation().getGetCurrentAnimTime() >= 52.0f) {
		_seFunc();
		_seFunc = [] {};
	}
	//アニメーションのちょうど手を地面につけるタイミングで帽子取る関数を呼ぶ
	if (enemyBase_.lock()->get_animation().getGetCurrentAnimTime() >= 66.0f) {
		_pickupFunc();
		_pickupFunc = [] {};
	}
	//アニメーションの頭につくタイミングで帽子かぶる関数を呼ぶ
	if (enemyBase_.lock()->get_animation().getGetCurrentAnimTime() >= 105.0f) {
		_wearFunc();
		_wearFunc = [] {};
	}
	//アニメーション終わったかどうか 
	if (enemyBase_.lock()->get_animation().isEnd()) {
		isEnd_ = true;
	}
}

void RisingHatState::Draw() const
{
}

bool RisingHatState::IsEnd() const
{
	return isEnd_;
}

void RisingHatState::End()
{
}

RandomEvent RisingHatState::Next() const
{
	return RandomEvent::LookAround_State;
}
