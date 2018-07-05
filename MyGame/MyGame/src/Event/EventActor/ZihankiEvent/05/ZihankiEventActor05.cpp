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

	//�����Ŏ��̋@���΂�
	mWorld->addActor(ActorGroup::ZIHANKI_ACTOR, std::make_shared<Zihanki>(mWorld, mEnemyBase->GetEventPoints().front().building_));

	Sound::GetInstance().Play3DSE(SE_ID::VEBDINGMACHINE_THROW_SE, (VECTOR*)&mEnemyBase->getPosition());

	//��������X�R�A�G���A
	mEnemyBase->setBaseScore(20);
}

void ZihankiEventActor05::Update()
{
	//������A�j���[�V�����I�������
	if (mEnemyBase->get_animation().isEnd()) {
		//��������X�R�A�G���A
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
