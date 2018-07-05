#pragma once
#include "Operation.h"
#include "../ID/EnumIDs.h"
#include <vector>

#include"Keyboard.h"
#include"XInputGamePad.h"
#include"../Math/Vector2.h"
#include<map>
#include<functional>
#include<memory>

class InputChecker
{

private:
	// コンストラクタ
	InputChecker();

public:

	// シングルトン！
	static InputChecker& GetInstance() 
	{
		static InputChecker ic;
		return ic;
	}

	// 更新
	void Update();

	// プレイヤー操作の追加
	void AddOperation(Operation_Type operation, std::vector<int> buttonType, std::vector<Stick_Input_Type> stickType, std::vector<Trigger_Input_Type> correspondingTriggers, std::vector<UINT> keyType);

	// プレイヤー操作のアクティブフラグの変更
	void ChangeActive(Operation_Type operation, bool active);

	// パッドが押されたかを返す
	bool KeyTriggerDown(Operation_Type operation)const;

	// パッドが離したかを返す
	bool KeyTriggerUp(Operation_Type operation)const;

	// パッドを押しているかを返す
	bool KeyStateDown(Operation_Type operation)const;

	// パッドが離されているかを返す
	bool KeyStateUp(Operation_Type operation)const;

	// 左スティックの傾きを返す
	Vector2 Stick()const;

	// 右スティックの傾きを返す
	Vector2 RightStick()const;

private:

	std::shared_ptr<Operation> GetOperation(Operation_Type operation) const;

	bool StickStateDown(Stick_Input_Type key) const;

	bool PreStickStateDown(Stick_Input_Type key) const;

	bool StickTriggerDown(Stick_Input_Type key) const;

	bool StickTriggerUp(Stick_Input_Type key) const;
	

private:

	// プレイヤー操作の種類の配列
	std::vector<std::shared_ptr<Operation>> operations_;
};