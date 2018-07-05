#include "Event.h"
#include "../../Game/Time.h"
Event::Event(IWorld& world) :
	mEventNum(0),
	mBeforeEventNum(0),
	mIsEnd(false),
	mFirstStartFlag(true),
	mWorld(&world)
{
	mTextBox = std::make_shared<TextBox>(0);
	mTextBox->Init();
	mTextBox->Display_Text();

	mEnemy = mWorld->findActor("Enemy");
	mPlayer = mWorld->findActor("Player");

	mAlpha = 0;
}

Event::~Event()
{
}

void Event::Add(EventActor* e)
{
	e->SetTextBox(mTextBox);
	mEvents.push_back(e);
}

void Event::Update()
{
	if (mEvents.size() <= mEventNum) {
		mIsEnd = true;
		return;
	}
	//��ԍŏ������̃X�^�[�g�֐����ĂԂƂ��̏���
	if (mFirstStartFlag)
	{
		mEvents[mEventNum]->Start();
		mFirstStartFlag = false;
	}

	//�A�b�v�f�[�g
	mEvents[mEventNum]->Update();



	//�C�x���g���̏I��点��ꍇ
	if (mEvents[mEventNum]->GetEventIsEnd()) {
		for (int i = mEventNum; i < mEvents.size(); i++) {
			delete mEvents[i];
			mTextBox->End();
			mIsEnd = true;
			return;
		}
	}

	//�I����Ă����玟�̃C�x���g��
	if (mEvents[mEventNum]->GetIsEnd())
		NextEvent();

	if (!mWorld->hitToLine(mPlayer->getPosition(), mEnemy->getPosition())) mTextBox->SetIsDraw(true);
	else mTextBox->SetIsDraw(false);


	//�e�L�X�g�A�b�v�f�[�g
	mTextBox->Update();
}

void Event::Draw() const
{
	//�I����Ă�����`�ʂ��Ȃ�
	if (mEvents.size() <= mEventNum || mIsEnd)return;
	mEvents[mEventNum]->Draw();

	mTextBox->Draw(Vector2{ 200.0f,800.0f }, FONT_ID::FONT_TEXT, Vector2(1000, 150));
}

void Event::NextEvent()
{
	//�������Ă΂�Ă����ꍇ�̃G���[���
	if (mIsEnd)return;
	//���݂̃C�x���g�̏I������
	mEvents[mEventNum]->End();
	//�g���I������C�x���g����
	delete mEvents[mEventNum];
	//���̃C�x���g��
	mEventNum++;
	//�S�ẴC�x���g���I�������
	if (mEventNum >= mEvents.size()) {
		//�C�x���g�I�����
		mIsEnd = true;
		return;
	}
	//���̃C�x���g�̃X�^�[�g
	mEvents[mEventNum]->Start();
}

void Event::ResetEvent()
{
}

bool Event::GetIsEventEnd()
{
	return mIsEnd;
}

void Event::SetIsDrawTextBox(bool flag)
{
	mIsDrawTextBox = flag;
}
