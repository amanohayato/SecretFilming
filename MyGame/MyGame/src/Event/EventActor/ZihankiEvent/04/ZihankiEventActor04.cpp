#include "ZihankiEventActor04.h"

#include "../../../../Game/Time.h"

#include "../../../../Sound/Sound.h"

ZihankiEventActor04::ZihankiEventActor04(IWorld & world) :
	EventActor(world)
{
}

void ZihankiEventActor04::Start()
{
	mEnemyBase = static_cast<EnemyBase*>(mWorld->findActor("Enemy").get());

	mTime = 0.0f;
}

void ZihankiEventActor04::Update()
{
	mTime += Time::GetInstance().deltaTime();
	mEnemyBase->get_animation().changeAnimation(AnimLoader::getInstance().getAnimKey(MODEL_ID::MODEL_ENEMY,(int)EnemyBase::EnemyAnimation::VendingMachine_Poi), false);


	//“Š‚°‚éŽžŠÔ‚É‚È‚Á‚½‚ç
	if (mTime >= 1.8f) {

		Sound::GetInstance().Play3DSE(SE_ID::VEBDINGMACHINE_HAVE_SE, (VECTOR*)&mEnemyBase->getPosition());

		mIsEnd = true;
	}
}

void ZihankiEventActor04::Draw() const
{
}

void ZihankiEventActor04::End()
{
}
