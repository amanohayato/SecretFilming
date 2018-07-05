#pragma once

#include "../../EventActor.h"

class KituenzyoEventActor02:public EventActor {
public:
	KituenzyoEventActor02(IWorld& world);
	~KituenzyoEventActor02();

	//�C�x���g�̍ŏ��Ɉ�񂾂��Ă΂��֐�
	virtual void Start() override;
	//�C�x���g���̃A�b�v�f�[�g
	virtual void Update() override;
	//�C�x���g�̕`��
	virtual void Draw()const override;
	//�C�x���g���I��������Ɉ�񂾂��Ă΂��֐�
	virtual void End() override;
private:
	Matrix mStartMat;
	Matrix mEndMat;
	float mLerpTime;
};