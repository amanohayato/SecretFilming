#ifndef HOUSE_2_H_
#define HOUSE_2_H_

#include "../BuildingBase.h"
#include "../../../Graphic/AnimationDx.h"

class House_2 : public BuildingBase {
public:
	House_2(IWorld* world, const Vector3& position, int rotationNum = 0);
	House_2(IWorld* world, const Vector2& position, int rotationNum = 0);
	House_2(IWorld* world, int width, int height, int rotationNum = 0, const Vector2& offset = Vector2::Zero);
	void update(float deltaTime) override;
	void draw() const override;
	void end() override;
	void setTexture(int type)override;

	std::shared_ptr<BuildingBase> clone() override;
	std::shared_ptr<BuildingBase> clone(IWorld* world, const Vector3& position, int rotationNum) override;
	std::shared_ptr<BuildingBase> clone(IWorld* world, const Vector2& position, int rotationNum) override;
	std::shared_ptr<BuildingBase> clone(IWorld* world, int width, int height, int rotationNum = 0, const Vector2& offset = Vector2::Zero) override;

private:
};

#endif // !HOUSE_1_H_