#include "ZihankiEventActor02.h"

ZihankiEventActor02::ZihankiEventActor02(IWorld & world) :
	EventActor(world)
{
}

void ZihankiEventActor02::Start()
{
	mEnemyBase = static_cast<EnemyBase*>(mWorld->findActor("Enemy").get());


}

void ZihankiEventActor02::Update()
{
	mEnemyBase->get_animation().changeAnimation(AnimLoader::getInstance().getAnimKey(MODEL_ID::MODEL_ENEMY, (int)EnemyBase::EnemyAnimation::VendingMachine), false);


	//アニメーション終わったかどうか
	if (mEnemyBase->get_animation().isEnd())
		mIsEnd = true;
}

void ZihankiEventActor02::Draw() const
{
}

void ZihankiEventActor02::End()
{
}
