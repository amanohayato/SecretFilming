#pragma once
#include "../TutorialCommand.h"
#include "../../../../Actor/Player/Player.h"
#include "../../../../Actor/Enemy/TutorialEnemy/TutorialEnemy.h"

class LookCameraIcon : public TutorialCommand
{
public:
	LookCameraIcon(std::shared_ptr<Player> player, std::shared_ptr<TutorialEnemy> enemy);

	virtual void onStart() override;
	virtual void onUpdate(float deltaTime) override;
	virtual void onDraw() const override;
	virtual void onEnd() override;

	virtual void setText() override;

private:

	std::shared_ptr<Player> player_;
	std::shared_ptr<TutorialEnemy> enemy_;

	// 宇宙人とホログラムを点滅させるためのタイマー
	float count_{ 0.0f };

	// ホログラムを“直接！！！”表示するためのクラス
	AnimationDx anim_;

	// プレイヤー入力を待っているかのフラグ
	bool isWaitInput_{ false };

	bool finalChangeAlpa_{ false };

	// UI強調表示画像の濃さ
	float blindAlpa_{ 0.0f };

	// 変化後のUI強調表示画像の濃さ
	float afterBlindAlpa_{ 0.0f };

	// 毎フレームごとのUI強調表示の濃さの変更
	float blindAlpaChangeRate_{ 0.0f };
};
