#pragma once
#include"../Enemy/EnemyBase.h"

class AlertGauge :public Actor {
public:
	AlertGauge(IWorld* world, std::weak_ptr<EnemyBase> enemy);

	//������
	virtual void initialize()override;
	//�X�V
	virtual void update(float deltaTime)override;
	//�`��
	virtual void draw() const override;

private:
	std::weak_ptr<EnemyBase> target_;	// �^�[�Q�b�g�|�C���^
	int cbuff_;
	float angle_{ 0.0f };				// �x���Q�[�W�̉�]�p�x�iHo Siu Ki�̒ǉ��A2018-5-29�j
	float drawRate_{ 0.0f };
	float addSign{ 1.0f };
	float excRate_{ 0.0f };
};