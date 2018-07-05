#pragma once
#include "../TutorialCommand.h"

class LookSpecifiedPointIcon : public TutorialCommand
{
public:
	LookSpecifiedPointIcon();

	virtual void onStart() override;
	virtual void onUpdate(float deltaTime) override;
	virtual void onDraw() const override;
	virtual void onEnd() override;

	virtual void setText() override;

private:

	bool finalChangeAlpa_{ false };

	// UI強調表示画像の濃さ
	float blindAlpa_{ 0.0f };

	// 変化後のUI強調表示画像の濃さ
	float afterBlindAlpa_{ 0.0f };

	// 毎フレームごとのUI強調表示の濃さの変更
	float blindAlpaChangeRate_{ 0.0f };
};