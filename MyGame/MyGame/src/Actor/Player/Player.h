#pragma once
#include"../Actor.h"
#include"../../Graphic/AnimationDx.h"
#include"../Body/BoundingCapsule.h"
#include"../../Method/CountTimer.h"
#include"Base/MatrixRotation.h"
#include"Base\Player_arm.h"
#include"Base\FPSCamera.h"
#include"State\PlayerState.h"
#include<memory>

class Player:public Actor {
public:
	enum class Player_Animation {
		Idle=0,
		Run=1,
		Jump=3,
		Slide=5,
		SlideJump=3,
		Float=3,
		Blow=7,
		Down = 8,
		GetUp = 9,
		Fly=6,
		WallRun=1,
		FloatJump = 3,
		FloatFall = 3,
		Fall=3,

	};

public:
	Player(IWorld* world, const Vector3& position, const IBodyPtr& body = std::make_shared<BoundingCapsule>(Vector3{0.0f,0.0f,0.0f},Matrix::Identity,15.0f,4.0f));
	Player(IWorld* world, const Vector3& position,const Matrix& rotation, const IBodyPtr& body = std::make_shared<BoundingCapsule>(Vector3{ 0.0f,0.0f,0.0f }, Matrix::Identity, 15.0f, 4.0f));

	void initialize();

	void update(float deltaTime);

	void draw()const;

	virtual void onCollide(Actor& other);
	//���b�Z�[�W�̎�M
	virtual void receiveMessage(EventMessage message, void* param) override;
	//�v���C���[���
	Player_State_ID getStateType()const;
	//���_�̎擾
	FPSCamera& getFPSCamera();
	//�r�̎擾
	Player_arm& getArm();
private:

	//��Ԃ̍X�V
	bool change_State(Player_State_ID state);
	//��Ԃ̎擾
	std::shared_ptr<PlayerState> getState(Player_State_ID state);
	//����I�u�W�F�N�g
	void hide_InCamera(BuildingBase& object);
	//�Փ˃��A�N�V����
	void hit(Vector3& dir);
	//�ǂƏ��̔���
	void collision();
	//�^�C���̔���
	void roadway();
private:
	//�v���C���[���
	std::shared_ptr<PlayerState> state_;
	// �J�����p�̉�]�s��
	Matrix cameraRotation_{ Matrix::Identity };
	//�C�x���g�p�̉�]�s��(��)
	Matrix mat_{Matrix::Identity};
	//�l���X�R�A
	int score_{ 1 };
	//�C�x���g
	EventType type_{EventType::EVENT_NULL};
	//�C�x���g�̏��
	EventAction_State eventActionState_;
	//�v���C���[���_
	FPSCamera fpsCam_;
	//�v���C���[�r
	Player_arm arm_;

	CsvReader roadway_;//�ԓ�CSV�ǂݍ��ݗp
	Vector3 beforpos_;//�|�W�V�������L�^
	
	bool collide{ false };
	//��{�I��velocity�̏�Z����
	const float DefVelocityMult{ 0.8f };

	float velocityMultPower{ DefVelocityMult };

};