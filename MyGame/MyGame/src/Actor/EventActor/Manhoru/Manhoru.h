#pragma once

#include "../../Actor.h"

class Manhoru :public Actor {
public:
	Manhoru(IWorld* world, const Vector3& pos);

	virtual void initialize() override;

	virtual void update(float deltaTime) override;

	virtual void draw()const override;
	//�����Ă��邩
	void SetIsFly(bool isFly);
	//���W���Z�b�g
	Vector3& GetPosition();

	//�Ԃ���΂�
	void IsFlyMax();

	//�߂��Ă���
	void IsReturn();
private:
	//�Ԃ��Ƃ΂�
	bool mIsFlyMax;
	//�����Ă��邩
	bool mIsFly;
	//�Ԃ̏㉺�ړ��̑��x
	Vector3 mVelo;
	//���W
	Vector3 mPosition;



	//�߂��Ă���Ƃ�
	bool mIsReturn;
	float mStartY;
	float mEndY;
	float mLerpTime;

	float mSinNumber;

};