#pragma once

#include"../../SubScene.h"
#include "../../../../Graphic/SpriteAnimation/ScalingSprite.h"

#include <vector>
#include <memory>

class DisplayPhoto : public SubScene {
public:
	DisplayPhoto();

	virtual void start() override;
	virtual void update(float deltaTime) override;
	virtual void draw()const override;
	virtual void end() override;

	void stampStart();

	bool isEndAnimation();

private:

	// 写真が降ってくる演出用クラス
	std::vector<std::shared_ptr<ScalingSprite>> photoAnims_;

	// 降ってくる写真のフレームの演出用クラス
	//std::shared_ptr<ScalingSprite> photoFrameAnims_;
	
	// 何回目の写真の表示アニメーションを表示しているか
	int displayPhotoCount_{ 0 };

	// 何枚の写真を表示するか？
	int photoNumber_{ 6 };

	// 最大何枚の写真を表示するか？
	static const int maxPhotoNumber_{ 6 };

	// スタンプが押されるアニメーションが開始されたかのフラグ
	bool isStampStart_;

	// スタンプが押されるアニメーションが折り返されたかのフラグ
	bool isAnimReturn_;
};