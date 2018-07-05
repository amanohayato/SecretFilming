#include "PoliceEventActor08.h"

#include "../../../../Game/Time.h"

#include "../../../../Field/Building/Town/PoliceBox.h"

#include "../../../../Actor/EventActor/EventUtility/MoveActor.h"

#include "../../../../Actor/EventActor/Police/Police.h"

#include "../../../../Sound/Sound.h"
PoliceEventActor08::PoliceEventActor08(IWorld & world) :
	EventActor(world),
	mTime(0.0f)
{
}


void PoliceEventActor08::Start()
{
	mEnemyBase = static_cast<EnemyBase*>(mWorld->findActor("Enemy").get());
	auto manhoruBil = static_cast<PoliceBox*>(mEnemyBase->GetEventPoints().front().building_.lock().get());
	mPolice = manhoruBil->GetPolice();
	auto police = static_cast<Police*>(mPolice.get());

	mEnemyBase->get_animation().changeAnimation(AnimLoader::getInstance().getAnimKey(MODEL_ID::MODEL_ENEMY, (int)EnemyBase::EnemyAnimation::Idle), false);
	police->GetAnimation().changeAnimation(AnimLoader::getInstance().getAnimKey(MODEL_ID::MODEL_POLICE, (int)Police::PoliceAnim::POLICE_RUN_ANIM), true);
	Sound::GetInstance().Play3DSE(SE_ID::POLICE_RETURN_VC, (VECTOR*)&mEnemyBase->getPosition());
	mTextBox->Hidden_Text();
}

void PoliceEventActor08::Update()
{
	auto police = static_cast<Police*>(mPolice.get());
	mIsEnd = MoveActor::Move(police->GetMatrix(), police->GetStartMat());

}

void PoliceEventActor08::Draw() const
{

}

void PoliceEventActor08::End()
{
	auto police = static_cast<Police*>(mPolice.get());

	//I‚í‚Á‚½‚çŒ©‰ñ‚·
	police->GetAnimation().changeAnimation(AnimLoader::getInstance().getAnimKey(MODEL_ID::MODEL_POLICE, (int)Police::PoliceAnim::POLICE_IDLE_ANIM), true);
	mTextBox->End();
}
