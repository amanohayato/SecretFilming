#include "CheckPoint.h"
#include"../Body/BoundingSphere.h"
#include"../../ID/EnumIDs.h"

CheckPoint::CheckPoint(IWorld * world, const Vector3 & position):
	Actor(world, "Point", position, std::make_shared<BoundingSphere>(0.0f, 5.0f)) {

}

void CheckPoint::update(float deltaTime)
{
}

void CheckPoint::draw() const
{
	body_->transform(getPose())->draw();

}

void CheckPoint::onCollide(Actor & other)
{
	//�v���C���[�ƐڐG�����玀��
	if (other.getGroup() == ActorGroup::PLAYER_ACTOR) {
		isDead_ = true;
	}
}
