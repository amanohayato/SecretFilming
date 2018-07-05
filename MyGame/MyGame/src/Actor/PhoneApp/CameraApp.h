#pragma once
#include"../Actor.h"

// �J�����A�v���̏��
enum class CameraAppState
{
	// �X���[�v��
	Sleep,

	// �N����
	Active
};

class CameraApp : public Actor
{
public:

	CameraApp(IWorld * world, ActorPtr player);

	void initialize();

	void update(float deltaTime);

	void draw()const;

	//���b�Z�[�W�̎�M
	virtual void receiveMessage(EventMessage message, void* param) override;

	// �X�R�A���v�Z����֐�
	int scoreCalculation();

	// �J�����A�v���̏�Ԃ̕ύX
	void changeState(CameraAppState state);

	void active();
	void sleep();
private:

	// ���݂̃J�����A�v���̏��
	CameraAppState curState_{ CameraAppState::Sleep };

	// �e�v�f�ł���v���C���[
	ActorPtr player_;

	// �ʐ^�̎B�e�ő勗��
	static const float shootingRange_;

	// �ʐ^�̎B�e�ő�p�x
	static const float shootingAngle_;

	float frameSetRate{ 0.0f };//�g�Z�b�g�܂ł̎���
};