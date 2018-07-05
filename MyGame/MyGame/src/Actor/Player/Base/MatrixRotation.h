#pragma once
#include"../../../Math/Matrix.h"
#include"../../../Input/InputChecker.h"
#include"../../../Math/MathHelper.h"
#include"../../../Math/Quaternion.h"

class MatrixRotation {
public:
	MatrixRotation();
	void initialize(Matrix& rotation);
	Matrix update();
	Matrix eventUpdate();
	Matrix resetOnlyUpdate();
	void move(const bool& limit);
	void SetEventRotation(const Matrix& mat);
	void NormalReset(const Matrix& mat);
	void EventReset(const Matrix& start);
	float& sens();
private:
	float verticalangle_{ 0.f };//x���̊p�x
	float horizontalangle_{ 0.f };//�����̊p�x
	float amount{ 0.0f };//Lerp�̃p�[�Z���g
	bool is_normalReset{ false };//�ʏ펞�̃��Z�b�g����
	bool is_eventReset{ false };//�C�x���g���̃��Z�b�g����
	Matrix endInitializeRotation{ Matrix::Identity };//Lerp�̃G���h
	float start_x{ 0.0f };
	float start_y{ 0.0f };
	float eRot{ 0.0f };
	float sens_{0.5f};
};