#pragma once

#include "../../EventActor.h"

class ManhoruEventActor02 :public EventActor {
public:
	ManhoruEventActor02(IWorld& world);
	~ManhoruEventActor02();

	//�C�x���g�̍ŏ��Ɉ�񂾂��Ă΂��֐�
	virtual void Start() override;
	//�C�x���g���̃A�b�v�f�[�g
	virtual void Update() override;
	//�C�x���g�̕`��
	virtual void Draw()const override;
	//�C�x���g���I��������Ɉ�񂾂��Ă΂��֐�
	virtual void End() override;
private:
	EventType mEventType;

	std::function<void()> isEndFunc_;

};