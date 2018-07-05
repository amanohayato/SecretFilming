#pragma once

#include "../../Actor.h"


class TitleUfo :public Actor {

public:
	TitleUfo(IWorld* world, const Vector3& pos1, const Vector3& pos2);

	virtual ~TitleUfo() override;

	virtual void initialize() override;

	virtual void update(float deltaTime) override;

	virtual void draw()const override;

private:

	// �J�n���W
	Vector3 startPos_;

	// �I�����W
	Vector3 goalPos_;

	// ���J�E���g�Ŏ��g����������\���J�E���^
	int deleteTimer_;

	// �ړ����x
	const float moveSpeed_ = { 3.0f };
};