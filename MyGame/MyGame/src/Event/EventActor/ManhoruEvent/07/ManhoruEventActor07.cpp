#include "ManhoruEventActor07.h"

#include "../../../../Actor/EventActor/EventEnemy/EventCar/EventCar.h"
#include "../../../../Game/Time.h"

#include "../../../../Actor/EventActor/EventUtility/MoveActor.h"
#include "../../../../Actor/EventActor/Ufo/EventUfo.h"

ManhoruEventActor07::ManhoruEventActor07(IWorld & world) :
	EventActor(world)
{
}

ManhoruEventActor07::~ManhoruEventActor07()
{
}

void ManhoruEventActor07::Start()
{
	mEnemyBase = static_cast<EnemyBase*>(mWorld->findActor("Enemy").get());

	Vector3 pos1 = Vector3(0, 400, 0);
	Vector3 pos2 = mEnemyBase->getPosition();
	pos2.y = 400.0f;

	auto ufo = std::make_shared<EventUfo>(mWorld, pos1, pos2);
	mWorld->addActor(ActorGroup::EVENT_ACTOR, ufo);
	mEventUfo = static_cast<EventUfo*>(ufo.get());
}

void ManhoruEventActor07::Update()
{
	mTime += Time::GetInstance().deltaTime();

	//ufo‚ªŽ‚¿ã‚°‚é–Ú“I’n‚É’…‚¢‚½‚ç
	if (mEventUfo->GetNumber() == 2) {
		mIsEnd = true;
	}
}

void ManhoruEventActor07::Draw() const
{
}

void ManhoruEventActor07::End()
{
}
