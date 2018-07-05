#pragma once

#include "../../EventActor.h"

class ManhoruEventActor05 :public EventActor {
public:
	ManhoruEventActor05(IWorld& world);
	~ManhoruEventActor05();

	//�C�x���g�̍ŏ��Ɉ�񂾂��Ă΂��֐�
	virtual void Start() override;
	//�C�x���g���̃A�b�v�f�[�g
	virtual void Update() override;
	//�C�x���g�̕`��
	virtual void Draw()const override;
	//�C�x���g���I��������Ɉ�񂾂��Ă΂��֐�
	virtual void End() override;
private:
	ActorPtr mManhoru;

	//��Ԍn
	Matrix mStartMat;
	Matrix mEndMat;

	float mTime;
};