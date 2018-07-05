#pragma once
#include "../../Actor.h"
#include "../../Enemy/EnemyBase.h"
#include "../../Player/State/PlayerState.h"

// ゲームオーバーイベントクラス
// 担当：Ho Siu Ki（何兆祺）
// 参考：Actor/EventActor/GameClearEvent.h
class GameOverEvent : public Actor
{
public:
	// コンストラクタ
	GameOverEvent(IWorld * world, float goal_timer, float goal_time, std::weak_ptr<EnemyBase> enemy);
	// 初期化
	void initialize();
	// 更新
	void update(float delta_time) override;
	// 描画
	void draw()const;


private:
	std::function<void()> createUFOfunc_;
	std::weak_ptr<EnemyBase> enemy_;	// エネミーのポインタ
	const float goal_time_;				// ゴールしてからリザルトに移行するまでの秒数
	float goal_timer_;					// ゴールしてからリザルトに移行するまでの秒数カウント
	const Vector3 camerapos_ = { 725.0f,11.0f,715.0f };
};