#include "JunctionEventActor02.h"
#include "../../../../Actor/EventActor/EventUtility/MoveActor.h"

JunctionEventActor02::JunctionEventActor02(IWorld & world) :
	EventActor(world)
{
}

void JunctionEventActor02::Start()
{
	mEnemyBase = static_cast<EnemyBase*>(mWorld->findActor("Enemy").get());
	mCar = mWorld->findActor("JunctionCar");
	mEnemyBase->get_animation().changeAnimation(AnimLoader::getInstance().getAnimKey(MODEL_ID::MODEL_ENEMY, (int)EnemyBase::EnemyAnimation::Idle), false);
}

void JunctionEventActor02::Update()
{
	float dis = Vector2::Distance(Vector2{ mEnemyBase->getPosition().x,mEnemyBase->getPosition().z }, Vector2{ mCar->getPosition().x,mCar->getPosition().z });
	if (dis < 150.0f) {
		mIsEnd = true;
	}

}

void JunctionEventActor02::Draw() const
{
	DebugDraw::DebugDrawFormatString(720, 300, GetColor(255, 255, 255), "%f,%f", mCar->getPosition().x,mCar->getPosition().z);
}

void JunctionEventActor02::End()
{
}
