#pragma once
#include "../../Actor.h"
class MissionStart:public Actor {
public:
	// コンストラクタ
	MissionStart();
	// 初期化
	virtual void initialize() override;
	// 更新
	virtual void update(float delta_time) override;
	// 描画
	virtual void draw() const override;

private:
	// 表示タイマー
	float mTime;
	//α値
	float mAlpha;
	//画像サイズ
	Vector2 mSize;
};