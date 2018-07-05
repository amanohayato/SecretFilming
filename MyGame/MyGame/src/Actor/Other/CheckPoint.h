#pragma once
#include"../Actor.h"

//�^�C���A�^�b�N�p�`�F�b�N�|�C���g
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