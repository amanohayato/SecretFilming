#ifndef ENEMY_BARRIER_H_
#define ENEMY_BARRIER_H_

#include "../Actor.h"

// エネミーのバリアクラス
// 担当：Ho Siu Ki（何兆祺）
class EnemyBarrier : public Actor
{
public:
	// コンストラクタ
	EnemyBarrier(ActorPtr target,ActorPtr enemy,Vector3 position, Matrix rotation,bool isStop = false);
	// 初期化
	void initialize() override;
	// 更新
	void update(float delta_time) override;
	// 描画
	void draw() const override;
private:
	// ターゲット（エネミー）
	ActorPtr target_;
	ActorPtr enemy_;
	// 表示タイマー
	float timer_{ 1.0f };
	bool isStop_{ false };
};

#endif // !ENEMY_BARRIER_H_