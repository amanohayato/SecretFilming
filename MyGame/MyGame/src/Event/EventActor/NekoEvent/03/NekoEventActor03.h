#pragma once

#include "../../EventActor.h"
#include"../../../../Actor/EventActor/AbductUfo/AbductUfo.h"

class NekoEventActor03 :public EventActor {
public:
	NekoEventActor03(IWorld& world);
	~NekoEventActor03();

	//�C�x���g�̍ŏ��Ɉ�񂾂��Ă΂��֐�
	virtual void Start() override;
	//�C�x���g���̃A�b�v�f�[�g
	virtual void Update() override;
	//�C�x���g�̕`��
	virtual void Draw()const override;
	//�C�x���g���I��������Ɉ�񂾂��Ă΂��֐�
	virtual void End() override;
private:
	std::weak_ptr<AbductUfo> ufo_;
};