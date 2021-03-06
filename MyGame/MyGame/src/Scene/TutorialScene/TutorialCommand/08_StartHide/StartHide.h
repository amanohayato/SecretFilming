#pragma once
#include "../TutorialCommand.h"
#include "../../../../Actor/Player/Player.h"
#include "../../../../Actor/Enemy/TutorialEnemy/TutorialEnemy.h"

class StartHide : public TutorialCommand
{
public:
	StartHide(std::shared_ptr<Player> player, std::shared_ptr<TutorialEnemy> enemy);

	virtual void onStart() override;
	virtual void onUpdate(float deltaTime) override;
	virtual void onDraw() const override;
	virtual void onEnd() override;

	virtual void setText() override;

private:

	std::shared_ptr<Player> player_;

	std::shared_ptr<TutorialEnemy> enemy_;

	// チュートリアル用の宇宙人の警戒度
	float tutorialAwareness_;

	// プレイヤー入力を待っているかのフラグ
	bool isWaitInput_{ false };
};