#include "ManhoruEventActor06.h"

#include "../../../../Actor/EventActor/EventEnemy/EventCar/EventCar.h"
#include "../../../../Game/Time.h"

#include "../../../../Actor/EventActor/EventUtility/MoveActor.h"

#include "../../../../Sound/Sound.h"

ManhoruEventActor06::ManhoruEventActor06(IWorld & world) :
	EventActor(world)
{
}

ManhoruEventActor06::~ManhoruEventActor06()
{
}

void ManhoruEventActor06::Start()
{
	mEnemyBase = static_cast<EnemyBase*>(mWorld->findActor("Enemy").get());

	mStartY = mEnemyBase->getPosition().y;
	mEndY = mEnemyBase->getPosition().y - 12.0f;
	mLerpTime = 0.0f;
	mEnemyBase->get_animation().changeAnimation(AnimLoader::getInstance().getAnimKey(MODEL_ID::MODEL_ENEMY, (int)EnemyBase::EnemyAnimation::Manhole_Fall), false);
	Sound::GetInstance().Play3DSE(SE_ID::MANHOLE_ALIEN_VC2, (VECTOR*)&mEnemyBase->getPosition());
	Sound::GetInstance().Play3DSE(SE_ID::MANHOLE_ALIEN_DOWN, (VECTOR*)&mEnemyBase->getPosition());
	//次へ
	mTextBox->Increment_Text();
	mTextBox->Display_Text();
}

void ManhoruEventActor06::Update()
{
	mLerpTime += 5.0f* Time::GetInstance().deltaTime();
	//エネミーが落ちる
	mEnemyBase->getPosition().y = MathHelper::Lerp(mStartY, mEndY, mLerpTime);
	mLerpTime = MathHelper::Clamp(mLerpTime, 0.0f, 1.0f);
	if (mLerpTime >= 1.0f) {
		Sound::GetInstance().Play3DSE(SE_ID::MANHOLE_ALIEN_FIT, (VECTOR*)&mEnemyBase->getPosition());
		mIsEnd = true;
	}
}

void ManhoruEventActor06::Draw() const
{
}

void ManhoruEventActor06::End()
{
}
