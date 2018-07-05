#pragma once

#include "../EnemyBase.h"

class TutorialEnemy : public EnemyBase
{
public:
	// コンストラクタ
	TutorialEnemy(IWorld* world, const Vector3& position, const IBodyPtr& body = std::make_shared<BoundingCapsule>(Vector3{ 0.0f,0.0f,0.0f }, Matrix::Identity, 15.0f, 4.0f));
	
	void update(float delta_time_) override;
	
	// 接触判定
	void onCollide(Actor& other) override;

	void changeSpeed(float normal_speed, float escape_speed);

	void changeTimer(float timer);

	void changeRandomEventFlag(bool flag);

	void setTutorialMovePoint();

	// 何秒で歩くのをやめるかを設定する
	void setStopTimer(float value);

	// 何秒で歩くのをやめるかのタイマーを無力化する
	void InactiveStopTimer();

	// 警戒度を上昇させないかのフラグを変更
	void SetInactiveAwareness(bool flag);

private:

	bool activeStopTimer_{ false };

	// 警戒度を上昇させないかのフラグ
	bool inactiveAwareness_{ false };

	// 何秒で歩くのをやめるかのタイマー
	float stopTimer_{ 0.0f };

};