#pragma once
#include "../RandomEventBase/IRandomEvent.h"

class SignalRandomEvent : public IRandomEvent
{
public:
	// �R���X�g���N�^
	SignalRandomEvent(IWorld& world);
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
	// �R�s�[�֎~    
	SignalRandomEvent(const SignalRandomEvent& other) = delete;
	SignalRandomEvent& operator = (const SignalRandomEvent& other) = delete;

private:
	// �����_���C�x���g�̒ǉ� 
	void Add(RandomEvent name, const IRandomEventPtr& event);
	// �����_���C�x���g�̕ύX   
	void Change(RandomEvent name);

private:
	// �����_���C�x���g���
	std::unordered_map<RandomEvent, IRandomEventPtr> randomEvents_;
	// ���݂̏��
	IRandomEventPtr currentRandomEvent_;
	// ���݂̏�ԁi�񋓌^�j
	RandomEvent randomEvent_;
};