#ifndef NOTICED_LINE_H_
#define NOTICED_LINE_H_

#include"../Enemy/EnemyBase.h"

// �C�Â����N���X
// �S���FHo Siu Ki�i�����Q�j
class NoticedLine : public Actor
{
public:
	// �R���X�g���N�^
	NoticedLine(ActorPtr target);
	// ������
	virtual void initialize() override;
	// �X�V
	virtual void update(float delta_time) override;
	// �`��
	virtual void draw() const override;

private:
	// �^�[�Q�b�g
	ActorPtr target_;
	// �\���^�C�}�[
	float timer_{ 1.0f };
};

#endif // !NOTICED_LINE_H_