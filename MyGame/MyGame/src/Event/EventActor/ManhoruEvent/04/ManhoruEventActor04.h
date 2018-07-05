#pragma once

#include "../../EventActor.h"

class ManhoruEventActor04 :public EventActor {
public:
	ManhoruEventActor04(IWorld& world);
	~ManhoruEventActor04();

	//イベントの最初に一回だけ呼ばれる関数
	virtual void Start() override;
	//イベント中のアップデート
	virtual void Update() override;
	//イベントの描写
	virtual void Draw()const override;
	//イベントが終わった時に一回だけ呼ばれる関数
	virtual void End() override;
private:
	ActorPtr mCar;
	ActorPtr mManhoru;

	float mStartY;
	float mEndY;

	//車を持ち上げるときの補間タイム
	float mLerpTime;
};