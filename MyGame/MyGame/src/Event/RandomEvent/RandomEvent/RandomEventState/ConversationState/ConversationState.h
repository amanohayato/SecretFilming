#pragma once
#include "../../RandomEventBase/IRandomEvent.h"

class ConversationState : public IRandomEvent
{
public:
	// コンストラクタ
	ConversationState(IWorld& world);
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
	float count_;
};