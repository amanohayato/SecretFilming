#pragma once
#include"../../../Math/Vector3.h"
#include"../../../Math/Matrix.h"
#include"MatrixRotation.h"

class FPSCamera{
public:
	FPSCamera();//�R���X�g���N�^
	void initialize(Matrix& rotation);//����
	void update(Vector3 position);//�ʏ펞��FPS�J�����̉�]
	void EventUpdate(Vector3 position);//�C�x���g����FPS�J�����̉�]
	void StartUpdate(Vector3 position,Matrix& rotation);
	void ResetUpdate(Vector3 position);
	void camera_update(const Vector3& position,const Matrix& rotation);
	Matrix getRotation()const;//FPS�J�����̉�]�s��擾
	void SetRotation(const Matrix& mat);
	void normalReset();//�ʏ펞�̃J�������Z�b�g
	void eventReset();//�C�x���g���̃J�������Z�b�g
	MatrixRotation rotationMat_;//stick�ɂ�鎋�_�ړ�
	float& getsens();
private:
	Matrix rotation_;//FPS�J�����̉�]�s��
	Matrix endRotation_;//�C�x���g���̌Œ�p�x
};