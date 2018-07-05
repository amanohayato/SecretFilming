#pragma once
#include<vector>
#include<memory>
#include"../Scene.h"
#include"../../World/World.h"
#include"../../Actor/Car/CarGenerateManager.h"
#include"../../Actor/Citizen/CitizenGenerateManager.h"

class Player;

class TutorialEnemy;

class TutorialCommand;

class TutorialScene : public Scene
{
public:
	TutorialScene();

	virtual void start()override;
	virtual void update(float deltaTime)override;
	virtual void draw()const override;
	virtual void lateDraw()override;
	virtual void end() override;

	void setTutorialCommand();
	void changeTutorialCommand();

private:

	// �摜�_�ŗp�J�E���g
	int sinCount_{ 0 };

	// �o�ߎ��ԁi�b�j�̒l
	float elapsedTime_{ 0.0f };

	// ���b��Ƀf�����[�r�[�V�[���Ɉڍs���邩
	const float goDemoSceneTime_{ 15.0f };

	// �`���[�g���A���̃R�}���h���X�g
	std::vector<std::shared_ptr<TutorialCommand>> commandList_;
	
	// ���݂̃R�}���h�ԍ�
	int curIndex_{ 0 };

	// 
	World world_;
	std::shared_ptr<Player> player_;
	std::shared_ptr<TutorialEnemy> enemy_;
	CarGenerateManager cagm_{};
	CitizenGenerateManager cigm_{};
};
