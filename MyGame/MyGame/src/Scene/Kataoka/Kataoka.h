#pragma once
#include"../Scene.h"

#include "../../World/World.h"

class EventManager;

//�V�[���e���v���[�g
class Kataoka :public Scene {
public:
	Kataoka();
	virtual void start()override;
	virtual void update(float deltaTime)override;
	virtual void draw()const override;
	//isEnd��true�ɂȂ�����̏���
	virtual void end() override;

	float Direction(const Matrix& mat1, const Matrix& mat2);

	World mWorld;
	//�C�x���g�}�l�[�W���[
	EventManager* mEventManager;
	
	Vector2 mPos;

	Matrix mMat;
	Matrix mVMat;

	Matrix mLerpMat;
	float mLerpTime;
};