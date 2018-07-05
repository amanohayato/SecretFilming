#include "RandomEventProbability.h"
#include "../RandomEventArea.h"
#include <DxLib.h>

// コンストラクタ
RandomEventProbability::RandomEventProbability() {
}

// 読み込み
void RandomEventProbability::Load()
{
	csvReader_.load("res/Data/eventProbability.csv");
}

// 渡されたエリアの発生確率を返す
std::vector<float> RandomEventProbability::SetUp(const RandomEventArea & area)
{
	currentArea_ = area;
	increase_ += 0.1f;
	auto col = csvReader_.columns();

	for (int i = 0; i < col; i++) {
		auto num = csvReader_.geti(static_cast<int>(area), i);
		probability_.at(i) = (float)num;
		// もしエリアにいたら発生確率を増加させる
		if (static_cast<int>(area) != 0) {
			probability_.at(i) *= increase_;//乗算にしちゃいました、問題あれば再修正お願いします
		}
	}
	return probability_;
}

// 発生確率を判定する
RandomEvent RandomEventProbability::Judgment()
{
	for (int i = 0; i < probability_.size(); i++) {
		if (probability_[i] >= (std::rand() % 100) + 1) {
			// 増加率を0%に戻す
			increase_ = 0.0f;
			// 確率を再設定
			SetUp(currentArea_);
			// 発生するイベントを返す
			return static_cast<RandomEvent>(i + 1);
		}
	}
	return RandomEvent::Null_Eve;
}
