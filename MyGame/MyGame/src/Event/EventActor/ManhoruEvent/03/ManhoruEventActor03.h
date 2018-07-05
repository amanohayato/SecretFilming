#pragma once

#include "../../EventActor.h"

class ManhoruEventActor03 :public EventActor {
public:
	ManhoruEventActor03(IWorld& world);
	~ManhoruEventActor03();

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

	float mManhoruStartY;
	float mManhoruEndY;


	//車を持ち上げるときの補間タイム
	float mLerpTime;
};