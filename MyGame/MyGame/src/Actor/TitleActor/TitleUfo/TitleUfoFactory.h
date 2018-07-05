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

	// UFOを出現する間隔のカウンター
	int spawnCounter_;

	// UFOが通る中心位置
	Vector3 centerPos_ = { 600, 300, 600 };

	// UFOが出現する間隔
	const int spawnInterval_ = { 60 * 10 };
};
