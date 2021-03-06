#pragma once

#include "../../EventActor.h"

class PoliceEventActor01 :public EventActor {
public:
	PoliceEventActor01(IWorld& world);

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
};