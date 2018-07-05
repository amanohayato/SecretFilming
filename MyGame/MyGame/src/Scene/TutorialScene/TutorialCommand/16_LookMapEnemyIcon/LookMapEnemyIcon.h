#pragma once
#include "../TutorialCommand.h"
#include "../../../../Actor/Enemy/TutorialEnemy/TutorialEnemy.h"

class LookMapEnemyIcon : public TutorialCommand
{
public:
	LookMapEnemyIcon(std::shared_ptr<TutorialEnemy> enemy);

	virtual void onStart() override;
	virtual void onUpdate(float deltaTime) override;
	virtual void onDraw() const override;
	virtual void onEnd() override;

	virtual void setText() override;

private:

	std::shared_ptr<TutorialEnemy> enemy_;

	bool finalChangeAlpa_{ false };

	// UI強調表示画像の濃さ
	float blindAlpa_{ 0.0f };

	// 変化後のUI強調表示画像の濃さ
	float afterBlindAlpa_{ 0.0f };

	// 毎フレームごとのUI強調表示の濃さの変更
	float blindAlpaChangeRate_{ 0.0f };
};