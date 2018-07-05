#pragma once

#include "Body.h"

// ����Ȃ�Body
class DummyBody : public Body{
public:
	// �R���X�g���N�^
	DummyBody() {}
	// Body�̕��s�ړ�
	virtual IBodyPtr translate(const Vector3& position) const override { return std::make_shared<DummyBody>(); }
	// Body�̕ϊ�
	virtual IBodyPtr transform(const Matrix& matrix) const override { return std::make_shared<DummyBody>(); }
	// �Փ˔���
	virtual bool isCollide(const IBody& other, HitInfo& hitinfo) const override { return false; }
	// �Փ˔���(��)
	virtual bool intersects(const BoundingSphere& other, HitInfo& hitinfo) const override { return false; }
	// �Փ˔���(�J�v�Z��)
	virtual bool intersects(const BoundingCapsule& other, HitInfo& hitinfo) const override { return false; }
	// �Փ˔���(����)
	virtual bool intersects(const BoundingSegment& other, HitInfo& hitinfo) const override { return false; }
	// �Փ˔���(AABB)
	virtual bool intersects(const BoundingBox& other, HitInfo& hitinfo) const override { return false; }
	// �Փ˔���(OBB)
	virtual bool intersects(const OrientedBoundingBox& other, HitInfo& hitinfo) const override { return false; }
	// �Փ˔���(���C)
	virtual bool intersects(const Ray& other, HitInfo& hitinfo) const override { return false; }
	// �Փ˔���(���f��)
	virtual bool intersects(const CollisionModel& other, HitInfo& hitinfo) const override { return false; }
	// �}�`�`��
	virtual void draw() const override{}
	virtual void draw(const Vector3& position) const override{}
};