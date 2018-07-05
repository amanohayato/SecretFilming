#include "JunctionEventActor03.h"
#include "../../../../Game/Time.h"
#include"../../../../Actor/Car/Car.h"

JunctionEventActor03::JunctionEventActor03(IWorld & world):
	EventActor(world)
{
}

void JunctionEventActor03::Start()
{
	mEnemyBase = static_cast<EnemyBase*>(mWorld->findActor("Enemy").get());
	mCar = static_cast<Car*>(mWorld->findActor("JunctionCar").get());

	Vector3 target_position = mCar->getPosition() - mEnemyBase->getPosition();
	target_position = target_position.Normalize();

	mCar->hit_Enemy(mCar->getPosition() - mEnemyBase->getPosition());

	mEnemyBase->on_Barrier(mWorld->findActor("JunctionCar"), mWorld->findActor("Enemy"),true);
	mEnemyBase->setBaseScore(20);
	mTextBox->add("Junction/intercept1.txt");
	mTextBox->Start_Text();
}

void JunctionEventActor03::Update()
{
	mTime += Time::GetInstance().deltaTime();
	if (mTime > 5.0f) {
		mIsEnd = true;
	}
}

void JunctionEventActor03::Draw() const
{
}

void JunctionEventActor03::End()
{
		mEnemyBase->setBaseScore(0);
		mTextBox->End();
}
