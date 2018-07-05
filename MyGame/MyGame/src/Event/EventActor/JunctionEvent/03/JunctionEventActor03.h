#pragma once

#include "../../EventActor.h"
#include"../../../../Actor/Car/Car.h"
class JunctionEventActor03 :public EventActor {
public:
	JunctionEventActor03(IWorld& world);

	//�C�x���g�̍ŏ��Ɉ�񂾂��Ă΂��֐�
	virtual void Start() override;
	//�C�x���g���̃A�b�v�f�[�g
	virtual void Update() override;
	//�C�x���g�̕`��
	virtual void Draw()const override;
	//�C�x���g���I��������Ɉ�񂾂��Ă΂��֐�
	virtual void End() override;
private:
	Car * mCar;
	float mTime{ 0.0f };
};