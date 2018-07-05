#pragma once
#include "../../Actor.h"
#include"../../../Graphic/AnimationDx.h"

class AbductCat:public Actor {
public:
	AbductCat(IWorld* world, const Vector3& position);
	
	virtual void initialize() override;

	virtual void update(float deltaTime) override;

	virtual void draw()const override;

	virtual void receiveMessage(EventMessage em,void* param)override;

	virtual void dead()override;
private:
	AnimationDx animation_{};

	std::function<void()> updatefunc_;
	std::function<void()> playSEfunc_;
};