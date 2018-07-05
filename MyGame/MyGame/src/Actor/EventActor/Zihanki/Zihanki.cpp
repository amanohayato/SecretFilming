#include "Zihanki.h"
#include "../../../Game/Time.h"

#include "../../Enemy/EnemyBase.h"
Zihanki::Zihanki(IWorld* world, std::weak_ptr<BuildingBase> zihanki) :
	Actor(world, "Zihanki", Vector3::Zero),
	mBuildingBase(zihanki)
{
}

Zihanki::~Zihanki()
{
}

void Zihanki::initialize()
{
	auto enemy = static_cast<EnemyBase*>(world_->findActor("Enemy").get());

	Vector3 enemyBack = enemy->getRotation().Backward();
	mVelo = enemyBack*Vector3(1, 0, 1);
	mVelo = mVelo.Normalize()*15.0f;
	mVelo.y = 40.0f;

}

void Zihanki::update(float deltaTime)
{
	mVelo.y -= 10.0f*Time::GetInstance().deltaTime();
	auto pos = mBuildingBase.lock();
	mBuildingBase.lock()->getPosition() += mVelo*5.0f*Time::GetInstance().deltaTime();

	mBuildingBase.lock()->getRotation()*=Matrix::CreateRotationZ(-0.5f);

}

void Zihanki::draw() const
{
}

void Zihanki::onCollide(Actor & other)
{
}
