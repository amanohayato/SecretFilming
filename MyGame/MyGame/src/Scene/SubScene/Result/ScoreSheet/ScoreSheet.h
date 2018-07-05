#pragma once

#include"../../SubScene.h"
#include "../../../../Graphic/SpriteAnimation/ScalingSprite.h"

#include <memory>

class ScoreSheet : public SubScene {
public:

	ScoreSheet();
	virtual void start() override;
	virtual void update(float deltaTime) override;
	virtual void draw()const override;
	virtual void end() override;

	void bonusCalculation();

	void stampStart();

protected:

	virtual void baseInit() override;

private:

	// ランクの種類
	enum Rank
	{
		S,
		A,
		B,
		C,
		D,
	};

	// そのゲームのランク
	Rank rank_;

	// ランクを出力するか？
	bool displayRank_{ false };

	// 確定度の値（％）
	float determination_{ 0.0f };

	// 撮った写真の枚数
	int photoCount_{ 0 };

	// 撮った写真の枚数でのボーナス値
	float photoCountBonus_{ 0.0f };

	// 逃げられた回数
	int escapeCount_{ 0 };

	// 逃げられた回数でのボーナス値
	float escapeCountBonus_{ 0.0f };

	// ボーナス込みの値（％）
	float totalScore_{ 0.0f };

	// ゲームのクリアフラグ
	bool isClear_{ false };

	// スタンプが押されるアニメーションが開始されたかのフラグ
	bool isAnimStart_;

	// スタンプが押されるアニメーションが折り返されたかのフラグ
	bool isAnimReturn_;

	// スタンプが押される演出用クラス
	std::shared_ptr<ScalingSprite> sheetAnim_;
};