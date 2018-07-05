#pragma once

#include "../EventActor/EventActor.h"
#include "../EventManager/EventManager.h"

#include <vector>

#include "../../Graphic/TextBox.h"

#include "../../Actor/Enemy/EnemyBase.h"
//こいつが中層イベント(イベント自体)

class Event {
public:
	//コンストラクタ
	Event(IWorld & world);
	//デストラクタ
	~Event();
	//一番細かいイベントの追加(イベントの追加順がそのまま反映されるので注意)
	void Add(EventActor* e);
	//アップデート
	void Update();
	//描写
	void Draw() const;
	//次のイベントへ進む
	void NextEvent();
	//イベントが強制チェンジされたとき呼ばれる
	void ResetEvent();
	//イベントが終わったかどうか
	bool GetIsEventEnd();
	//テキストボックス表示させるか
	void SetIsDrawTextBox(bool flag);
private:
	//イベントたち
	std::vector<EventActor*> mEvents;
	//イベントがどのくらい進んだか
	int mEventNum;
	//直前のイベント番号
	int mBeforeEventNum;
	//このイベントが終わったかどうか？
	bool mIsEnd;
	//テキストボックス
	std::shared_ptr<TextBox> mTextBox;
	//テキストボックス表示させるか
	bool mIsDrawTextBox;
	//最初だけのフラグ
	bool mFirstStartFlag;
	ActorPtr mEnemy;
	ActorPtr mPlayer;
	IWorld* mWorld;
	int mAlpha;
};