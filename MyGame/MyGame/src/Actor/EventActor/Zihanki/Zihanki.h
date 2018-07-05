#pragma once

#include "../../Actor.h"

#include "../../../Field/Building/BuildingBase.h"
//イベントの自販機を支配するアクター


class Zihanki :public Actor{
public:
	Zihanki(IWorld* world, std::weak_ptr<BuildingBase> zihanki);
	virtual ~Zihanki() override;

	virtual void initialize() override;

	virtual void update(float deltaTime) override;

	virtual void draw()const override;

	//接触時
	virtual void onCollide(Actor& other) override;

private:
	std::weak_ptr<BuildingBase> mBuildingBase;
	Vector3 mVelo;
};