#pragma once
#include"../Base/FPSCamera.h"
#include"../../../Math/Matrix.h"
#include"../../../Math/Vector3.h"
#include"../../../World/IWorld.h"
#include"../../Actor.h"
#include"State_ID.h"
#include<memory>
//�v���C���[�X�e�[�g���N���X
class PlayerState : public std::enable_shared_from_this<PlayerState> {
public:
	//�R���X�g���N�^
	PlayerState() = default;
	PlayerState(ActorPtr player);
	PlayerState(IWorld* world, ActorPtr player);
	//���z�f�X�g���N�^
	virtual ~PlayerState() {}
	//�J�n
	virtual void start();
	//�X�V
	virtual void update(float deltaTime);
	//�I��
	virtual void end();
	//���͂��ړ���
	void input_to_move(float deltaTime);
	//���ɂ��Ă��邩
	void setFloor(bool prevfloor);
	//���̏��
	Player_State_ID getState()const;
	//���̏��
	Player_State_ID getNextState()const;
	//�J�������
	FPSCamera getFPSCam()const;
	//�d�͂̎擾
	float getGravity()const;
	//�t���O
	bool isCamera()const;
	bool isAction()const;

	void setIsWatch(const bool& isWatch);
	bool getIsWatch()const;
	//�J�������̃Z�b�g
	void setFPSCam(FPSCamera cam);
	//�C�x���g
	void setObjct(const Vector3& position,const Matrix& rotation);
protected:
	//���[���h
	IWorld * world_{ nullptr };
	//�v���C���[
	ActorPtr player_{nullptr};
	//���̏��
	Player_State_ID state_{Player_State_ID::Idle};
	//���̏��(�f�t�H���gNULL)
	Player_State_ID nextState_{ Player_State_ID::Null };

	//�v���C���[�̈ʒu�ۊ�
	Vector3 playerPositionStr_{ Vector3::Zero };
	//����I�u�W�F�N�g�̈ʒu�ۊ�
	Vector3 objPositionStr_{ Vector3::Zero };
	//�J����
	FPSCamera& fpsCam_;
	//��]�s��
	Matrix rotation_{Matrix::Identity};
	Matrix objRotation_{ Matrix::Identity };
	// �ړ����x�̒l�i�f�t�H���g100.0f�j
	float moveSpeed_{ 30.0f };
	//�O�t�����ɂ��Ă���
	bool prevfloor_{ true };
	//�J������Ԃ�
	bool isCamera_{ false };
	//�A�N�V������Ԃ�
	bool isAction_{ false };
	//�I�u�W�F�N�g�����Ă��邩
	bool isWatch_{ false };
	//�d�͔{��
	float gravity_{ 0.0f };
};