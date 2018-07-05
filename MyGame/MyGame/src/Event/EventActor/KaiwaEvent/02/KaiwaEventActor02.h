#pragma once

#include "../../EventActor.h"

#include "../../../../Actor/EventActor/Ufo/EventUfo.h"


class EnemyBase;

class KaiwaEventActor02 :public EventActor {
public:
	KaiwaEventActor02(IWorld& world);

	//�C�x���g�̍ŏ��Ɉ�񂾂��Ă΂��֐�
	virtual void Start() override;
	//�C�x���g���̃A�b�v�f�[�g
	virtual void Update() override;
	//�C�x���g�̕`��
	virtual void Draw()const override;
	//�C�x���g���I��������Ɉ�񂾂��Ă΂��֐�
	virtual void End() override;
private:
	EventUfo* mEventUfo;

	float mTime;
	Matrix mUfoMat;
};