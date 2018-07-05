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
	//一番最初だけのスタート関数を呼ぶときの処理
	if (mFirstStartFlag)
	{
		mEvents[mEventNum]->Start();
		mFirstStartFlag = false;
	}

	//アップデート
	mEvents[mEventNum]->Update();



	//イベント自体終わらせる場合
	if (mEvents[mEventNum]->GetEventIsEnd()) {
		for (int i = mEventNum; i < mEvents.size(); i++) {
			delete mEvents[i];
			mTextBox->End();
			mIsEnd = true;
			return;
		}
	}

	//終わっていたら次のイベントへ
	if (mEvents[mEventNum]->GetIsEnd())
		NextEvent();

	if (!mWorld->hitToLine(mPlayer->getPosition(), mEnemy->getPosition())) mTextBox->SetIsDraw(true);
	else mTextBox->SetIsDraw(false);


	//テキストアップデート
	mTextBox->Update();
}

void Event::Draw() const
{
	//終わっていたら描写しない
	if (mEvents.size() <= mEventNum || mIsEnd)return;
	mEvents[mEventNum]->Draw();

	mTextBox->Draw(Vector2{ 200.0f,800.0f }, FONT_ID::FONT_TEXT, Vector2(1000, 150));
}

void Event::NextEvent()
{
	//もしも呼ばれていた場合のエラー回避
	if (mIsEnd)return;
	//現在のイベントの終了処理
	mEvents[mEventNum]->End();
	//使い終わったイベント消す
	delete mEvents[mEventNum];
	//次のイベントへ
	mEventNum++;
	//全てのイベントが終わったら
	if (mEventNum >= mEvents.size()) {
		//イベント終わった
		mIsEnd = true;
		return;
	}
	//次のイベントのスタート
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
