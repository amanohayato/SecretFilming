#include "PoliceEventActor05.h"

#include "../../../../Game/Time.h"

#include "../../../../Field/Building/Town/PoliceBox.h"

#include "../../../../Actor/EventActor/EventUtility/MoveActor.h"

#include "../../../../Actor/EventActor/Police/Police.h"
PoliceEventActor05::PoliceEventActor05(IWorld & world) :
	EventActor(world),
	mTime(0.0f)
{
}


void PoliceEventActor05::Start()
{
	mEnemyBase = static_cast<EnemyBase*>(mWorld->findActor("Enemy").get());
	auto manhoruBil = static_cast<PoliceBox*>(mEnemyBase->GetEventPoints().front().building_.lock().get());
	mPolice = manhoruBil->GetPolice();
}

void PoliceEventActor05::Update()
{
	auto police = static_cast<Police*>(mPolice.get());

	mTime += Time::GetInstance().deltaTime();
	//無視して歩く
	mEnemyBase->getPosition() += 15.0f*mEnemyBase->getRotation().Forward()*Time::GetInstance().deltaTime();



	//2秒後に警察が早めに歩く
	if (mTime >= 1.0f) {

		police->GetAnimation().changeAnimation(AnimLoader::getInstance().getAnimKey(MODEL_ID::MODEL_POLICE, (int)Police::PoliceAnim::POLICE_RUN_ANIM), true);

		auto pos = 50.0f*(mEnemyBase->getPosition() - police->GetMatrix().Translation()).Normalize();
		pos.y = 0.0f;
		police->GetMatrix() *= Matrix::CreateTranslation(pos*Time::GetInstance().deltaTime());
		//追い付いたら次へ
		auto dis = Vector3::Distance(mEnemyBase->getPosition(), police->GetMatrix().Translation());
		if (dis <= 20.0f) {
			mIsEnd = true;
		}
	}
}

void PoliceEventActor05::Draw() const
{
}

void PoliceEventActor05::End()
{
}
