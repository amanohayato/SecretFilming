#pragma once

#include "../../EventActor.h"

class ManhoruEventActor05 :public EventActor {
public:
	ManhoruEventActor05(IWorld& world);
	~ManhoruEventActor05();

	//イベントの最初に一回だけ呼ばれる関数
	virtual void Start() override;
	//イベント中のアップデート
	virtual void Update() override;
	//イベントの描写
	virtual void Draw()const override;
	//イベントが終わった時に一回だけ呼ばれる関数
	virtual void End() override;
private:
	ActorPtr mManhoru;

	//補間系
	Matrix mStartMat;
	Matrix mEndMat;

	float mTime;
};