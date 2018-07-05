#pragma once
#include"../Actor.h"
#include"../Body/BoundingSphere.h"
#include"../../ID/EnumIDs.h"

class HideObject:public Actor {
public:
	HideObject(IWorld* world,const Vector3& position):Actor(world,"Object",position, std::make_shared<BoundingSphere>(Vector3::Zero, 80.0f)) {
		
	}
	
	void draw()const override {
		DrawSphere3D(position_, body_->radius(), 32, GetColor(255, 0, 0), GetColor(125, 125, 125), FALSE);

	}

	virtual void onCollide(Actor& other) {
		other.receiveMessage(EventMessage::Hide_Object, (void*)&position_);
	}

};