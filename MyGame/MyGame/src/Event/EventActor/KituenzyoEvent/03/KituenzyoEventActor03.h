#pragma once

#include "../../EventActor.h"

class KituenzyoEventActor03:public EventActor {
public:
	KituenzyoEventActor03(IWorld& world);
	~KituenzyoEventActor03();

	//�C�x���g�̍ŏ��Ɉ�񂾂��Ă΂��֐�
	virtual void Start() override;
	//�C�x���g���̃A�b�v�f�[�g
	virtual void Update() override;
	//�C�x���g�̕`��
	virtual void Draw()const override;
	//�C�x���g���I��������Ɉ�񂾂��Ă΂��֐�
	virtual void End() override;
private:

};