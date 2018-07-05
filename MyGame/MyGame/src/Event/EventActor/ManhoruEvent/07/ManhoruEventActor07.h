#pragma once

#include "../../EventActor.h"

class EventUfo;

class ManhoruEventActor07 :public EventActor {
public:
	ManhoruEventActor07(IWorld& world);
	~ManhoruEventActor07();

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
	float mTime;
};