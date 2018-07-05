#include "NekoEventActor02.h"
#include"../../../../Sound/Sound.h"
#include"../../../../Actor/UIActor/TextActor.h"

NekoEventActor02::NekoEventActor02(IWorld & world):
	EventActor(world)
{
}

NekoEventActor02::~NekoEventActor02()
{
}

void NekoEventActor02::Start()
{
	mEnemyBase = static_cast<EnemyBase*>(mWorld->findActor("Enemy").get());
	mEnemyBase->get_animation().changeAnimation(AnimLoader::getInstance().getAnimKey(MODEL_ID::MODEL_ENEMY, (int)EnemyBase::EnemyAnimation::UDEKUMI), false);

	//mStartMat = mEnemyBase->getPose();
	//mEndMat = mEnemyBase->getPose()*Matrix::CreateTranslation(mEnemyBase->getPose().Forward()*40.0f);

	//mLerpTime = 0.0f;
	_voiceFunc = [&] {
		Sound::GetInstance().Play3DSE(SE_ID::NEKO_GRAY_VOICE_SE, (VECTOR*)&mEnemyBase->getPosition());
	};

	mTextBox->add("CatEvent/cat1.txt");
	mTextBox->Start_Text();

}

void NekoEventActor02::Update()
{
	if (mEnemyBase->get_animation().getGetCurrentAnimTime() >= 30.0f) {
		_voiceFunc();
		_voiceFunc = [] {};
	}

	mIsEnd = mEnemyBase->get_animation().isEnd();

}

void NekoEventActor02::Draw() const
{
}

void NekoEventActor02::End()
{
	mTextBox->Hidden_Text();

	mTextBox->End();

}
