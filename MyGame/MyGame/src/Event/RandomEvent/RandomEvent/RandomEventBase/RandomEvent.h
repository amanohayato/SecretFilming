#pragma once

// �������郉���_���C�x���g�̎��
enum class RandomEvent {
	// �����_���C�x���g�̎��
	Null_Eve,                      // ��̃C�x���g
	FallDown_Eve,                  // ������
	Signal_Eve,	                   // �ʐM

	// ������C�x���g�̏��
	FallDown_State,                // �O�ɓ]��(���̂Ƃ��X�q������)
	RisingHat_State,               // �����オ�藎���Ă���X�q��r��L�΂��ďE���A���ɂ��Ԃ�

    // �ʐM�C�x���g�̏��
	Hologram_State,                // �|�P�b�g���K�T�S�\������A�ʐM�A�C�e���������Ȃ���z���O�������f���o�����
	Conversation_State,            // �S�g�����F�����点�Ȃ���z���O�����Ɖ�b����
	StopShine_State,               // �����~�߂ċ}���Ń|�P�b�g�ɒʐM�A�C�e�������܂�

	// ���ʂŎg������
	LookAround_State,              // ��������n��
};