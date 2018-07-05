#pragma once
#include"../Actor.h"

//タイムアタック用チェックポイント
class CheckPoint :public Actor {
public:
	CheckPoint(IWorld* world, const Vector3& position);	
	~CheckPoint() = default;

private:
	void update(float deltaTime)override;

	void draw()const override;

	void onCollide(Actor& other) override;

private:

};