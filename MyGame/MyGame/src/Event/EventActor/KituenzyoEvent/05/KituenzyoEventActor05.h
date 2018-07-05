#pragma once

#include "../../EventActor.h"

class KituenzyoEventActor05:public EventActor {
public:
	KituenzyoEventActor05(IWorld& world);
	~KituenzyoEventActor05();

	//イベントの最初に一回だけ呼ばれる関数
	virtual void Start() override;
	//イベント中のアップデート
	virtual void Update() override;
	//イベントの描写
	virtual void Draw()const override;
	//イベントが終わった時に一回だけ呼ばれる関数
	virtual void End() override;
private:
	float mTime;

	ActorPtr mBeam;

};