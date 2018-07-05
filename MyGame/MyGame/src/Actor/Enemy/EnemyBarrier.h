#ifndef ENEMY_BARRIER_H_
#define ENEMY_BARRIER_H_

#include "../Actor.h"

// �G�l�~�[�̃o���A�N���X
// �S���FHo Siu Ki�i�����Q�j
class EnemyBarrier : public Actor
{
public:
	// �R���X�g���N�^
	EnemyBarrier(ActorPtr target,ActorPtr enemy,Vector3 position, Matrix rotation,bool isStop = false);
	// ������
	void initialize() override;
	// �X�V
	void update(float delta_time) override;
	// �`��
	void draw() const override;
private:
	// �^�[�Q�b�g�i�G�l�~�[�j
	ActorPtr target_;
	ActorPtr enemy_;
	// �\���^�C�}�[
	float timer_{ 1.0f };
	bool isStop_{ false };
};

#endif // !ENEMY_BARRIER_H_