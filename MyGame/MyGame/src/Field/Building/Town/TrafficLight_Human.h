#ifndef TRAFFIC_LIGHT_HUMAN_H_
#define TRAFFIC_LIGHT_HUMAN_H_

#include "../BuildingBase.h"
#include "../../../Graphic/AnimationDx.h"

class TrafficLight_Human : public BuildingBase {
public:
	TrafficLight_Human(IWorld* world, const Vector3& position, int rotationNum = 0);
	TrafficLight_Human(IWorld* world, const Vector2& position, int rotationNum = 0);
	TrafficLight_Human(IWorld* world, int width, int height, int rotationNum = 0, const Vector2& offset = Vector2::Zero);
	void update(float deltaTime) override;
	void draw() const override;
	void end() override;

	void onCollide(Actor& other) override;
	void onEvent() override;

	std::shared_ptr<BuildingBase> clone() override;
	std::shared_ptr<BuildingBase> clone(IWorld* world, const Vector3& position, int rotationNum) override;
	std::shared_ptr<BuildingBase> clone(IWorld* world, const Vector2& position, int rotationNum) override;
	std::shared_ptr<BuildingBase> clone(IWorld* world, int width, int height, int rotationNum = 0, const Vector2& offset = Vector2::Zero) override;

private:
};

#endif // !TRAFFIC_LIGHT_HUMAN_H_