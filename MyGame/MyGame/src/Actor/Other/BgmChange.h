#pragma once
#include"../Actor.h"

class BgmChange : public Actor
{
public:

	BgmChange(IWorld * world);

	void initialize();

	void update(float deltaTime) override;

	void draw()const;

	//���b�Z�[�W�̎�M
	//virtual void receiveMessage(EventMessage message, void* param) override;


private:
	static const int transbgmtime_ = 5;//BGM���J�ڂ��Ă��瓦��BGM�����S�ɏ�����܂ł̎���(�b)

	double flightbgmvol_ = 0.0;//����BGM�{�����[��(%)
	double gamebgmvol_ = 1.0;//�Q�[��BGM�{�����[��(%)
	bool enemyescape_ = false;//�G�l�~�[��������Ԃ��ǂ���
	bool bgmsmallflag_ = false;//BGM������������t���O
};