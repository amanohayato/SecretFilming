#pragma once

#include<DxLib.h>
#include "../../math/Vector2.h"

// 画像の大きさ変更アニメーションクラス
class ScalingSprite
{
public:
	// コンストラクタ
	ScalingSprite(Vector2 beforeScale, Vector2 afterScale, float scalingTime);

	// 値を再設定
	void reSet(Vector2 afterScale, float scalingTime);

	// 更新
	void update(float deltaTime);

	// 現在のスケールを取得
	Vector2 getCurScale();

	// アニメーションが終わっているかの判定
	bool isAnimationEnd();

private:

	// 経過時間
	float time_{ 0.0f };

	// 終了する時間
	float limitTime_{ 0.0f };

	// 現在のスケール
	Vector2 curScale_;

	// 変化後のスケール
	Vector2 afterScale_;

	// 毎秒あたりのスケールの変化幅
	Vector2 scaleChangeWidth_;
};