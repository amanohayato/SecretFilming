#pragma once
#include "../../EventActor.h"

class KousatenBulding;

class JunctionEventActor01 :public EventActor {
public:
	JunctionEventActor01(IWorld& world);
	~JunctionEventActor01();

	//�C�x���g�̍ŏ��Ɉ�񂾂��Ă΂��֐�
	virtual void Start() override;
	//�C�x���g���̃A�b�v�f�[�g
	virtual void Update() override;
	//�C�x���g�̕`��
	virtual void Draw()const override;
	//�C�x���g���I��������Ɉ�񂾂��Ă΂��֐�
	virtual void End() override;
private:
	ActorPtr mCar{nullptr};
	std::weak_ptr<KousatenBulding> junc_;
	float mTime{ 0.0f };
};