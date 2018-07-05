#pragma once

#include"DxLib.h"
#include"Sprite.h"
#include"../ID/EnumIDs.h"

// 画像の大きさ変更アニメーションクラス
class ScalingImage
{
public:
	// コンストラクタ
	ScalingImage(SPRITE_ID id, Vector2 position, Vector2 origin, Vector2 beforeScale, Vector2 afterScale, float beforeAlpha, float afterAlpha, float scalingTime);

	// 
	void reSet(Vector2 afterScale, float afterAlpha, float scalingTime);

	// 更新
	void update(float deltaTime);

	// 描画
	void draw();

	// アニメーションが終わっているかの判定
	bool isAnimationEnd();

private:

	// 表示するスプライトのID
	SPRITE_ID id_;

	// 表示するスプライトの位置
	Vector2 position_;

	// 表示するスプライトの中心点
	Vector2 origin_;

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

	// 現在のスプライトの濃さ
	float curAlpha_;

	// 変化後のスプライトの濃さ
	float afterAlpha_;

	// 毎秒あたりのスプライトの濃さの変化幅
	float alphaChangeWidth_;
};