#pragma once
#include "../../../Resource/CsvReader.h"
#include "../RandomEvent/RandomEventBase/RandomEvent.h"

enum class RandomEventArea;

class RandomEventProbability
{
public:
	// コンストラクタ
	RandomEventProbability();
	// 読み込み
	void Load();
	// 渡されたエリアの発生確率を返す
	std::vector<float> SetUp(const RandomEventArea& area);
	// 発生確率を判定する
	RandomEvent Judgment();

private:
	// CSV読み込み
	CsvReader csvReader_;
	// エリアごとの確率
	std::vector<float> probability_{ std::vector<float>(2) };
	// 現在のエリア
	RandomEventArea currentArea_;
	// 増加率
	float increase_{ 0.0f };
};
