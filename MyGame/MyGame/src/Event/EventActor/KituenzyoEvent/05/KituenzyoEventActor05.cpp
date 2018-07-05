#include "KituenzyoEventActor05.h"

#include "../../../../Actor/EventActor/EventUtility/MoveActor.h"

#include "../../../../Game/Time.h"

#include "../../../../Actor/EventActor/EnemyBeam/EnemyBeam.h"

KituenzyoEventActor05::KituenzyoEventActor05(IWorld& world):
	EventActor(world)
{
}

KituenzyoEventActor05::~KituenzyoEventActor05()
{
}

void KituenzyoEventActor05::Start()
{
	mEnemyBase = static_cast<EnemyBase*>(mWorld->findActor("Enemy").get());

	mTextBox->Hidden_Text();

	mBeam = mWorld->findActor("EnemyBeam");
	mTime = 0.0f;
}

void KituenzyoEventActor05::Update()
{
	mTime += Time::GetInstance().deltaTime();
	if (mTime >= 1.0f) {
		static_cast<EnemyBeam*>(mBeam.get())->SetIsBeam(false);
		mEnemyBase->setBaseScore(0);
		if (mEnemyBase->get_animation().isEnd())
			mIsEnd = true;
	}

}

void KituenzyoEventActor05::Draw() const
{
}

void KituenzyoEventActor05::End()
{
	mTextBox->End();

}
