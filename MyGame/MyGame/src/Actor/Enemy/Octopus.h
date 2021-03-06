#ifndef OCTOPUS_H_
#define OCTOPUS_H_

#include "EnemyBase.h"

// ^R^FlNX
// SFHo Siu Kii½âQj

class Octopus : public EnemyBase
{
public:
	// RXgN^
	Octopus(IWorld* world, const Vector3& position, const IBodyPtr& body = std::make_shared<BoundingCapsule>(Vector3{ 0.0f,0.0f,0.0f }, Matrix::Identity, 15.0f, 4.0f));
	// ú»
	void initialize() override;
	// ÚG»è
	void onCollide(Actor& other) override;
};

#endif // !OCTOPUS_H_