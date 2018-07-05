#include "PoliceEventActor01.h"

#include "../../../../Game/Time.h"

PoliceEventActor01::PoliceEventActor01(IWorld & world):
	EventActor(world),
	mTime(0.0f)
{

}



void PoliceEventActor01::Start()
{
	mEnemyBase = static_cast<EnemyBase*>(mWorld->findActor("Enemy").get());

}

void PoliceEventActor01::Update()
{
	auto ptr = mEnemyBase->GetEventPoints().front();

	//‚±‚±‚ÉŠJŽnˆ—
	if (mEnemyBase->isPathEnd()&&
		ptr.building_.lock()->getEvent() == EventType::EVENT_POLICE) {

		//‚à‚µ“¦‘–’†‚È‚ç–³Ž‹
		if (mEnemyBase->get_state() == EnemyBase::EnemyState::Escape) {
			mEventIsEnd = true;
			return;
		}

		mEnemyBase->set_is_event(true);

		mIsEnd = true;
	}

}

void PoliceEventActor01::Draw() const
{

}

void PoliceEventActor01::End()
{
	int a = 0;
}
