#pragma once

#include "../../Actor.h"

class TitleUfoFactory : public Actor
{
public:
	TitleUfoFactory(IWorld* world);

	virtual void initialize() override;

	virtual void update(float deltaTime) override;

	virtual void draw()const override;

private:

	// UFO���o������Ԋu�̃J�E���^�[
	int spawnCounter_;

	// UFO���ʂ钆�S�ʒu
	Vector3 centerPos_ = { 600, 300, 600 };

	// UFO���o������Ԋu
	const int spawnInterval_ = { 60 * 10 };
};
