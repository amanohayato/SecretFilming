#include "ManhoruEventActor08.h"

#include "../../../../Actor/EventActor/EventEnemy/EventCar/EventCar.h"
#include "../../../../Game/Time.h"

#include "../../../../Actor/EventActor/EventUtility/MoveActor.h"
#include "../../../../Actor/EventActor/Ufo/EventUfo.h"

#include "../../../../Sound/Sound.h"

ManhoruEventActor08::ManhoruEventActor08(IWorld & world) :
	EventActor(world)
{
}

ManhoruEventActor08::~ManhoruEventActor08()
{
}

void ManhoruEventActor08::Start()
{
	mEnemyBase = static_cast<EnemyBase*>(mWorld->findActor("Enemy").get());

	mStartY = mEnemyBase->getPosition().y;
	mEndY = mStartY + 20.0f;
	mLerpTime = 0.0f;

	mEnemyBase->get_animation().changeAnimation(AnimLoader::getInstance().getAnimKey(MODEL_ID::MODEL_ENEMY, (int)EnemyBase::EnemyAnimation::Manhole_Rescue), false);

	//次へ
	mTextBox->Increment_Text();

	mEventUfo = static_cast<EventUfo*>(mWorld->findActor("Ufo").get());

	//ここからスコアエリア
	mEnemyBase->setBaseScore(20);
	Sound::GetInstance().Play3DSE(SE_ID::UFO_ABDUCTION_SE, (VECTOR*)&mEnemyBase->getPosition());
}

void ManhoruEventActor08::Update()
{
	//UFOによってエネミーが持ち上がる
	mLerpTime += Time::GetInstance().deltaTime();
	mEnemyBase->getPosition().y = MathHelper::Lerp(mStartY, mEndY, mLerpTime);

	mLerpTime = MathHelper::Clamp(mLerpTime, 0.0f, 1.0f);
	//ufoが移動する瞬間
	if (mEventUfo->GetNumber()==3) {
		Sound::GetInstance().StopSE(SE_ID::UFO_ABDUCTION_SE);
		mIsEnd = true;
	}
}

void ManhoruEventActor08::Draw() const
{
}

void ManhoruEventActor08::End()
{
}
