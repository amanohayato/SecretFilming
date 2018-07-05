#pragma once
#include"../Enemy/EnemyBase.h"

class AlertGauge :public Actor {
public:
	AlertGauge(IWorld* world, std::weak_ptr<EnemyBase> enemy);

	//初期化
	virtual void initialize()override;
	//更新
	virtual void update(float deltaTime)override;
	//描画
	virtual void draw() const override;

private:
	std::weak_ptr<EnemyBase> target_;	// ターゲットポインタ
	int cbuff_;
	float angle_{ 0.0f };				// 警戒ゲージの回転角度（Ho Siu Kiの追加、2018-5-29）
	float drawRate_{ 0.0f };
	float addSign{ 1.0f };
	float excRate_{ 0.0f };
};