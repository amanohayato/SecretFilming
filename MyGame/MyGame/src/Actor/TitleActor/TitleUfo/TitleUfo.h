#pragma once

#include "../../Actor.h"


class TitleUfo :public Actor {

public:
	TitleUfo(IWorld* world, const Vector3& pos1, const Vector3& pos2);

	virtual ~TitleUfo() override;

	virtual void initialize() override;

	virtual void update(float deltaTime) override;

	virtual void draw()const override;

private:

	// 開始座標
	Vector3 startPos_;

	// 終了座標
	Vector3 goalPos_;

	// 何カウントで自身を消すかを表すカウンタ
	int deleteTimer_;

	// 移動速度
	const float moveSpeed_ = { 3.0f };
};