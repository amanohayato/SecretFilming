#pragma once
#include "../../RandomEventBase/IRandomEvent.h"

class FallDownState : public IRandomEvent
{
public:
	// �R���X�g���N�^
	FallDownState(IWorld& world);
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
	std::function<void()> voice_Func;
	std::function<bool()> _scoreUpFunc;//�X�R�A�㏸���Ăяo�����߂̊֐�
};