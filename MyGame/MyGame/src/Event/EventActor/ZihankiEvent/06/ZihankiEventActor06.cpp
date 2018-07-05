#include "ZihankiEventActor06.h"

#include "../../../../Game/Time.h"

#include "../../../../Actor/EventActor/Zihanki/Zihanki.h"

ZihankiEventActor06::ZihankiEventActor06(IWorld & world) :
	EventActor(world)
{
}

void ZihankiEventActor06::Start()
{
	mEnemyBase = static_cast<EnemyBase*>(mWorld->findActor("Enemy").get());
	mEnemyBase->get_animation().changeAnimation(AnimLoader::getInstance().getAnimKey(MODEL_ID::MODEL_ENEMY, (int)EnemyBase::EnemyAnimation::Aware), false);
}

void ZihankiEventActor06::Update()
{
	//見まわし
	if (mEnemyBase->get_animation().isEnd()) {
		mIsEnd = true;
	}
}

void ZihankiEventActor06::Draw() const
{
}

void ZihankiEventActor06::End()
{
	//イベント終了
	mEnemyBase->set_is_event(false);
}
