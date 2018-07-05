#pragma once
#include "../RandomEventBase/RandomEvent.h"
#include "../../../../World/IWorld.h"
#include "../../../../Actor/Enemy/EnemyBase.h"
#include "../../../../Actor/UIActor/TextActor.h"

class IRandomEvent
{
public:
	// ������
	virtual void Initialize() = 0;
	// �X�V
	virtual void Update() = 0;
	// �`��
	virtual void Draw() const = 0;
	// �I�����Ă��邩�H
	virtual bool IsEnd() const = 0;
	// �I��
	virtual void End() = 0;
	// ���̃����_���C�x���g
	virtual RandomEvent Next() const = 0;

protected:
	// ���[���h
	IWorld* world_;
	// �G�l�~�[
	std::weak_ptr<EnemyBase> enemyBase_;
	//�e�L�X�g�{�b�N�X
	std::shared_ptr<TextBox> textBox_;
	// �I���t���O
	bool isEnd_;
};