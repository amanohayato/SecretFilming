#pragma once

#include"UI.h"

class IWorld;
class CameraUI{
public:
	//�R���X�g���N�^
	CameraUI(IWorld* world);

	//������
	void initialize();
	//�X�V
	void update(float deltaTime);
	//�`��
	void draw() const;
private:
	IWorld * world_;
	float alpha_ = 1.0f;
	bool alpha_up_ = false;
	static const int speed_ = 2;
};