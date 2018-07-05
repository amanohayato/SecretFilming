#pragma once
#include"../Actor.h"

class IconControl : public Actor
{
public:

	IconControl(IWorld * world);

	void initialize();

	void update(float deltaTime) override;

	void draw()const;

	void camera_icon_flashing();

	void map_icon_flashing();

	//���b�Z�[�W�̎�M
	//virtual void receiveMessage(EventMessage message, void* param) override;


private:
	const float Yicon_drawX_{ 0.06f };//�}�b�v�A�C�R���̍��W���ߗp
	const float Yicon_drawY_{ 0.01f };
	const float LTicon_drawX_{ 0.16f };//�J�����A�C�R���̍��W���ߗp
	const float LTicon_drawY_{ 0.01f };
	const float mapicon_drawX_{ 0.01f };//�}�b�v�A�C�R���̍��W���ߗp
	const float mapicon_drawY_{ 0.03f };
	const float cameraicon_drawX_{ 0.11f };//�J�����A�C�R���̍��W���ߗp
	const float cameraicon_drawY_{ 0.03f };
	const float alerticon_drawX_{ 0.21f };//�A���[�g�A�C�R���̍��W���ߗp
	const float alerticon_drawY_{ 0.03f };//�A���[�g�A�C�R���̍��W���ߗp
	int score_{ 0 };//�G�l�~�[�̃X�R�A��Ԃ��擾
	float map_alpha_{ 1.f };//�}�b�v�̃A���t�@�l
	float camera_alpha_{ 1.f };//�J�����̃A���t�@�l
	bool camera_alphaup_{ false };//�J�����̃A���t�@�l���v���X����t���O
	bool map_alphaup_{ false };//�}�b�v�̃A���t�@�l���v���X����t���O
	const float speed_{ 3.f };//�_�ł̃X�s�[�h
	const float map_flashing_time_{ 10.0f };//�}�b�v�A�C�R�����_�ł��Ă��鎞�Ԃ�ݒ�
	bool points_change_{ false };//�ړI�n���؂�ւ�����Ƃ��p�̃t���O
	float flashing_count_{ 0.f };//�}�b�v�A�C�R�����_�ł��Ă��鎞�Ԃ��J�E���g
	Vector3 event_pos_{ 0.f, 0.f, 0.f };//eventposition�擾�p
	Vector3 before_event_pos_{ 0.f, 0.f, 0.f };////eventposition��r�p
	float deltaTime_;

	float _alert_alpha{ 0.0f };
};