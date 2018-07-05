#pragma once
#include "../ID/EnumIDs.h"
#include "Keyboard.h"
#include <vector>

// �v���C���[����̍\����
struct Operation
{
public:

	// �R���X�g���N�^
	Operation(Operation_Type type, std::vector<int> correspondingButtons, std::vector<Stick_Input_Type> correspondingSticks, std::vector<Trigger_Input_Type> correspondingTriggers)
	{
		IsActive = true;
		Type = type;
		CorrespondingButtons = correspondingButtons;
		CorrespondingSticks = correspondingSticks;
		CorrespondingTriggers = correspondingTriggers;
	};

	// ���̑�����󂯕t���邩�̃t���O
	bool IsActive;

	// �v���C���[����̎��
	Operation_Type Type;

	// �Ή�����{�^�����͂̎��
	std::vector<int> CorrespondingButtons;

	// �Ή�����X�e�B�b�N���͂̎��
	std::vector<Stick_Input_Type> CorrespondingSticks;

	// �Ή�����g���K�[���͂̎��
	std::vector<Trigger_Input_Type> CorrespondingTriggers;

	//****************************************
	// �f�o�b�O�p�L�[�{�[�h���͏���

	// �f�o�b�O�p�L�[�{�[�h���͍��݂̃R���X�g���N�^
	Operation(Operation_Type type, std::vector<int> correspondingButtons, std::vector<Stick_Input_Type> correspondingSticks, std::vector<Trigger_Input_Type> correspondingTriggers, std::vector<UINT> correspondingKeys)
	{
		IsActive = true;
		Type = type;
		CorrespondingButtons = correspondingButtons;
		CorrespondingSticks = correspondingSticks;
		CorrespondingTriggers = correspondingTriggers;
		CorrespondingKeys = correspondingKeys;
	};

	// �Ή�����L�[�{�[�h���͂̎��
	std::vector<UINT> CorrespondingKeys;
};