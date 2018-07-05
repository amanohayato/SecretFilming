#pragma once
#include "../../RandomEventBase/IRandomEvent.h"

class RisingHatState : public IRandomEvent
{
public:
	// コンストラクタ
	RisingHatState(IWorld& world);
	// 開始
	virtual void Initialize() override;
	// 更新
	virtual void Update() override;
	// 描画
	virtual void Draw() const override;
	// 終了しているか?
	virtual bool IsEnd() const override;
	// 終了
	virtual void End() override;
	// 次のランダムイベント
	virtual RandomEvent Next() const override;
private:
	std::function<void()> _seFunc;//帽子を取る
	std::function<void()> _pickupFunc;//帽子を取る
	std::function<void()> _wearFunc;//帽子をかぶる

};