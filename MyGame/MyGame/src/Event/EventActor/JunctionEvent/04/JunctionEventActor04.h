#pragma once

#include "../../EventActor.h"
#include"../../../../Actor/Car/Car.h"
class JunctionEventActor04 :public EventActor {
public:
	JunctionEventActor04(IWorld& world);

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
	int count{ 0 };
};