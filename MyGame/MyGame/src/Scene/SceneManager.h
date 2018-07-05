#pragma once
#include<map>
#include<memory>
#include"../ID/EnumIDs.h"
class Scene;

class TransitionsAnimation;

//�V�[���̊Ǘ����s���AGame�y�т��̔h���N���X�ŗ��p����
class SceneManager {
public:
	SceneManager();
	void start();
	void update(float deltaTime);
	void draw();
	//�V�[�����I�����Ă��邩���m�F���A�K�v�ł���Ύ��̃V�[���ɑJ�ڂ���
	void checkIsEnd();
	//���̃V�[���֑J�ڂ���
	void next(TransitionsAnimeType transitionsAnimation);

	bool isGameEnd() const { return isGameEnd_; }

private:

	void changeNextScene();

private:

	// �V�[���J�ڃA�j���[�V�������Đ�����Ă��邩�̃t���O
	bool isTransitionsAnimation_{ false };

	//�V�[���ꗗ
	std::map<SceneType, std::shared_ptr<Scene>> scenes_;
	//���݂̃V�[��
	SceneType currentScene_;

	std::map<TransitionsAnimeType, std::shared_ptr<TransitionsAnimation>> transitionsAnimations_;
	TransitionsAnimeType currentAnime_;

	bool isGameEnd_{ false };
};