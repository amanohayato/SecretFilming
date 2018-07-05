#pragma once

#include "../../EventActor.h"

class ManhoruEventActor02 :public EventActor {
public:
	ManhoruEventActor02(IWorld& world);
	~ManhoruEventActor02();

	//イベントの最初に一回だけ呼ばれる関数
	virtual void Start() override;
	//イベント中のアップデート
	virtual void Update() override;
	//イベントの描写
	virtual void Draw()const override;
	//イベントが終わった時に一回だけ呼ばれる関数
	virtual void End() override;
private:
	EventType mEventType;

	std::function<void()> isEndFunc_;

};