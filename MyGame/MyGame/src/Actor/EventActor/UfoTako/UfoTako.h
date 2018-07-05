#pragma once

#include "../../Actor.h"

#include "../../../Graphic/AnimationOutSide.h"

class UfoTako :public Actor {
public:
	UfoTako(IWorld* world, const Vector3& start, const Vector3& end);
	~UfoTako();
	//������
	virtual void initialize() override;
	virtual void update(float deltaTime) override;
	virtual void draw()const override;

	AnimationOutSide& GetAnimation();

	//�n��ɏo�邩�ǂ���
	void SetIsDown(bool isDown);

	//�X�^�[�g�n�_��ς���
	void SetStartPos(const Vector3& startPos);
private:
	//�G�l�~�[
	ActorPtr mEnemyBase;
	//�^�R�̃}�g���N�X
	Matrix mUfoTakoMat;
	Vector3 mPosition;

	Vector3 mStartPos;
	Vector3 mEndPos;

	bool mIsDown;	//�n��ɏo�Ă��邩�H

	float mLerpTime;

	AnimationOutSide mAnimation;
};