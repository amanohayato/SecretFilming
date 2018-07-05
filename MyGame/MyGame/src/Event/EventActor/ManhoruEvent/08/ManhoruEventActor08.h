#pragma once

#include "../../EventActor.h"

class EventUfo;

class ManhoruEventActor08 :public EventActor {
public:
	ManhoruEventActor08(IWorld& world);
	~ManhoruEventActor08();

	//イベントの最初に一回だけ呼ばれる関数
	virtual void Start() override;
	//イベント中のアップデート
	virtual void Update() override;
	//イベントの描写
	virtual void Draw()const override;
	//イベントが終わった時に一回だけ呼ばれる関数
	virtual void End() override;
private:

	EventUfo* mEventUfo;
	ActorPtr mCar;

	float mStartY;
	float mEndY;
	float mLerpTime;
};