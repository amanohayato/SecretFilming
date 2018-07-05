#include "FallDownState.h"
#include"../../../../../Sound/Sound.h"

FallDownState::FallDownState(IWorld & world){
	world_ = &world;
}

void FallDownState::Initialize()
{
	isEnd_ = false;
	enemyBase_ = std::dynamic_pointer_cast<EnemyBase>(world_->findActor("Enemy"));
	//イベント中
	enemyBase_.lock()->set_is_event(true);
	// アニメーション再生
	enemyBase_.lock()->get_animation().changeAnimation(AnimLoader::getInstance().getAnimKey(MODEL_ID::MODEL_ENEMY, (int)EnemyBase::EnemyAnimation::FallDown), false);
	_scoreUpFunc = [&] {
		//状態がStopになったら帽子を落としてスコアを設定します
		if (enemyBase_.lock()->get_state() == EnemyBase::EnemyState::Stop) {
			enemyBase_.lock()->fallcap();
			enemyBase_.lock()->setBaseScore(20);
			return true;
		}
		return false;
	};
	voice_Func = [&] {
		Sound::GetInstance().Play3DSE(SE_ID::FALL_VOICE_SE, (VECTOR*)&enemyBase_.lock()->getPosition());
	};
}

void FallDownState::Update()
{
	if (enemyBase_.lock()->get_animation().getGetCurrentAnimTime() >= 15.0f) {
		voice_Func();
		voice_Func = [] {};

	}
	//スコア設定関数を呼び出し
	if (_scoreUpFunc()) {
		_scoreUpFunc = [] {return false; };
	}

	//アニメーション終わったかどうか 
	if (enemyBase_.lock()->get_animation().isEnd()) {
		isEnd_ = true;
	}
}

void FallDownState::Draw() const
{
}

bool FallDownState::IsEnd() const
{
	return isEnd_;
}

void FallDownState::End()
{
	Sound::GetInstance().Play3DSE(SE_ID::FALL_DOWN_SE, (VECTOR*)&enemyBase_.lock()->getPosition());
}

RandomEvent FallDownState::Next() const
{
	return RandomEvent::RisingHat_State;
}
