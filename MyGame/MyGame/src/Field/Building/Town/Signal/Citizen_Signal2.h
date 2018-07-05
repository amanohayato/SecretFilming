#pragma once

#include "../../BuildingBase.h"
#include "../../../../Graphic/AnimationDx.h"

class Citizen_Signal2 : public BuildingBase {
public:
	Citizen_Signal2(IWorld* world, const Vector3& position, int rotationNum = 0);
	Citizen_Signal2(IWorld* world, const Vector2& position, int rotationNum = 0);
	Citizen_Signal2(IWorld* world, int width, int height, int rotationNum = 0, const Vector2& offset = Vector2::Zero);
	void update(float delta_time) override;
	void draw() const override;
	void end() override;
	void ci_yellow_signal(float delta_time);

	std::shared_ptr<BuildingBase> clone() override;
	std::shared_ptr<BuildingBase> clone(IWorld* world, const Vector3& position, int rotationNum) override;
	std::shared_ptr<BuildingBase> clone(IWorld* world, const Vector2& position, int rotationNum) override;
	std::shared_ptr<BuildingBase> clone(IWorld* world, int width, int height, int rotationNum = 0, const Vector2& offset = Vector2::Zero) override;

private:
	float count = 0;
};