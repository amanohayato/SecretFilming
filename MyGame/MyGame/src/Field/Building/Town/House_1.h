#ifndef HOUSE_1_H_
#define HOUSE_1_H_

#include "../BuildingBase.h"
#include "../../../Graphic/AnimationDx.h"

class House_1 : public BuildingBase {
public:
	House_1(IWorld* world, const Vector3& position, int rotationNum = 0);
	House_1(IWorld* world, const Vector2& position, int rotationNum = 0);
	House_1(IWorld* world, int width, int height, int rotationNum = 0, const Vector2& offset = Vector2::Zero);
	void update(float deltaTime) override;
	void draw() const override;
	void end() override;
	virtual void setTexture(int type)override;
	std::shared_ptr<BuildingBase> clone() override;
	std::shared_ptr<BuildingBase> clone(IWorld* world, const Vector3& position, int rotationNum) override;
	std::shared_ptr<BuildingBase> clone(IWorld* world, const Vector2& position, int rotationNum) override;
	std::shared_ptr<BuildingBase> clone(IWorld* world, int width, int height, int rotationNum = 0, const Vector2& offset = Vector2::Zero) override;

private:
};

#endif // !HOUSE_1_H_