#include "KituenzyoEventActor04.h"

#include "../../../../Game/Time.h"

#include "../../../../Actor/EventActor/EventUtility/MoveActor.h"

#include "../../../../Actor/EventActor/EnemyBeam/EnemyBeam.h"

#include "../../../../Sound/Sound.h"

KituenzyoEventActor04::KituenzyoEventActor04(IWorld& world) :
	EventActor(world)
{
}

KituenzyoEventActor04::~KituenzyoEventActor04()
{
}

void KituenzyoEventActor04::Start()
{
	mEnemyBase = static_cast<EnemyBase*>(mWorld->findActor("Enemy").get());
	mBeam = std::make_shared<EnemyBeam>(mWorld);
	mWorld->addActor(ActorGroup::EVENT_ACTOR, mBeam);

	mTime = 0.0f;
}

void KituenzyoEventActor04::Update()
{
	mTime += Time::GetInstance().deltaTime();
	if (mTime>=3.5f) {
		mEnemyBase->setBaseScore(20);
		Sound::GetInstance().StopSE(SE_ID::SMOKE_BEAM_CHARGE_SE);
		Sound::GetInstance().Play3DSE(SE_ID::SMOKE_BEAM_SE, (VECTOR*)&mEnemyBase->getPosition());
		static_cast<EnemyBeam*>(mBeam.get())->SetIsBeam(true);
		mIsEnd = true;
	}
}

void KituenzyoEventActor04::Draw() const
{
}

void KituenzyoEventActor04::End()
{
}
