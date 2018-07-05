#pragma once

#include "../../EventActor.h"

class EventUfo;

class ManhoruEventActor09 :public EventActor {
public:
	ManhoruEventActor09(IWorld& world);
	~ManhoruEventActor09();

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

};