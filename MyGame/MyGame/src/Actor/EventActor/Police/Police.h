#pragma once

#include "../../Actor.h"

#include "../../../Graphic/AnimationOutSide.h"


class Police :public Actor {

public:
	enum PoliceAnim {
		POLICE_IDLE_ANIM,
		POLICE_RUN_ANIM,
		POLICE_POINT_ANIM,
		POLICE_SICK_ANIM = 3
	};

public:
	Police(IWorld* world, const Matrix& mat);

	virtual void initialize() override;

	virtual void update(float deltaTime) override;

	virtual void draw()const override;
	virtual void shadowDraw()const override;


public:
	AnimationOutSide& GetAnimation();
	Matrix& GetMatrix();
	Matrix GetStartMat();
private:
	Matrix mStartMat;

	AnimationOutSide mAnim;

	Matrix mPoliceMat;
	//ç¿ïW
	Vector3 mPosition;
	//âÒì]
	Vector3 mRotate;


	int mEventIndex;
};