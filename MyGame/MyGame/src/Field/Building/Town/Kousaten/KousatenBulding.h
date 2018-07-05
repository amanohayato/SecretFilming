#pragma once

#include "../../BuildingBase.h"
#include "../../../../Graphic/AnimationDx.h"

class KousatenBulding : public BuildingBase {
public:
	KousatenBulding(IWorld* world, const Vector3& position, int rotationNum = 0);
	KousatenBulding(IWorld* world, const Vector2& position, int rotationNum = 0);
	KousatenBulding(IWorld* world, int width, int height, int rotationNum = 0, const Vector2& offset = Vector2::Zero);
	void update(float deltaTime) override;
	void draw() const override;
	void end() override;

	std::shared_ptr<BuildingBase> clone() override;
	std::shared_ptr<BuildingBase> clone(IWorld* world, const Vector3& position, int rotationNum) override;
	std::shared_ptr<BuildingBase> clone(IWorld* world, const Vector2& position, int rotationNum) override;
	std::shared_ptr<BuildingBase> clone(IWorld* world, int width, int height, int rotationNum = 0, const Vector2& offset = Vector2::Zero) override;

private:
};