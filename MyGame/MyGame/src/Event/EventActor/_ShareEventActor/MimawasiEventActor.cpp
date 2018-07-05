#include "MimawasiEventActor.h"

#include "../../../Game/Time.h"

#include "../../../Actor/EventActor/Zihanki/Zihanki.h"
#include"../../../Sound/Sound.h"

MimawasiEventActor::MimawasiEventActor(IWorld & world) :
	EventActor(world)
{
}

void MimawasiEventActor::Start()
{
	mEnemyBase = static_cast<EnemyBase*>(mWorld->findActor("Enemy").get());
	mEnemyBase->get_animation().changeAnimation(AnimLoader::getInstance().getAnimKey(MODEL_ID::MODEL_ENEMY, (int)EnemyBase::EnemyAnimation::Aware), false);
	Sound::GetInstance().Play3DSE(SE_ID::ALIAN_VOICE_SE, (VECTOR*)&mEnemyBase->getPosition());
}

void MimawasiEventActor::Update()
{
	//見まわし
	if (mEnemyBase->get_animation().isEnd()) {
		mIsEnd = true;
	}
}

void MimawasiEventActor::Draw() const
{
}

void MimawasiEventActor::End()
{
	//イベント終了
	mEnemyBase->set_is_event(false);
	mEnemyBase->setNextEvent();
}
