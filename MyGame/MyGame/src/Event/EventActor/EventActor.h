#pragma once

#include "../../World/IWorld.h"

#include "../../Actor/Enemy/EnemyBase.h"
#include "../../Graphic/TextBox.h"
//�ŉ��w�C�x���g(�C�x���g���ׂ̍����s��)	
class EventActor {
public:
	//�R���X�g���N�^
	EventActor(IWorld& world) :mWorld(&world), mIsEnd(false), mEventIsEnd(false) {};
	virtual ~EventActor() {};
	//�C�x���g�̍ŏ��Ɉ�񂾂��Ă΂��֐�
	virtual void Start() = 0;
	//�C�x���g���̃A�b�v�f�[�g
	virtual void Update() = 0;
	//�C�x���g�̕`��
	virtual void Draw()const = 0;
	//�C�x���g���I��������Ɉ�񂾂��Ă΂��֐�
	virtual void End() = 0;

	//�I��������ǂ����H
	bool GetIsEnd() { return mIsEnd; };
	//�C�x���g���̏I��点�邩
	bool GetEventIsEnd() { return mEventIsEnd; };
	//�e�L�X�g�{�b�N�X���Z�b�g����
	void SetTextBox(std::shared_ptr<TextBox> textBox) { mTextBox = textBox; };
protected:
	//���[���h
	IWorld* mWorld;
	//���̃C�x���g���I������ꍇ
	bool mIsEnd;

	//�������ɃC�x���g�ɓ������p
	bool mEventIsEnd;

	//�G�l�~�[�x�[�X
	EnemyBase* mEnemyBase;

	//�e�L�X�g�{�b�N�X
	std::shared_ptr<TextBox> mTextBox;
};