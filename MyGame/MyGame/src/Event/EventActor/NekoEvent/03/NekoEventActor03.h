#pragma once

#include "../../EventActor.h"
#include"../../../../Actor/EventActor/AbductUfo/AbductUfo.h"

class NekoEventActor03 :public EventActor {
public:
	NekoEventActor03(IWorld& world);
	~NekoEventActor03();

	//イベントの最初に一回だけ呼ばれる関数
	virtual void Start() override;
	//イベント中のアップデート
	virtual void Update() override;
	//イベントの描写
	virtual void Draw()const override;
	//イベントが終わった時に一回だけ呼ばれる関数
	virtual void End() override;
private:
	std::weak_ptr<AbductUfo> ufo_;
};