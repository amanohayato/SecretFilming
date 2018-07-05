#pragma once
#include"UI.h"

class IWorld;
class Action :public UI {
public:
	//�R���X�g���N�^
	Action(IWorld* world,const Vector2& position);

	//������
	virtual void initialize()override;
	//�X�V
	virtual void update(float deltaTime)override;
	//�`��
	virtual void draw() const override;
private:
	IWorld * world_;
	float amount{ 0.0f };
	bool is_Action{ false };
	float alpha{ 0.0f };
};