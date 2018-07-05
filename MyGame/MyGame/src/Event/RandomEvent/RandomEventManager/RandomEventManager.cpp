#include "RandomEventManager.h"
#include "../RandomEventProbability/RandomEventProbability.h"
#include "../RandomEvent/NullRandomEvent/NullRandomEvent.h"
#include "../RandomEvent/SignalRandomEvent/SignalRandomEvent.h"
#include "../RandomEvent/FallDownRandomEvent/FallDownRandomEvent.h"
#include "../RandomEvent/RandomEventBase/RandomEvent.h"
#include "../RandomEventArea.h"
#include "../../../Actor/Enemy/EnemyBase.h"
#include "../../../World/World.h"
#include <assert.h>
#include <DxLib.h>

// コンストラクタ
RandomEventManager::RandomEventManager(IWorld& world)
	: world_(&world), currentRandomEvent_() {
	Load();
	Add(RandomEvent::Null_Eve, std::make_shared<NullRandomEvent>(world));
	Add(RandomEvent::FallDown_Eve, std::make_shared<FallDownRandomEvent>(world));
	Add(RandomEvent::Signal_Eve, std::make_shared<SignalRandomEvent>(world));
	Change(RandomEvent::Null_Eve);
	currentRandomEvent_.lock()->Initialize();
}

// 読み込み
void RandomEventManager::Load()
{
	csvReader_.load("res/Data/randomEvent.csv");
	eventProbability_.Load();
}

// 初期化
void RandomEventManager::Initialize()
{
	End();
	randomEvents_.clear();
	Add(RandomEvent::Null_Eve, std::make_shared<NullRandomEvent>(*world_));
	Add(RandomEvent::FallDown_Eve, std::make_shared<FallDownRandomEvent>(*world_));
	Add(RandomEvent::Signal_Eve, std::make_shared<SignalRandomEvent>(*world_));
	Change(RandomEvent::Null_Eve);
	currentRandomEvent_.lock()->Initialize();
}

// 更新
void RandomEventManager::Update()
{
	prevSquares_ = currentSquares_;
	currentSquares_ = ToSquares(world_->findActor("Enemy")->getPosition());

	// マス目が変わったら
	if ((int)currentSquares_.x != (int)prevSquares_.x || (int)currentSquares_.y != (int)prevSquares_.y) {
		// 1フレーム前のエリアを設定
		prevArea_ = currentArea_;
		// 現在のエリアを設定
		currentArea_ = CheckArea(currentSquares_);
		// エネミーが移動中かつ同じエリアじゃない場合に処理をする
		if (std::static_pointer_cast<EnemyBase>(world_->findActor("Enemy"))->get_state() == EnemyBase::EnemyState::Move
			&& currentArea_ != prevArea_) {
			// エリアによる確率を設定
			SetUp(CheckArea(currentSquares_));
			// 発生確率を判定
			Change(eventProbability_.Judgment());
		}
	}
	currentRandomEvent_.lock()->Update();
	if (currentRandomEvent_.lock()->IsEnd()) {
		Change(currentRandomEvent_.lock()->Next());
	}
}

// 描画
void RandomEventManager::Draw() const
{
	currentRandomEvent_.lock()->Draw();
}

// 座標をマス目に変換する
Vector2 RandomEventManager::ToSquares(const Vector3 & pos)
{
	auto row = ((pos.x) / 48.5f) + 1;
	auto col = ((27 - ((pos.z) / 48.5f)));

	// インデックス外にならないための処理
	if (row >= 28) row = 28;
	else if (row <= 1) row = 1;
	if (col >= 24) col = 24;
	else if (col <= 1) col = 1;

	return Vector2(row, col);
}

// どのエリアにいるかを判定
RandomEventArea RandomEventManager::CheckArea(const Vector2& pos)
{
	auto num = csvReader_.geti((int)pos.y - 1, (int)pos.x - 2);
	return static_cast<RandomEventArea>(num);
}

// エリアの確率を設定
void RandomEventManager::SetUp(const RandomEventArea& area)
{
	probability_ = eventProbability_.SetUp(area);
}

// 発生確率を判定する
void RandomEventManager::Judgment()
{
	auto num = (std::rand() % 100) + 1;
}

// デバッグ処理
void RandomEventManager::DebugDraw()
{
#ifdef _DEBUG
	SetFontSize(32);
	/*DrawFormatString(10, 50, GetColor(255, 0, 0), "縦：%i", (int)currentSquares_.y);
	DrawFormatString(10, 100, GetColor(255, 0, 0), "横：%i", (int)currentSquares_.x);*/
	switch (currentArea_) {
	case(RandomEventArea::None):DrawFormatString(10, 150, GetColor(255, 0, 0), "現在のエリア：どこのエリアにもいません"); break;
	case(RandomEventArea::AreaBlue):DrawFormatString(10, 150, GetColor(255, 0, 0), "現在のエリア：青エリア"); break;
	case(RandomEventArea::AreaGreen):DrawFormatString(10, 150, GetColor(255, 0, 0), "現在のエリア：緑エリア"); break;
	case(RandomEventArea::AreaRed):DrawFormatString(10, 150, GetColor(255, 0, 0), "現在のエリア：赤エリア"); break;
	case(RandomEventArea::AreaOrange):DrawFormatString(10, 150, GetColor(255, 0, 0), "現在のエリア：橙エリア"); break;
	default:assert(!"割り振られていません"); break;
	}
	if (probability_.empty())return;
	DrawFormatString(10, 50, GetColor(255, 0, 0), "こける発生確率：%f", probability_[0]);
	DrawFormatString(10, 100, GetColor(255, 0, 0), "通信発生確率：%f", probability_[1]);
#endif // _DEBUG
}

// 終了
void RandomEventManager::End()
{
	if (currentRandomEvent_.expired())return;
	currentRandomEvent_.lock()->End();
}

// ランダムイベントの追加 
void RandomEventManager::Add(RandomEvent name, const IRandomEventPtr & event)
{
	randomEvents_[name] = event;
}

// ランダムイベントの変更   
void RandomEventManager::Change(RandomEvent name)
{
	End();
	currentRandomEvent_ = randomEvents_[name];
	currentRandomEvent_.lock()->Initialize();
}

void RandomEventManager::SetPosition(const Vector3 & position)
{
	currentSquares_ = ToSquares(position);
	prevSquares_ = currentSquares_;
	currentArea_ = CheckArea(currentSquares_);

}
