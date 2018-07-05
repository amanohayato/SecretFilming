#pragma once
#include "../../../Resource/CsvReader.h"
#include "../../../World/IWorld.h"
#include "../RandomEvent/RandomEventBase/IRandomEventPtr.h"
#include "../RandomEventProbability/RandomEventProbability.h"
#include <unordered_map>

enum class RandomEvent;
enum class RandomEventArea;

class RandomEventManager
{
public:
	// コンストラクタ
	RandomEventManager(IWorld& world);
	// 読み込み
	void Load();
	// 初期化  
	void Initialize();
	// 更新
	void Update();
	// 描画  
	void Draw() const;
	// デバッグ処理
	void DebugDraw();
	// 終了    
	void End();
	// ランダムイベントの追加 
	void Add(RandomEvent name, const IRandomEventPtr& event);
	// ランダムイベントの変更   
	void Change(RandomEvent name);
	void SetPosition(const Vector3& position);
	// コピー禁止    
	RandomEventManager(const RandomEventManager& other) = delete;
	RandomEventManager& operator = (const RandomEventManager& other) = delete;

private:
	// 座標をマス目に変換する
	Vector2 ToSquares(const Vector3& pos);
	// どのエリアにいるかを判定
	RandomEventArea CheckArea(const Vector2& pos);
	// エリアの確率を設定
	void SetUp(const RandomEventArea& area);
	// 発生確率を判定する
	void Judgment();

private:
	// ランダムイベント
	std::unordered_map<RandomEvent, IRandomEventPtr> randomEvents_;
	// 現在の状態
	std::weak_ptr<IRandomEvent> currentRandomEvent_;
	// CSV読み込み
	CsvReader csvReader_;
	// エリアの確率を設定してくれるやつ
	RandomEventProbability eventProbability_;
	// エリアの確率
	std::vector<float> probability_;
	// 現在のエリア
	RandomEventArea currentArea_;
	// 1フレーム前のエリア
	RandomEventArea prevArea_;
	// ワールド
	IWorld* world_;
	// 現在のマス目
	Vector2 currentSquares_;
	// 1フレーム前のマス目
	Vector2 prevSquares_;
};