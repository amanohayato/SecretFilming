#include "InputChecker.h"
#include "GamePad.h"
#include "../ID/EnumIDs.h"
#include <vector>
#include <string>

InputChecker::InputChecker()
{
	// ************************************************************
	// キーボードと絶交したくなったら使え
	/*AddOperation
	(
		Operation_Type::ANY_BUTTON,
		{ XINPUT_BUTTON_A, XINPUT_BUTTON_B, XINPUT_BUTTON_X, XINPUT_BUTTON_Y, XINPUT_BUTTON_LEFT_SHOULDER, XINPUT_BUTTON_RIGHT_SHOULDER, XINPUT_BUTTON_START, XINPUT_BUTTON_BACK },
		{},
		{ Trigger_Input_Type::LEFT_TRIGGER, Trigger_Input_Type::RIGHT_TRIGGER },
		{}
	);

	AddOperation(Operation_Type::STICK_UP, {}, { Stick_Input_Type::LEFT_STICK_UP, Stick_Input_Type::RIGHT_STICK_UP }, {}, {});
	AddOperation(Operation_Type::STICK_DOWN, {}, { Stick_Input_Type::LEFT_STICK_DOWN, Stick_Input_Type::RIGHT_STICK_DOWN }, {}, {});
	AddOperation(Operation_Type::STICK_LEFT, {}, { Stick_Input_Type::LEFT_STICK_LEFT, Stick_Input_Type::RIGHT_STICK_LEFT }, {}, {});
	AddOperation(Operation_Type::STICK_RIGHT, {}, { Stick_Input_Type::LEFT_STICK_RIGHT, Stick_Input_Type::RIGHT_STICK_RIGHT }, {}, {});

	AddOperation(Operation_Type::DECISION_BUTTON, { XINPUT_BUTTON_A }, {}, {}, {});
	AddOperation(Operation_Type::CANCEL_BUTTON, { XINPUT_BUTTON_B }, {}, {}, {});

	AddOperation(Operation_Type::PLAYER_MOVE_STICK, {}, {}, {}, {});
	AddOperation(Operation_Type::CHANGE_VIEW_POINT_STICK, {}, {}, {}, {});

	AddOperation(Operation_Type::SHOW_MAP_BUTTON, { XINPUT_BUTTON_Y }, {}, {}, {});
	AddOperation(Operation_Type::HOLD_CAMERA_BUTTON, {}, {}, { Trigger_Input_Type::LEFT_TRIGGER }, {});
	AddOperation(Operation_Type::TAKE_SHUTTER_BUTTON, {}, {}, { Trigger_Input_Type::RIGHT_TRIGGER }, {});
	AddOperation(Operation_Type::HIDE_BUTTON, {}, {}, { Trigger_Input_Type::RIGHT_TRIGGER }, {});
	AddOperation(Operation_Type::DASH_BUTTON, { XINPUT_BUTTON_RIGHT_SHOULDER }, {}, {}, {});
	AddOperation(Operation_Type::RETURN_VIEW_POINT_BUTTON, { XINPUT_BUTTON_LEFT_SHOULDER }, {}, {}, {});

	AddOperation(Operation_Type::PAUSE_BUTTON, { XINPUT_BUTTON_START }, {}, {}, {});
	AddOperation(Operation_Type::DEBUG_CLEAR_BUTTON, { XINPUT_BUTTON_BACK }, {}, {}, {});*/
	// ************************************************************

	AddOperation
	(
		Operation_Type::ANY_BUTTON,
		{ XINPUT_BUTTON_A, XINPUT_BUTTON_B, XINPUT_BUTTON_X, XINPUT_BUTTON_Y, XINPUT_BUTTON_LEFT_SHOULDER, XINPUT_BUTTON_RIGHT_SHOULDER, XINPUT_BUTTON_START, XINPUT_BUTTON_BACK },
		{},
		{ Trigger_Input_Type::LEFT_TRIGGER, Trigger_Input_Type::RIGHT_TRIGGER },
		{ KEYCODE::N, KEYCODE::M , KEYCODE::Z, KEYCODE::X, KEYCODE::E, KEYCODE::Q, KEYCODE::R, KEYCODE::TAB, KEYCODE::H, KEYCODE::B, }
	);

	AddOperation(Operation_Type::STICK_UP,		{}, { Stick_Input_Type::LEFT_STICK_UP, Stick_Input_Type::RIGHT_STICK_UP },		{}, { KEYCODE::W, KEYCODE::I });
	AddOperation(Operation_Type::STICK_DOWN,	{}, { Stick_Input_Type::LEFT_STICK_DOWN, Stick_Input_Type::RIGHT_STICK_DOWN },	{}, { KEYCODE::S, KEYCODE::K });
	AddOperation(Operation_Type::STICK_LEFT,	{}, { Stick_Input_Type::LEFT_STICK_LEFT, Stick_Input_Type::RIGHT_STICK_LEFT },	{}, { KEYCODE::A, KEYCODE::J });
	AddOperation(Operation_Type::STICK_RIGHT,	{}, { Stick_Input_Type::LEFT_STICK_RIGHT, Stick_Input_Type::RIGHT_STICK_RIGHT },{}, { KEYCODE::D, KEYCODE::L });

	AddOperation(Operation_Type::DECISION_BUTTON,	{ XINPUT_BUTTON_A }, {}, {}, { KEYCODE::Z });
	AddOperation(Operation_Type::CANCEL_BUTTON,		{ XINPUT_BUTTON_B }, {}, {}, { KEYCODE::M });

	AddOperation(Operation_Type::PLAYER_MOVE_STICK,			{}, {}, {}, {});
	AddOperation(Operation_Type::CHANGE_VIEW_POINT_STICK,	{}, {}, {}, {});

	AddOperation(Operation_Type::SHOW_MAP_BUTTON,			{ XINPUT_BUTTON_Y }, {}, {}, { KEYCODE::X });
	AddOperation(Operation_Type::HOLD_CAMERA_BUTTON,		{}, {}, { Trigger_Input_Type::LEFT_TRIGGER }, { KEYCODE::TAB });
	AddOperation(Operation_Type::TAKE_SHUTTER_BUTTON,		{}, {}, { Trigger_Input_Type::RIGHT_TRIGGER }, { KEYCODE::R });
	AddOperation(Operation_Type::HIDE_BUTTON,				{}, {}, { Trigger_Input_Type::RIGHT_TRIGGER }, { KEYCODE::R });
	AddOperation(Operation_Type::DASH_BUTTON,				{ XINPUT_BUTTON_RIGHT_SHOULDER }, {}, {},	{ KEYCODE::LSHIFT, KEYCODE::LSHIFT });
	AddOperation(Operation_Type::RETURN_VIEW_POINT_BUTTON,	{ XINPUT_BUTTON_LEFT_SHOULDER }, {}, {},	{ KEYCODE::Q });

	AddOperation(Operation_Type::PAUSE_BUTTON,				{ XINPUT_BUTTON_START }, {}, {}, { KEYCODE::NUM0 });
	AddOperation(Operation_Type::DEBUG_CLEAR_BUTTON,		{ XINPUT_BUTTON_BACK }, {}, {}, { KEYCODE::B });


	ChangeActive(Operation_Type::DEBUG_CLEAR_BUTTON, false);
}

void InputChecker::Update()
{
	Keyboard::GetInstance().Update();
	XInputGamePad::GetInstance().update();
}

void InputChecker::AddOperation(Operation_Type operation, std::vector<int> buttonType, std::vector<Stick_Input_Type> stickType, std::vector<Trigger_Input_Type> correspondingTriggers, std::vector<UINT> keyType)
{
	// プレイヤー操作の種類の配列の中に同じ Operation_Type の要素があれば追加しない
	if (GetOperation(operation) != nullptr) return;

	// プレイヤー操作の構造体を作成
	std::shared_ptr<Operation> tempPtr = std::make_shared<Operation>(operation, buttonType, stickType, correspondingTriggers, keyType);

	// プレイヤー操作の種類の配列に追加
	operations_.push_back(tempPtr);
}

void InputChecker::ChangeActive(Operation_Type operation, bool active)
{
	// 引数に一致する Operation_Type を持つ構造体が無ければ処理を行わない
	if (GetOperation(operation) == nullptr) return;

	// 引数に一致する構造体のアクティブフラグを変更する
	GetOperation(operation)->IsActive = active;
}

bool InputChecker::KeyTriggerDown(Operation_Type operation) const
{
	// アクティブフラグが Off だったら ture を返さない
	if (!GetOperation(operation)->IsActive) return false;

	// ゲームパッドのボタン入力の判定用フラグ
	bool buttonJudge = false;

	// ゲームパッドのボタン入力判定処理
	for each (int key in GetOperation(operation)->CorrespondingButtons)
	{
		if (XInputGamePad::GetInstance().ButtonTriggerDown(key))
		{
			buttonJudge = true;
		}
	}

	// ゲームパッドのスティック入力の判定用フラグ
	bool stickJudge = false;

	for each (Stick_Input_Type key in GetOperation(operation)->CorrespondingSticks)
	{
		if (StickTriggerDown(key)) stickJudge = true;
	}

	// ゲームパッドのトリガー入力の判定用フラグ
	bool triggerJudge = false;

	for each (Trigger_Input_Type key in GetOperation(operation)->CorrespondingTriggers)
	{
		switch (key)
		{
		case LEFT_TRIGGER:

			if (XInputGamePad::GetInstance().LTrigger_TriggerDown()) triggerJudge = true;
			break;

		case RIGHT_TRIGGER:

			if (XInputGamePad::GetInstance().RTrigger_TriggerDown()) triggerJudge = true;
			break;
		}
	}

	//****************************************
	// デバッグ用キーボード入力処理

	// キーボード入力の判定用フラグ
	bool keyJudge = false;

	// キーボードの入力判定処理
	for each (UINT key in GetOperation(operation)->CorrespondingKeys)
	{
		if (Keyboard::GetInstance().KeyTriggerDown(key)) 
			keyJudge = true;
	}

	if (operation == Operation_Type::STICK_UP)
	{
		return (buttonJudge || stickJudge || triggerJudge || keyJudge);
	}

	//****************************************

	// 4つのフラグを考慮して最終的なフラグを返す
	return (buttonJudge || stickJudge || triggerJudge || keyJudge);
}

bool InputChecker::KeyTriggerUp(Operation_Type operation) const
{
	// アクティブフラグが Off だったら ture を返さない
	if (!GetOperation(operation)->IsActive) return false;

	// ゲームパッドのボタン入力の判定用フラグ
	bool buttonJudge = false;

	// ゲームパッドのボタン入力判定処理
	for each (int key in GetOperation(operation)->CorrespondingButtons)
	{
		if (XInputGamePad::GetInstance().ButtonTriggerUp(key)) buttonJudge = true;
	}

	// ゲームパッドのスティック入力の判定用フラグ
	bool stickJudge = false;

	for each (Stick_Input_Type key in GetOperation(operation)->CorrespondingSticks)
	{
		if (StickTriggerUp(key)) stickJudge = true;
	}

	// ゲームパッドのトリガー入力の判定用フラグ
	bool triggerJudge = false;

	for each (Trigger_Input_Type key in GetOperation(operation)->CorrespondingTriggers)
	{
		switch (key)
		{
		case LEFT_TRIGGER:

			if (XInputGamePad::GetInstance().LTrigger_TriggerUp()) triggerJudge = true;
			break;

		case RIGHT_TRIGGER:

			if (XInputGamePad::GetInstance().RTrigger_TriggerUp()) triggerJudge = true;
			break;
		}
	}

	//****************************************
	// デバッグ用キーボード入力処理

	// キーボード入力の判定用フラグ
	bool keyJudge = false;

	// キーボードの入力判定処理
	for each (UINT key in GetOperation(operation)->CorrespondingKeys)
	{
		if (Keyboard::GetInstance().KeyTriggerUp(key)) keyJudge = true;
	}

	//****************************************

	// 4つのフラグを考慮して最終的なフラグを返す
	return (buttonJudge || stickJudge || triggerJudge || keyJudge);
}

bool InputChecker::KeyStateDown(Operation_Type operation) const
{
	// アクティブフラグが Off だったら ture を返さない
	if (!GetOperation(operation)->IsActive) return false;

	std::shared_ptr<Operation> o = GetOperation(operation);

	// ゲームパッドのボタン入力の判定用フラグ
	bool buttonJudge = false;

	// ゲームパッドのボタン入力判定処理
	for each (int key in GetOperation(operation)->CorrespondingButtons)
	{
		if (XInputGamePad::GetInstance().ButtonStateDown(key)) buttonJudge = true;
	}

	// ゲームパッドのスティック入力の判定用フラグ
	bool stickJudge = false;

	for each (Stick_Input_Type key in GetOperation(operation)->CorrespondingSticks)
	{
		if (StickStateDown(key)) stickJudge = true;
	}

	// ゲームパッドのトリガー入力の判定用フラグ
	bool triggerJudge = false;

	for each (Trigger_Input_Type key in GetOperation(operation)->CorrespondingTriggers)
	{
		switch (key)
		{
		case LEFT_TRIGGER:

			if (XInputGamePad::GetInstance().LTrigger_StateDown()) triggerJudge = true;
			break;

		case RIGHT_TRIGGER:

			if (XInputGamePad::GetInstance().RTrigger_StateDown()) triggerJudge = true;
			break;
		}
	}

	//****************************************
	// デバッグ用キーボード入力処理

	// キーボード入力の判定用フラグ
	bool keyJudge = false;

	// キーボードの入力判定処理
	for each (UINT key in GetOperation(operation)->CorrespondingKeys)
	{
		if (Keyboard::GetInstance().KeyStateDown(key)) keyJudge = true;
	}

	//****************************************

	// 4つのフラグを考慮して最終的なフラグを返す
	return (buttonJudge || stickJudge || triggerJudge || keyJudge);
}

bool InputChecker::KeyStateUp(Operation_Type operation) const
{
	// アクティブフラグが Off だったら ture を返さない
	if (!GetOperation(operation)->IsActive) return false;

	return !KeyStateDown(operation);
}

Vector2 InputChecker::Stick() const
{
	// アクティブフラグが Off だったら ture を返さない
	if (!GetOperation(Operation_Type::PLAYER_MOVE_STICK)->IsActive)
		return Vector2::Zero;

	Vector2 result = Vector2::Zero;

	//****************************************
	// デバッグ用キーボード入力処理
	
	if (Keyboard::GetInstance().KeyStateDown(KEYCODE::A)) result.x -= 1.f;
	if (Keyboard::GetInstance().KeyStateDown(KEYCODE::D)) result.x += 1.f;
	if (Keyboard::GetInstance().KeyStateDown(KEYCODE::W)) result.y += 1.f;
	if (Keyboard::GetInstance().KeyStateDown(KEYCODE::S)) result.y -= 1.f;

	//****************************************
	
	Vector2 stickVector = XInputGamePad::GetInstance().Stick();
	if (std::abs(stickVector.x) <= 0.05f)stickVector.x = 0.f;
	if (std::abs(stickVector.y) <= 0.05f)stickVector.y = 0.f;
	
	result += stickVector;
	result = Vector2::Clamp(result, Vector2(-1.f, -1.f), Vector2(1.f, 1.f));
	
	return result;
}

Vector2 InputChecker::RightStick() const
{
	// アクティブフラグが Off だったら ture を返さない
	if (!GetOperation(Operation_Type::CHANGE_VIEW_POINT_STICK)->IsActive)
		return Vector2::Zero;

	Vector2 result = Vector2::Zero;

	//****************************************
	// デバッグ用キーボード入力処理
	
	if (Keyboard::GetInstance().KeyStateDown(KEYCODE::J)) result.x -= 1.f;
	if (Keyboard::GetInstance().KeyStateDown(KEYCODE::L)) result.x += 1.f;
	if (Keyboard::GetInstance().KeyStateDown(KEYCODE::I)) result.y += 1.f;
	if (Keyboard::GetInstance().KeyStateDown(KEYCODE::K)) result.y -= 1.f;

	//****************************************
	
	Vector2 rightStickVector = XInputGamePad::GetInstance().RightStick();
	if (std::abs(rightStickVector.x) <= 0.05f)rightStickVector.x = 0.f;
	if (std::abs(rightStickVector.y) <= 0.05f)rightStickVector.y = 0.f;

	result += rightStickVector;
	result = Vector2::Clamp(result, Vector2(-1.f, -1.f), Vector2(1.f, 1.f));
	
	return result;
}

std::shared_ptr<Operation> InputChecker::GetOperation(Operation_Type operation) const
{
	// プレイヤー操作の種類の配列の中に同じ Operation_Type の構造体があればそれを返す
	for each (std::shared_ptr<Operation> ptr in operations_) if (ptr->Type == operation) return ptr;

	// 無ければぬるぽを返す
	return nullptr;
}

bool InputChecker::StickStateDown(Stick_Input_Type key) const
{
	// 以前のスティック入力による判定
	Vector2 curStick = XInputGamePad::GetInstance().Stick();
	Vector2 curRightStick = XInputGamePad::GetInstance().RightStick();
	switch (key)
	{
	case LEFT_STICK_ANY:
		return (
			curStick.y > 0.5f ||
			curStick.y < -0.5f ||
			curStick.x < -0.5f ||
			curStick.x > 0.5f
			);

	case LEFT_STICK_UP:
		return curStick.y > 0.5f;

	case LEFT_STICK_DOWN:
		return curStick.y < -0.5f;

	case LEFT_STICK_LEFT:
		return curStick.x < -0.5f;

	case LEFT_STICK_RIGHT:
		return curStick.x > 0.5f;

	case RIGHT_STICK_ANY:
		return (
			curRightStick.y > 0.5f ||
			curRightStick.y < -0.5f ||
			curRightStick.x < -0.5f ||
			curRightStick.x > 0.5f
			);

	case RIGHT_STICK_UP:
		return curRightStick.y > 0.5f;

	case RIGHT_STICK_DOWN:
		return curRightStick.y < -0.5f;

	case RIGHT_STICK_LEFT:
		return curRightStick.x < -0.5f;

	case RIGHT_STICK_RIGHT:
		return curRightStick.x > 0.5f;
	}
	return false;
}

bool InputChecker::PreStickStateDown(Stick_Input_Type key) const
{
	// 以前のスティック入力による判定
	Vector2 preStick = XInputGamePad::GetInstance().GetPreviousStick();
	Vector2 preRightStick = XInputGamePad::GetInstance().GetPreviousRightStick();
	switch (key)
	{
	case LEFT_STICK_ANY:
		return (
			preStick.y > 0.5f ||
			preStick.y < -0.5f ||
			preStick.x < -0.5f ||
			preStick.x > 0.5f
			);

	case LEFT_STICK_UP:
		return preStick.y > 0.5f;

	case LEFT_STICK_DOWN:
		return preStick.y < -0.5f;

	case LEFT_STICK_LEFT:
		return preStick.x < -0.5f;

	case LEFT_STICK_RIGHT:
		return preStick.x > 0.5f;


	case RIGHT_STICK_ANY:
		return (
			preRightStick.y > 0.5f ||
			preRightStick.y < -0.5f ||
			preRightStick.x < -0.5f ||
			preRightStick.x > 0.5f
			);

	case RIGHT_STICK_UP:
		return preRightStick.y > 0.5f;

	case RIGHT_STICK_DOWN:
		return preRightStick.y < -0.5f;

	case RIGHT_STICK_LEFT:
		return preRightStick.x < -0.5f;

	case RIGHT_STICK_RIGHT:
		return preRightStick.x > 0.5f;
	}

	return false;
}

bool InputChecker::StickTriggerDown(Stick_Input_Type key) const
{
	// 前フレーム入力されていなく、現フレーム入力されていれば true
	return (!PreStickStateDown(key) && StickStateDown(key));
}

bool InputChecker::StickTriggerUp(Stick_Input_Type key) const
{
	// 前フレーム入力されていて、現フレーム入力されていなければ true
	return (PreStickStateDown(key) && !StickStateDown(key));
}