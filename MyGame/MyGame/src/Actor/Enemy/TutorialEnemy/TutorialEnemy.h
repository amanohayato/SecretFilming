#pragma once

#include "../EnemyBase.h"

class TutorialEnemy : public EnemyBase
{
public:
	// �R���X�g���N�^
	TutorialEnemy(IWorld* world, const Vector3& position, const IBodyPtr& body = std::make_shared<BoundingCapsule>(Vector3{ 0.0f,0.0f,0.0f }, Matrix::Identity, 15.0f, 4.0f));
	
	void update(float delta_time_) override;
	
	// �ڐG����
	void onCollide(Actor& other) override;

	void changeSpeed(float normal_speed, float escape_speed);

	void changeTimer(float timer);

	void changeRandomEventFlag(bool flag);

	void setTutorialMovePoint();

	// ���b�ŕ����̂���߂邩��ݒ肷��
	void setStopTimer(float value);

	// ���b�ŕ����̂���߂邩�̃^�C�}�[�𖳗͉�����
	void InactiveStopTimer();

	// �x���x���㏸�����Ȃ����̃t���O��ύX
	void SetInactiveAwareness(bool flag);

private:

	bool activeStopTimer_{ false };

	// �x���x���㏸�����Ȃ����̃t���O
	bool inactiveAwareness_{ false };

	// ���b�ŕ����̂���߂邩�̃^�C�}�[
	float stopTimer_{ 0.0f };

};