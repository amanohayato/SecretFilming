#pragma once

#include "../EventActor.h"

class KizukiEventActor :public EventActor {
public:
	KizukiEventActor(IWorld& world, EventType eventType);
	~KizukiEventActor();

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