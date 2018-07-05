#pragma once

#include "../../EventActor.h"

class PoliceEventActor04 :public EventActor {
public:
	PoliceEventActor04(IWorld& world);

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
	//�x��
	ActorPtr mPolice;
	//�G�l�~�[���ړ�����x�N�g��
	Vector3 mEnemyVec;
	//�G�l�~�[���ŏ������ꏊ
	Matrix mFirstEnemyMat;
	//�U�薳�����̍s��
	Matrix mEndMat;
};