#pragma once

#include "../EventActor.h"

class MimawasiEventActor :public EventActor {
public:
	MimawasiEventActor(IWorld& world);

	//�C�x���g�̍ŏ��Ɉ�񂾂��Ă΂��֐�
	virtual void Start() override;
	//�C�x���g���̃A�b�v�f�[�g
	virtual void Update() override;
	//�C�x���g�̕`��
	virtual void Draw()const override;
	//�C�x���g���I��������Ɉ�񂾂��Ă΂��֐�
	virtual void End() override;
private:
	float mTime;

	Vector3 mVelo;
};