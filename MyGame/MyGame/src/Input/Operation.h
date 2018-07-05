#pragma once
#include "../ID/EnumIDs.h"
#include "Keyboard.h"
#include <vector>

// プレイヤー操作の構造体
struct Operation
{
public:

	// コンストラクタ
	Operation(Operation_Type type, std::vector<int> correspondingButtons, std::vector<Stick_Input_Type> correspondingSticks, std::vector<Trigger_Input_Type> correspondingTriggers)
	{
		IsActive = true;
		Type = type;
		CorrespondingButtons = correspondingButtons;
		CorrespondingSticks = correspondingSticks;
		CorrespondingTriggers = correspondingTriggers;
	};

	// この操作を受け付けるかのフラグ
	bool IsActive;

	// プレイヤー操作の種類
	Operation_Type Type;

	// 対応するボタン入力の種類
	std::vector<int> CorrespondingButtons;

	// 対応するスティック入力の種類
	std::vector<Stick_Input_Type> CorrespondingSticks;

	// 対応するトリガー入力の種類
	std::vector<Trigger_Input_Type> CorrespondingTriggers;

	//****************************************
	// デバッグ用キーボード入力処理

	// デバッグ用キーボード入力込みのコンストラクタ
	Operation(Operation_Type type, std::vector<int> correspondingButtons, std::vector<Stick_Input_Type> correspondingSticks, std::vector<Trigger_Input_Type> correspondingTriggers, std::vector<UINT> correspondingKeys)
	{
		IsActive = true;
		Type = type;
		CorrespondingButtons = correspondingButtons;
		CorrespondingSticks = correspondingSticks;
		CorrespondingTriggers = correspondingTriggers;
		CorrespondingKeys = correspondingKeys;
	};

	// 対応するキーボード入力の種類
	std::vector<UINT> CorrespondingKeys;
};