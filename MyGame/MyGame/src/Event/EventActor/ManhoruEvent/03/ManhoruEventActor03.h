#pragma once

#include "../../EventActor.h"

class ManhoruEventActor03 :public EventActor {
public:
	ManhoruEventActor03(IWorld& world);
	~ManhoruEventActor03();

	//�C�x���g�̍ŏ��Ɉ�񂾂��Ă΂��֐�
	virtual void Start() override;
	//�C�x���g���̃A�b�v�f�[�g
	virtual void Update() override;
	//�C�x���g�̕`��
	virtual void Draw()const override;
	//�C�x���g���I��������Ɉ�񂾂��Ă΂��֐�
	virtual void End() override;
private:
	ActorPtr mCar;
	ActorPtr mManhoru;


	float mStartY;
	float mEndY;

	float mManhoruStartY;
	float mManhoruEndY;


	//�Ԃ������グ��Ƃ��̕�ԃ^�C��
	float mLerpTime;
};