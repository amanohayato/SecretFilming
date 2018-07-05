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
	// �R���X�g���N�^
	InputChecker();

public:

	// �V���O���g���I
	static InputChecker& GetInstance() 
	{
		static InputChecker ic;
		return ic;
	}

	// �X�V
	void Update();

	// �v���C���[����̒ǉ�
	void AddOperation(Operation_Type operation, std::vector<int> buttonType, std::vector<Stick_Input_Type> stickType, std::vector<Trigger_Input_Type> correspondingTriggers, std::vector<UINT> keyType);

	// �v���C���[����̃A�N�e�B�u�t���O�̕ύX
	void ChangeActive(Operation_Type operation, bool active);

	// �p�b�h�������ꂽ����Ԃ�
	bool KeyTriggerDown(Operation_Type operation)const;

	// �p�b�h������������Ԃ�
	bool KeyTriggerUp(Operation_Type operation)const;

	// �p�b�h�������Ă��邩��Ԃ�
	bool KeyStateDown(Operation_Type operation)const;

	// �p�b�h��������Ă��邩��Ԃ�
	bool KeyStateUp(Operation_Type operation)const;

	// ���X�e�B�b�N�̌X����Ԃ�
	Vector2 Stick()const;

	// �E�X�e�B�b�N�̌X����Ԃ�
	Vector2 RightStick()const;

private:

	std::shared_ptr<Operation> GetOperation(Operation_Type operation) const;

	bool StickStateDown(Stick_Input_Type key) const;

	bool PreStickStateDown(Stick_Input_Type key) const;

	bool StickTriggerDown(Stick_Input_Type key) const;

	bool StickTriggerUp(Stick_Input_Type key) const;
	

private:

	// �v���C���[����̎�ނ̔z��
	std::vector<std::shared_ptr<Operation>> operations_;
};