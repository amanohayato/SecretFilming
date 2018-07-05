#pragma once

// 発生するランダムイベントの種類
enum class RandomEvent {
	// ランダムイベントの種類
	Null_Eve,                      // 空のイベント
	FallDown_Eve,                  // こける
	Signal_Eve,	                   // 通信

	// こけるイベントの状態
	FallDown_State,                // 前に転ぶ(このとき帽子が取れる)
	RisingHat_State,               // 立ち上がり落ちている帽子を腕を伸ばして拾い、頭にかぶる

    // 通信イベントの状態
	Hologram_State,                // ポケットをガサゴソあさり、通信アイテムを持ちながらホログラムが映し出される
	Conversation_State,            // 全身を黄色く光らせながらホログラムと会話する
	StopShine_State,               // 光を止めて急いでポケットに通信アイテムをしまう

	// 共通で使える状態
	LookAround_State,              // 周りを見渡す
};