#pragma once
#include"../Actor.h"
#include"../Body/BoundingSphere.h"
#include"../../ID/EnumIDs.h"

class Hide_InCamera:public Actor {
public:
	Hide_InCamera(IWorld* world, const Vector3& position) :Actor(world, "Object", position, std::make_shared<BoundingSphere>(Vector3::Zero, 80.0f)) {
		rotation_ = Matrix::CreateRotationY(30);
		rotation_ *= Matrix::CreateRotationX(-20);
	}
	void update(float deltaTime)override {
	}
	void draw()const override {
		DrawSphere3D(position_, body_->radius(), 32, GetColor(255, 0, 0), GetColor(125, 125, 125), FALSE);
		DrawSphere3D(position_, body_->radius()*0.05f, 32, GetColor(255, 0, 0), GetColor(125, 125, 125), TRUE);
	}

	virtual void onCollide(Actor& other) {
		if (!isAction_) {
			if (other.getName() == "Enemy") {
				//other.receiveMessage(EventMessage::Hide_InCamera, (void*)this);
			}
			if (other.getName() == "Player") {
				//other.receiveMessage(EventMessage::Hide_InCamera, (void*)this);
			}
		}
	}
	void isAction() {
		isAction_ = true;
	}
	void endAction() {
		isAction_ = false;
	}
	EventAction_State getEvent()const {
		return state_;
	}
private:
	bool isAction_{ false };
	EventAction_State state_{ EventAction_State::Car_Action };
};