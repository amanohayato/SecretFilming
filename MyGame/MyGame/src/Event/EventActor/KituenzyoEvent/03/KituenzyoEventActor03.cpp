#include "KituenzyoEventActor03.h"

#include "../../../../Actor/EventActor/EventUtility/MoveActor.h"

#include "../../../../Sound/Sound.h"

KituenzyoEventActor03::KituenzyoEventActor03(IWorld& world):
	EventActor(world)
{
}

KituenzyoEventActor03::~KituenzyoEventActor03()
{
}

void KituenzyoEventActor03::Start()
{
	mEnemyBase = static_cast<EnemyBase*>(mWorld->findActor("Enemy").get());
	mEnemyBase->get_animation().changeAnimation(AnimLoader::getInstance().getAnimKey(MODEL_ID::MODEL_ENEMY, (int)EnemyBase::EnemyAnimation::Me_Mogaki), false);
	
	Sound::GetInstance().Play3DSE(SE_ID::SMOKE_BEAM_CHARGE_SE, (VECTOR*)&mEnemyBase->getPosition());
	mTextBox->add("SmokeEvent/smoking1.txt");
	mTextBox->Start_Text();
	//auto time = mEnemyBase->get_animation().getGetCurrentAnimTime();
	//int a = 0;
}

void KituenzyoEventActor03::Update()
{
	//もがくアニメーション再生
	mIsEnd = true;
}

void KituenzyoEventActor03::Draw() const
{
}

void KituenzyoEventActor03::End()
{
}
