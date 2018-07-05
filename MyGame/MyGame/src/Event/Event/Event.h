#pragma once

#include "../EventActor/EventActor.h"
#include "../EventManager/EventManager.h"

#include <vector>

#include "../../Graphic/TextBox.h"

#include "../../Actor/Enemy/EnemyBase.h"
//���������w�C�x���g(�C�x���g����)

class Event {
public:
	//�R���X�g���N�^
	Event(IWorld & world);
	//�f�X�g���N�^
	~Event();
	//��ԍׂ����C�x���g�̒ǉ�(�C�x���g�̒ǉ��������̂܂ܔ��f�����̂Œ���)
	void Add(EventActor* e);
	//�A�b�v�f�[�g
	void Update();
	//�`��
	void Draw() const;
	//���̃C�x���g�֐i��
	void NextEvent();
	//�C�x���g�������`�F���W���ꂽ�Ƃ��Ă΂��
	void ResetEvent();
	//�C�x���g���I��������ǂ���
	bool GetIsEventEnd();
	//�e�L�X�g�{�b�N�X�\�������邩
	void SetIsDrawTextBox(bool flag);
private:
	//�C�x���g����
	std::vector<EventActor*> mEvents;
	//�C�x���g���ǂ̂��炢�i�񂾂�
	int mEventNum;
	//���O�̃C�x���g�ԍ�
	int mBeforeEventNum;
	//���̃C�x���g���I��������ǂ����H
	bool mIsEnd;
	//�e�L�X�g�{�b�N�X
	std::shared_ptr<TextBox> mTextBox;
	//�e�L�X�g�{�b�N�X�\�������邩
	bool mIsDrawTextBox;
	//�ŏ������̃t���O
	bool mFirstStartFlag;
	ActorPtr mEnemy;
	ActorPtr mPlayer;
	IWorld* mWorld;
	int mAlpha;
};