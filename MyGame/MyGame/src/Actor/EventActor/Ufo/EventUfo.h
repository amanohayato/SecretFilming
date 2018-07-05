#pragma once

#include "../../Actor.h"

#include "../../../Field/Building/BuildingBase.h"

#include "../UfoTako/UfoTako.h"


class EventUfo :public Actor {

public:
	EventUfo(IWorld* world,const Vector3& pos1,const Vector3& pos2);
	virtual ~EventUfo() override;

	virtual void initialize() override;

	virtual void update(float deltaTime) override;

	virtual void draw()const override;

	//�ڐG��
	virtual void onCollide(Actor& other) override;

	//ufo�̑��x�擾
	Vector3 GetVelocity();

	//��Ԕԍ����擾
	int& GetNumber();

private:
	void SetLightFlag(bool flag);


private:

	bool mIsLight;

	UfoTako* mUfoTako;


	int mStateNumber;

	Matrix mUfoMat;

	float mRotateY;	//UFO��Y��]

	Vector3 mVelo;		//���x
	Vector3 mSevePosition;
	



	Vector3 mPosition;
	Vector3 mStartPos;	//�X�^�[�g
	Vector3 mGoalPos;	//�S�[��
	float mLerpTime;	//���`�ۊǃ^�C��

	Matrix mUfoLightMat;

	float mUfoLightTime;//���ۊǃ^�C��


};