#include "KituenzyoEventActor02.h"

#include "../../../../Actor/EventActor/EventUtility/MoveActor.h"

#include "../../../../Actor/EventActor/EventEnemy/EnemyHatManager/EnemyHatManager.h"

KituenzyoEventActor02::KituenzyoEventActor02(IWorld& world):
	EventActor(world)
{
}

KituenzyoEventActor02::~KituenzyoEventActor02()
{
}

void KituenzyoEventActor02::Start()
{
	mEnemyBase = static_cast<EnemyBase*>(mWorld->findActor("Enemy").get());
	
	mStartMat = mEnemyBase->getPose();
	mEndMat = mEnemyBase->getPose()*Matrix::CreateTranslation(mEnemyBase->getPose().Forward()*40.0f);

	mLerpTime = 0.0f;

	//‰Œ”­¶’Ê’m
	for (auto& b : mWorld->getBuildings()) {
		b->message(EventMessage::Play_Smoke);
	}
}

void KituenzyoEventActor02::Update()
{
	if (mEnemyBase->get_animation().isEnd())
		mIsEnd = true;
	//‰º‚ðŒü‚¢‚Ä•à‚­
	mIsEnd=MoveActor::Move(mStartMat, mEndMat);
}

void KituenzyoEventActor02::Draw() const
{
}

void KituenzyoEventActor02::End()
{
}
