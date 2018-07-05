#pragma once
#include "../TutorialCommand.h"
#include "../../../../Actor/Enemy/TutorialEnemy/TutorialEnemy.h"

class TakaShutter : public TutorialCommand
{
public:
	TakaShutter(std::shared_ptr<TutorialEnemy> enemy);

	virtual void onStart() override;
	virtual void onUpdate(float deltaTime) override;
	virtual void onDraw() const override;
	virtual void onEnd() override;

	virtual void setText() override;

private:

	std::shared_ptr<TutorialEnemy> enemy_;

	// 宇宙人とホログラムを点滅させるためのタイマー
	float count_{ 0.0f };

	// ホログラムを“直接！！！”表示するためのクラス
	AnimationDx anim_;

	// プレイヤー入力を待っているかのフラグ
	bool isWaitInput_{ false };
};