#pragma once

#include "../../World/IWorld.h"

#include "../../Actor/Enemy/EnemyBase.h"
#include "../../Graphic/TextBox.h"
//最下層イベント(イベント中の細かい行動)	
class EventActor {
public:
	//コンストラクタ
	EventActor(IWorld& world) :mWorld(&world), mIsEnd(false), mEventIsEnd(false) {};
	virtual ~EventActor() {};
	//イベントの最初に一回だけ呼ばれる関数
	virtual void Start() = 0;
	//イベント中のアップデート
	virtual void Update() = 0;
	//イベントの描写
	virtual void Draw()const = 0;
	//イベントが終わった時に一回だけ呼ばれる関数
	virtual void End() = 0;

	//終わったかどうか？
	bool GetIsEnd() { return mIsEnd; };
	//イベント自体終わらせるか
	bool GetEventIsEnd() { return mEventIsEnd; };
	//テキストボックスをセットする
	void SetTextBox(std::shared_ptr<TextBox> textBox) { mTextBox = textBox; };
protected:
	//ワールド
	IWorld* mWorld;
	//このイベントが終わった場合
	bool mIsEnd;

	//逃走中にイベントに入った用
	bool mEventIsEnd;

	//エネミーベース
	EnemyBase* mEnemyBase;

	//テキストボックス
	std::shared_ptr<TextBox> mTextBox;
};