#pragma once

#include "../../EventActor.h"

class EventUfo;

class ManhoruEventActor09 :public EventActor {
public:
	ManhoruEventActor09(IWorld& world);
	~ManhoruEventActor09();

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
	ActorPtr mCar;

};