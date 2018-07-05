#pragma once

#include"../../Camera/Camera.h"
#include"../Actor.h"
#include"../Body/Base/DummyBody.h"

class CarCamera :public Actor {
public:
	CarCamera(IWorld* world, const Vector3& position, IBodyPtr body = std::make_shared<DummyBody>());

	void setTarget(std::weak_ptr<Actor> target);
	virtual void update(float deltaTime)override;

private:
	std::weak_ptr<Actor> target_;
};