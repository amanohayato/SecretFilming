#pragma once
#include "../../EventActor.h"

class KousatenBulding;

class JunctionEventActor01 :public EventActor {
public:
	JunctionEventActor01(IWorld& world);
	~JunctionEventActor01();

	//イベントの最初に一回だけ呼ばれる関数
	virtual void Start() override;
	//イベント中のアップデート
	virtual void Update() override;
	//イベントの描写
	virtual void Draw()const override;
	//イベントが終わった時に一回だけ呼ばれる関数
	virtual void End() override;
private:
	ActorPtr mCar{nullptr};
	std::weak_ptr<KousatenBulding> junc_;
	float mTime{ 0.0f };
};