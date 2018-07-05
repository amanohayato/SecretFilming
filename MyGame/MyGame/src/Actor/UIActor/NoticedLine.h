#ifndef NOTICED_LINE_H_
#define NOTICED_LINE_H_

#include"../Enemy/EnemyBase.h"

// 気づき線クラス
// 担当：Ho Siu Ki（何兆祺）
class NoticedLine : public Actor
{
public:
	// コンストラクタ
	NoticedLine(ActorPtr target);
	// 初期化
	virtual void initialize() override;
	// 更新
	virtual void update(float delta_time) override;
	// 描画
	virtual void draw() const override;

private:
	// ターゲット
	ActorPtr target_;
	// 表示タイマー
	float timer_{ 1.0f };
};

#endif // !NOTICED_LINE_H_