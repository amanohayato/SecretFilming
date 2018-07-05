#include "NekoEventActor03.h"

NekoEventActor03::NekoEventActor03(IWorld & world):
	EventActor(world)
{
}

NekoEventActor03::~NekoEventActor03()
{

}

void NekoEventActor03::Start()
{
	mEnemyBase = static_cast<EnemyBase*>(mWorld->findActor("Enemy").get());
	mEnemyBase->get_animation().changeAnimation(AnimLoader::getInstance().getAnimKey(MODEL_ID::MODEL_ENEMY, (int)EnemyBase::EnemyAnimation::LOOK_UP), false,0.3f);
	ufo_ = std::static_pointer_cast<AbductUfo>(mWorld->findActor("AbductUfo"));
	ufo_.lock()->begin();

}

void NekoEventActor03::Update()
{
	//mIsEnd = mEnemyBase->get_animation().isEnd();
	
	mIsEnd = (ufo_.expired());
}

void NekoEventActor03::Draw() const
{
}

void NekoEventActor03::End()
{

}
