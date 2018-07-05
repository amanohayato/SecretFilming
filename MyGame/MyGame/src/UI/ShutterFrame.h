#pragma once

#include"UI.h"

class IWorld;
class ShutterFrame {
public:
	//�R���X�g���N�^
	ShutterFrame(IWorld* world);

	//������
	void initialize();
	//�X�V
	void update(float deltaTime);
	//�`��
	void draw(Vector2& position, Vector2& size) const;
private:
	IWorld * world_;
	float amount{ 1.0f };
	float alpha{ 0.0f };
};