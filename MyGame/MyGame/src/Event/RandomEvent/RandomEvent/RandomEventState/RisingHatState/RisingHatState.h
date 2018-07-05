#pragma once
#include "../../RandomEventBase/IRandomEvent.h"

class RisingHatState : public IRandomEvent
{
public:
	// �R���X�g���N�^
	RisingHatState(IWorld& world);
	// �J�n
	virtual void Initialize() override;
	// �X�V
	virtual void Update() override;
	// �`��
	virtual void Draw() const override;
	// �I�����Ă��邩?
	virtual bool IsEnd() const override;
	// �I��
	virtual void End() override;
	// ���̃����_���C�x���g
	virtual RandomEvent Next() const override;
private:
	std::function<void()> _seFunc;//�X�q�����
	std::function<void()> _pickupFunc;//�X�q�����
	std::function<void()> _wearFunc;//�X�q�����Ԃ�

};