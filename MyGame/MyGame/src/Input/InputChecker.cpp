#include "InputChecker.h"
#include "GamePad.h"
#include "../ID/EnumIDs.h"
#include <vector>
#include <string>

InputChecker::InputChecker()
{
	// ************************************************************
	// �L�[�{�[�h�Ɛ���������Ȃ�����g��
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
	// �v���C���[����̎�ނ̔z��̒��ɓ��� Operation_Type �̗v�f������Βǉ����Ȃ�
	if (GetOperation(operation) != nullptr) return;

	// �v���C���[����̍\���̂��쐬
	std::shared_ptr<Operation> tempPtr = std::make_shared<Operation>(operation, buttonType, stickType, correspondingTriggers, keyType);

	// �v���C���[����̎�ނ̔z��ɒǉ�
	operations_.push_back(tempPtr);
}

void InputChecker::ChangeActive(Operation_Type operation, bool active)
{
	// �����Ɉ�v���� Operation_Type �����\���̂�������Ώ������s��Ȃ�
	if (GetOperation(operation) == nullptr) return;

	// �����Ɉ�v����\���̂̃A�N�e�B�u�t���O��ύX����
	GetOperation(operation)->IsActive = active;
}

bool InputChecker::KeyTriggerDown(Operation_Type operation) const
{
	// �A�N�e�B�u�t���O�� Off �������� ture ��Ԃ��Ȃ�
	if (!GetOperation(operation)->IsActive) return false;

	// �Q�[���p�b�h�̃{�^�����͂̔���p�t���O
	bool buttonJudge = false;

	// �Q�[���p�b�h�̃{�^�����͔��菈��
	for each (int key in GetOperation(operation)->CorrespondingButtons)
	{
		if (XInputGamePad::GetInstance().ButtonTriggerDown(key))
		{
			buttonJudge = true;
		}
	}

	// �Q�[���p�b�h�̃X�e�B�b�N���͂̔���p�t���O
	bool stickJudge = false;

	for each (Stick_Input_Type key in GetOperation(operation)->CorrespondingSticks)
	{
		if (StickTriggerDown(key)) stickJudge = true;
	}

	// �Q�[���p�b�h�̃g���K�[���͂̔���p�t���O
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
	// �f�o�b�O�p�L�[�{�[�h���͏���

	// �L�[�{�[�h���͂̔���p�t���O
	bool keyJudge = false;

	// �L�[�{�[�h�̓��͔��菈��
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

	// 4�̃t���O���l�����čŏI�I�ȃt���O��Ԃ�
	return (buttonJudge || stickJudge || triggerJudge || keyJudge);
}

bool InputChecker::KeyTriggerUp(Operation_Type operation) const
{
	// �A�N�e�B�u�t���O�� Off �������� ture ��Ԃ��Ȃ�
	if (!GetOperation(operation)->IsActive) return false;

	// �Q�[���p�b�h�̃{�^�����͂̔���p�t���O
	bool buttonJudge = false;

	// �Q�[���p�b�h�̃{�^�����͔��菈��
	for each (int key in GetOperation(operation)->CorrespondingButtons)
	{
		if (XInputGamePad::GetInstance().ButtonTriggerUp(key)) buttonJudge = true;
	}

	// �Q�[���p�b�h�̃X�e�B�b�N���͂̔���p�t���O
	bool stickJudge = false;

	for each (Stick_Input_Type key in GetOperation(operation)->CorrespondingSticks)
	{
		if (StickTriggerUp(key)) stickJudge = true;
	}

	// �Q�[���p�b�h�̃g���K�[���͂̔���p�t���O
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
	// �f�o�b�O�p�L�[�{�[�h���͏���

	// �L�[�{�[�h���͂̔���p�t���O
	bool keyJudge = false;

	// �L�[�{�[�h�̓��͔��菈��
	for each (UINT key in GetOperation(operation)->CorrespondingKeys)
	{
		if (Keyboard::GetInstance().KeyTriggerUp(key)) keyJudge = true;
	}

	//****************************************

	// 4�̃t���O���l�����čŏI�I�ȃt���O��Ԃ�
	return (buttonJudge || stickJudge || triggerJudge || keyJudge);
}

bool InputChecker::KeyStateDown(Operation_Type operation) const
{
	// �A�N�e�B�u�t���O�� Off �������� ture ��Ԃ��Ȃ�
	if (!GetOperation(operation)->IsActive) return false;

	std::shared_ptr<Operation> o = GetOperation(operation);

	// �Q�[���p�b�h�̃{�^�����͂̔���p�t���O
	bool buttonJudge = false;

	// �Q�[���p�b�h�̃{�^�����͔��菈��
	for each (int key in GetOperation(operation)->CorrespondingButtons)
	{
		if (XInputGamePad::GetInstance().ButtonStateDown(key)) buttonJudge = true;
	}

	// �Q�[���p�b�h�̃X�e�B�b�N���͂̔���p�t���O
	bool stickJudge = false;

	for each (Stick_Input_Type key in GetOperation(operation)->CorrespondingSticks)
	{
		if (StickStateDown(key)) stickJudge = true;
	}

	// �Q�[���p�b�h�̃g���K�[���͂̔���p�t���O
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
	// �f�o�b�O�p�L�[�{�[�h���͏���

	// �L�[�{�[�h���͂̔���p�t���O
	bool keyJudge = false;

	// �L�[�{�[�h�̓��͔��菈��
	for each (UINT key in GetOperation(operation)->CorrespondingKeys)
	{
		if (Keyboard::GetInstance().KeyStateDown(key)) keyJudge = true;
	}

	//****************************************

	// 4�̃t���O���l�����čŏI�I�ȃt���O��Ԃ�
	return (buttonJudge || stickJudge || triggerJudge || keyJudge);
}

bool InputChecker::KeyStateUp(Operation_Type operation) const
{
	// �A�N�e�B�u�t���O�� Off �������� ture ��Ԃ��Ȃ�
	if (!GetOperation(operation)->IsActive) return false;

	return !KeyStateDown(operation);
}

Vector2 InputChecker::Stick() const
{
	// �A�N�e�B�u�t���O�� Off �������� ture ��Ԃ��Ȃ�
	if (!GetOperation(Operation_Type::PLAYER_MOVE_STICK)->IsActive)
		return Vector2::Zero;

	Vector2 result = Vector2::Zero;

	//****************************************
	// �f�o�b�O�p�L�[�{�[�h���͏���
	
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
	// �A�N�e�B�u�t���O�� Off �������� ture ��Ԃ��Ȃ�
	if (!GetOperation(Operation_Type::CHANGE_VIEW_POINT_STICK)->IsActive)
		return Vector2::Zero;

	Vector2 result = Vector2::Zero;

	//****************************************
	// �f�o�b�O�p�L�[�{�[�h���͏���
	
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
	// �v���C���[����̎�ނ̔z��̒��ɓ��� Operation_Type �̍\���̂�����΂����Ԃ�
	for each (std::shared_ptr<Operation> ptr in operations_) if (ptr->Type == operation) return ptr;

	// ������΂ʂ�ۂ�Ԃ�
	return nullptr;
}

bool InputChecker::StickStateDown(Stick_Input_Type key) const
{
	// �ȑO�̃X�e�B�b�N���͂ɂ�锻��
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
	// �ȑO�̃X�e�B�b�N���͂ɂ�锻��
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
	// �O�t���[�����͂���Ă��Ȃ��A���t���[�����͂���Ă���� true
	return (!PreStickStateDown(key) && StickStateDown(key));
}

bool InputChecker::StickTriggerUp(Stick_Input_Type key) const
{
	// �O�t���[�����͂���Ă��āA���t���[�����͂���Ă��Ȃ���� true
	return (PreStickStateDown(key) && !StickStateDown(key));
}