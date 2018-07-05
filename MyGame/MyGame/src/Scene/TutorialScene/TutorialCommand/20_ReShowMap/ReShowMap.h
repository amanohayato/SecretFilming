#pragma once
#include "../TutorialCommand.h"
#include "../../../../Actor/Player/Player.h"

class ReShowMap : public TutorialCommand
{
public:
	ReShowMap(std::shared_ptr<Player> player);

	virtual void onStart() override;
	virtual void onUpdate(float deltaTime) override;
	virtual void onDraw() const override;
	virtual void onEnd() override;

	virtual void setText() override;

private:

	std::shared_ptr<Player> player_;

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