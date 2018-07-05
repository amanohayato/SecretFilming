#pragma once
#include "../RandomEventBase/RandomEvent.h"
#include "../../../../World/IWorld.h"
#include "../../../../Actor/Enemy/EnemyBase.h"
#include "../../../../Actor/UIActor/TextActor.h"

class IRandomEvent
{
public:
	// 初期化
	virtual void Initialize() = 0;
	// 更新
	virtual void Update() = 0;
	// 描画
	virtual void Draw() const = 0;
	// 終了しているか？
	virtual bool IsEnd() const = 0;
	// 終了
	virtual void End() = 0;
	// 次のランダムイベント
	virtual RandomEvent Next() const = 0;

protected:
	// ワールド
	IWorld* world_;
	// エネミー
	std::weak_ptr<EnemyBase> enemyBase_;
	//テキストボックス
	std::shared_ptr<TextBox> textBox_;
	// 終了フラグ
	bool isEnd_;
};