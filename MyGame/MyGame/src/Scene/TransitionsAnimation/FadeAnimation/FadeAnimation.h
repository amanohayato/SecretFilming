#pragma once
#include "../TransitionsAnimation.h"

class FadeAnimation : public TransitionsAnimation
{
public:
	FadeAnimation(float maxAnimeTime);

	virtual void start() override;
	virtual void update(float deltaTime) override;
	virtual void draw()const override;

	virtual bool isChangeScene() override;

private:

	bool isAnimeReturn_{ false };
	float fadeRate_{ 0.0f };
	float animeTimer_{ 0.0f };

	float maxAnimeTime_{ 0.0f };
};