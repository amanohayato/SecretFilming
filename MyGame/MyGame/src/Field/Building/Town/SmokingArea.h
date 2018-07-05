#ifndef SMOKING_AREA_H_
#define SMOKING_AREA_H_

#include "../BuildingBase.h"
#include "../../../Graphic/AnimationDx.h"
#include"../../../Actor/Effect/Particle/Smoke/SmokeEffect.h"

class SmokingArea : public BuildingBase {
public:
	SmokingArea(IWorld* world, const Vector3& position, int rotationNum = 0);
	SmokingArea(IWorld* world, const Vector2& position, int rotationNum = 0);
	SmokingArea(IWorld* world, int width, int height, int rotationNum = 0, const Vector2& offset = Vector2::Zero);
	void update(float deltaTime) override;
	void draw() const override;
	void end() override;

	void playSmoke();
	// 固有イベント
	void smoking() override;
	virtual void message(EventMessage eventMessage, void* param = nullptr) override;

	std::shared_ptr<BuildingBase> clone() override;
	std::shared_ptr<BuildingBase> clone(IWorld* world, const Vector3& position, int rotationNum) override;
	std::shared_ptr<BuildingBase> clone(IWorld* world, const Vector2& position, int rotationNum) override;
	std::shared_ptr<BuildingBase> clone(IWorld* world, int width, int height, int rotationNum = 0, const Vector2& offset = Vector2::Zero) override;

private:
	int time_{ 1 };
	std::weak_ptr<SmokeEffect> _se;
};

#endif // !SMOKING_AREA_H_