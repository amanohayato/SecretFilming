#pragma once

#include "../../Actor.h"

#include "../../../Field/Building/BuildingBase.h"
//�C�x���g�̎��̋@���x�z����A�N�^�[


class EnemyBeam :public Actor{
public:
	EnemyBeam(IWorld* world);
	virtual ~EnemyBeam() override;

	virtual void initialize() override;

	virtual void update(float deltaTime) override;

	virtual void draw()const override;

	//�ڐG��
	virtual void onCollide(Actor& other) override;

	//�r�[���������ǂ���
	void SetIsBeam(bool flag);

private:
	bool mIsBeam;

	Matrix mBeamMat;

	float mBeamScaleY;
	float mBeamScaleXZ;

	float mAlpha;
};