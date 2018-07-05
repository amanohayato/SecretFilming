#pragma once
#include<map>
#include<memory>
#include"../Scene.h"
#include"../../World/World.h"
#include"../../Actor/Car/CarGenerateManager.h"
#include"../../Actor/Citizen/CitizenGenerateManager.h"

class SubScene;

class TitleCamera;
class TitleUfoFactory;

// �G���g�����X�V�[��
class EntranceScene :public Scene {

public:
	EntranceScene();

	virtual void start()override;
	virtual void update(float deltaTime)override;
	virtual void draw()const override;
	virtual void lateDraw() override;
	virtual void end() override;

	// �G���g�����X�V�[���̏�Ԃ�ύX����
	void changeState(SubSceneType next);

private:

	// �T�u�V�[���̎��
	std::map<SubSceneType, std::shared_ptr<SubScene>> subScenes_;

	// ���݂̃T�u�V�[���̏��
	std::shared_ptr<SubScene> curSubScene_;

	// �摜�_�ŗp�J�E���g
	int sinCount_{ 0 };

	// �o�ߎ��ԁi�b�j�̒l
	float elapsedTime_{ 0.0f };

	// ���b��Ƀf�����[�r�[�V�[���Ɉڍs���邩
	const float goDemoSceneTime_{ 15.0f };

	// �^�C�g���̔w�i�ɕK�v�ȃN���X����
	World world_;
	std::shared_ptr<TitleCamera> titleCamera_;
	std::shared_ptr<TitleUfoFactory> titleUfoFactory_;
	CarGenerateManager cagm_{};
	CitizenGenerateManager cigm_{};
};