#ifndef SEND_EVENT_TO_ENEMY_H_
#define SEND_EVENT_TO_ENEMY_H_

#include <memory>
#include "BuildingBase.h"

struct EventPoint
{
	std::weak_ptr<BuildingBase> building_;
	Vector3 position_;

	//�}���z�[���C�x���g�p
	Vector3 position2_;


	int block_;
};

#endif // !SEND_EVENT_TO_ENEMY_H_

