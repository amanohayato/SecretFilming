#pragma once
#include "../../Actor.h"
class MissionStart:public Actor {
public:
	// �R���X�g���N�^
	MissionStart();
	// ������
	virtual void initialize() override;
	// �X�V
	virtual void update(float delta_time) override;
	// �`��
	virtual void draw() const override;

private:
	// �\���^�C�}�[
	float mTime;
	//���l
	float mAlpha;
	//�摜�T�C�Y
	Vector2 mSize;
};