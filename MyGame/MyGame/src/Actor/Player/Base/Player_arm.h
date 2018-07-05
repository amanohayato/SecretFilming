#pragma once

#include<iostream>
#include"../../../World/World.h"

class Player_arm {
public:
	Player_arm();
	void start(ActorPtr player);
	void update(float deltaTime);
	void draw() const;
	void change_arm(MODEL_ID name, ActorPtr player,Matrix rotation);
	void isArm(bool isArm);
	bool isAction() const;
	void move(float deltaTime);

private:
	IWorld * world_;
	ActorPtr playerptr_;
	Vector3 position_{Vector3::Zero};
	Vector3 pos{ Vector3::Zero };
	Matrix rotation_{ Matrix::Identity };
	Matrix rot{ Matrix::Identity };
	Matrix playerRot{ Matrix::Identity };
	bool isArm_{ false };
	bool isAction_{ false };
	float amount{ 0.0f };
	float timer_{ 0.0f };
	AnimationDx animation_;
};