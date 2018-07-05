#include "ZihankiEventActor05.h"

#include "../../../../Game/Time.h"

#include "../../../../Actor/EventActor/Zihanki/Zihanki.h"

#include "../../../../Sound/Sound.h"

ZihankiEventActor05::ZihankiEventActor05(IWorld & world) :
	EventActor(world)
{
}

void ZihankiEventActor05::Start()
{
	mEnemyBase = static_cast<EnemyBase*>(mWorld->findActor("Enemy").get());

	//ここで自販機を飛ばす
	mWorld->addActor(ActorGroup::ZIHANKI_ACTOR, std::make_shared<Zihanki>(mWorld, mEnemyBase->GetEventPoints().front().building_));

	Sound::GetInstance().Play3DSE(SE_ID::VEBDINGMACHINE_THROW_SE, (VECTOR*)&mEnemyBase->getPosition());

	//ここからスコアエリア
	mEnemyBase->setBaseScore(20);
}

void ZihankiEventActor05::Update()
{
	//投げるアニメーション終わったら
	if (mEnemyBase->get_animation().isEnd()) {
		//ここからスコアエリア
		mEnemyBase->setBaseScore(0);
		mIsEnd = true;
	}
}

void ZihankiEventActor05::Draw() const
{
}

void ZihankiEventActor05::End()
{
	mTextBox->Hidden_Text();

	mTextBox->End();
}
