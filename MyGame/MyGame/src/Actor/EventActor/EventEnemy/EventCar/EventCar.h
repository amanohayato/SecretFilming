#pragma once
#include "../../../Actor.h"


class EventCar :public Actor {
public:
	EventCar(IWorld* world,const Matrix& mat);

	virtual void initialize() override;

	virtual void update(float deltaTime) override;

	virtual void draw()const override;
	virtual void shadowDraw()const override;

	//�ڐG��
	virtual void onCollide(Actor& other) override;

	//�����Ă��邩
	void SetIsFly(bool isFly);
	//���W���Z�b�g
	Vector3& GetPosition();

	//�Ԃ���΂�
	void IsFlyMax();

private:
	//�Ԃ��Ƃ΂�
	bool mIsFlyMax;
	//�����Ă��邩
	bool mIsFly;
	//�Ԃ̏㉺�ړ��̑��x
	Vector3 mVelo;
	//���W
	Vector3 mPosition;

	Matrix mMat;
	
	float mSinNumber;
};