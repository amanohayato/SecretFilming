#pragma once

#include "../../EventActor.h"

class ManhoruEventActor06 :public EventActor {
public:
	ManhoruEventActor06(IWorld& world);
	~ManhoruEventActor06();

	//イベントの最初に一回だけ呼ばれる関数
	virtual void Start() override;
	//イベント中のアップデート
	virtual void Update() override;
	//イベントの描写
	virtual void Draw()const override;
	//イベントが終わった時に一回だけ呼ばれる関数
	virtual void End() override;
private:
	float mStartY;
	float mEndY;
	float mLerpTime;

	float mTime;
};