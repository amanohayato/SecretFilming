#pragma once
enum class Player_State_ID {
	Null=0,//�Ȃ�
	Idle,//�ҋ@
	Fall,//����
	Launch,//�Փˎ��̑ł��グ
	SetUp,//�J�������\����
	Dash,//�_�b�V��
	Event_Before,//�C�x���g�A�N�V�����O
	EventAction,//�C�x���g�A�N�V����
	Event_After,//�C�x���g�A�N�V������
	MapApp,//�}�b�v�A�v�����N������
	ActionReset,//���E�̃��Z�b�g
};